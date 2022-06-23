import java.io.File;
import java.io.InputStream;
import java.io.OutputStream;

import com.microchip.mcu8.commandcore.ACommandBase;

import console16bit.Console16bitImpl;
import exceptionclasses.TransactionFailureException;
import i2cBootloaderController.mcu32.CommandChecksumUSBMCU32;
import i2cBootloaderController.mcu32.CommandEraseDeviceUSBMCU32;
import i2cBootloaderController.mcu32.CommandReadVersionProtocolUSBMCU32;
import i2cBootloaderController.mcu32.CommandResetDeviceUSBMCU32;
import i2cBootloaderController.mcu32.CommandWriteDeviceFlashUSBMCU32;
import i2cBootloaderModel.BootloaderModel;
import i2cBootloaderModel.DeviceArchitecture;
import javafx.scene.control.Tab;
import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;
import jssc.SerialPortTimeoutException;
import readFileController.IFileIO;
import readFileController.TextFileIO;
import readFileModel.MCU32MemoryModel;
import readFileModel.MemoryModel;
import usbhid4javaserviceprovider.Hid4JavaUSBAdapter;
import uartjsscadapter.JSSCSerialPortAdapter;
import java.io.IOException;
import java.util.concurrent.TimeUnit;
import unified.bootloader16bit.*;
import java.nio.channels.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

import purejavacomm.*;
import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import console16bit.*;
import java.util.*;
import java.io.*;

class StreamGobbler extends Thread {
    InputStream is;
    String type;
    Boolean success = false;

    StreamGobbler(InputStream is, String type) {
        this.is = is;
        this.type = type;
    }

    public Boolean IsSuccess() {
        return success;
    }

    public void run() {
        try {
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader br = new BufferedReader(isr);
            String line = null;
            while ((line = br.readLine()) != null) {
                if (line.contains("success")) {
                    success = true;
                }

                System.out.println(type + ">" + line);
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }
}

public class App {

    // Get a list of COM Ports attachec to PC
    public static String[] GetAttachedPorts() {
        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(50000);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        try {
            return jsscDriverInterface.getAttachedDevices();
        } catch (Exception ex) {
            System.out.println("Failed to enumerate com ports. " + ex.toString());
            String[] result = {};
            return result;
        }

    }

    // Program 32 bit pic via serial prototocol from programmer
    // This function does not work with DAR, left in case it is useful in future

    public static boolean ProgramSerial32Legacy(String Port, String FileName) {

        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(50000);
        jsscDriverInterface.setDeviceName(Port);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        try {
            jsscDriverInterface.getAttachedDevices();// needed due to bug in serial port handler
        } catch (Exception ex) {
            System.out.println("Failed to enumerate com ports. " + ex.toString());
        }
        System.out.println("Trying to Connect: " + Port);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            jsscDriverInterface.connect();
            inputStream = jsscDriverInterface.getInputStream();
            outputStream = jsscDriverInterface.getOutputStream();
            ProgramDevice32(inputStream, outputStream, FileName);
        } catch (IOException ex) {
            System.out.println("Device connection Failed" + ex.toString());
            return false;
        } finally {
            try {
                jsscDriverInterface.disconnect();
            } catch (IOException ex) {
                System.out.println("Device connection Failed" + ex.toString());
            }
        }

        return true;
    }

    // program a pic32 device, using input and output streams to communicate,
    // firmware is FileName
    public static void ProgramDevice32(InputStream InputStream, OutputStream OutputStream, String FileName) {
        BootloaderModel model = new BootloaderModel();
        // set up memory map
        MCU32MemoryModel mcu32DeviceMemoryModel = new MCU32MemoryModel();
        MemoryModel deviceMemoryModel = new MemoryModel(DeviceArchitecture.PIC32);

        int ProgramMemorySize = 0x4000;
        int BootloaderOffset = 0x400;
        int ByteAlignedEraseRowSize = 0x40;
        int ByteAlignedEepromSize = 0x40;
        int ByteAlignedConfigMemoryOffset = 0x30000;
        int ByteAlignedConfigSize = 0x0E;
        int ByteAlignedEepromMemoryOffset = 0x1E000;
        int WriteBlockSize = 0x20;

        deviceMemoryModel.setbyteAlignedprogramMemorySize(ProgramMemorySize);
        deviceMemoryModel.setbyteAlignedbootloaderOffset(BootloaderOffset);
        deviceMemoryModel.setbyteAlignedEraseRowSize(ByteAlignedEraseRowSize);
        deviceMemoryModel.setbyteAlignedeepromSize(ByteAlignedEepromSize);
        deviceMemoryModel.setbyteAlignedeepromMemoryOffset(ByteAlignedEepromMemoryOffset);
        deviceMemoryModel.setskipErasedFlashLocationsFlag(false);
        deviceMemoryModel.setbyteAlignedWriteBlockSize(WriteBlockSize);
        deviceMemoryModel.setbyteAlignedconfigurationWordsOffset(ByteAlignedConfigMemoryOffset);
        deviceMemoryModel.setbyteAlignedconfigurationWordsSize(ByteAlignedConfigSize);
        deviceMemoryModel.createProgramMemoryMap();
        deviceMemoryModel.createEEPROMMap();
        deviceMemoryModel.createConfigurationWordsMap();

        mcu32DeviceMemoryModel.createProgramMemoryMap();

        // create read command
        ACommandBase readVersionCommand = (ACommandBase) new CommandReadVersionProtocolUSBMCU32(InputStream,
                OutputStream, mcu32DeviceMemoryModel);
        readVersionCommand.setRetryCount(1);
        readVersionCommand.setTimeout(1000);
        readVersionCommand.setBootloaderModel(model);

        try {
            readVersionCommand.executeChain();
        } catch (TransactionFailureException ex) {
            System.out.println("Cannot read firmware version");
            return;
        }

        IFileIO fileReader = (IFileIO) new TextFileIO();
        fileReader.setMemoryModel((Object) mcu32DeviceMemoryModel);

        if (FileName.isEmpty()) {
            System.out.println("Hex File is Invalid");
            return;
        }
        final File fp = fileReader.fopen(FileName);
        fileReader.fread(fp);
        boolean endOfChain = false;

        try {
            endOfChain = false;
            System.out.println("Reading Version ...");

            readVersionCommand.executeChain();
            System.out.println("Bootloader Version Read Successful");

            // now create other commands
            ACommandBase eraseDeviceCommand = (ACommandBase) new CommandEraseDeviceUSBMCU32(InputStream, OutputStream,
                    mcu32DeviceMemoryModel);
            ACommandBase writeCommand = (ACommandBase) new CommandWriteDeviceFlashUSBMCU32(InputStream, OutputStream,
                    mcu32DeviceMemoryModel);
            ACommandBase checksumCommand = (ACommandBase) new CommandChecksumUSBMCU32(InputStream, OutputStream,
                    mcu32DeviceMemoryModel);
            ACommandBase resetCommand = (ACommandBase) new CommandResetDeviceUSBMCU32(InputStream, OutputStream,
                    mcu32DeviceMemoryModel);

            eraseDeviceCommand.setTimeout(20000);
            eraseDeviceCommand.setRetryCount(1);
            eraseDeviceCommand.setBootloaderModel(model);

            writeCommand.setTimeout(1000);
            writeCommand.setRetryCount(1);
            writeCommand.setBootloaderModel(model);

            checksumCommand.setTimeout(10000);
            checksumCommand.setRetryCount(1);
            checksumCommand.setBootloaderModel(model);

            resetCommand.setTimeout(100);
            resetCommand.setRetryCount(1);
            resetCommand.setBootloaderModel(model);

            System.out.println("Erasing Device ...");
            eraseDeviceCommand.executeChain();
            System.out.println("Erase Successful");

            System.out.println("Programming Flash ...");

            writeCommand.executeChain();
            System.out.println("Flashed Programmed");

            System.out.println("Resetting Device");

            System.out.println("Device Reset");

            System.out.println("Device: Bootloaded Successful");

            endOfChain = true;
            resetCommand.executeChain();
        } catch (TransactionFailureException ex) {
            if (endOfChain) {

                System.out.println("Device Programming Chain Completed.");
                System.out.println("Timeout for Reset Command Occured; this is expected behavior.");
            } else {
                System.out.println("Device Failed to respond to command...");
                System.out.println("Chain Exception Thrown: " + ex);
            }
        }
    }

    // program a 32 bit pic via USB bootloader, used on EFH bootloader
    public static void ProgramUSB32(String DeviceID, String FileName) {
        Hid4JavaUSBAdapter usbDriverInterface;
        final int USB_TIMEOUT_MS = 20000;

        usbDriverInterface = new Hid4JavaUSBAdapter();
        usbDriverInterface.setTimeOut(USB_TIMEOUT_MS);

        // get attached devices
        try {
            final String[] returnedListAvailable = usbDriverInterface.getAttachedDevices();
        } catch (java.io.IOException ex) {
            System.out.println("exception reading attached usb devices");
        }

        usbDriverInterface.setDeviceName(DeviceID);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            usbDriverInterface.connect();
            inputStream = usbDriverInterface.getInputStream();
            outputStream = usbDriverInterface.getOutputStream();
        } catch (java.io.IOException ex) {
            System.out.println("exception opening usb device");
            return;
        }

        ProgramDevice32(inputStream, outputStream, FileName);

        try {
            usbDriverInterface.disconnect();
        } catch (java.io.IOException ex) {
            System.out.println("exception opening usb device");
        }
    }

    // program a 32 bit pic via serial, using external python programming script,
    // return true on success
    public static Boolean ProgramSerial32_old(String Port, String Firmware) throws IOException {
        // "C:\Program Files\Microchip\xc32\v2.50\bin/xc32-objcopy.exe" -I ihex -O
        // binary input.hex test.bin
        //System.out.println("Convert .hex to .bin");
        var proc1 = Runtime.getRuntime().exec("pic32m-objcopy.exe -I ihex -O binary " + Firmware + " temp.bin");

        StreamGobbler errorGobbler1 = new StreamGobbler(proc1.getErrorStream(), "ERROR");

        // any output?
        StreamGobbler outputGobbler1 = new StreamGobbler(proc1.getInputStream(), "OUTPUT");

        // kick them off
        errorGobbler1.start();
        outputGobbler1.start();

        // any error???
        try {
            int exitVal1 = proc1.waitFor();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.out.println("Run python programming..." + Port);
        
                //.exec("python btl_host.py -v -i " + Port + " -d pic32mz -a 0x9D000000 -f temp_demo.bin");
        boolean result = false;
        Thread thread = new Thread(){
            public void run(){
                Process proc2 = null;
                try{
                proc2 = Runtime.getRuntime()
                    .exec("python btl_host.py -v -f temp_demo.bin -d pic32mz -i " + Port + " -a 0x9D000000");
                }
                catch(IOException ex){
                    System.out.println("pythone execution IO ERROR");
                }
                StreamGobbler errorGobbler2 = new StreamGobbler(proc2.getErrorStream(), "ERROR");
                StreamGobbler outputGobbler2 = new StreamGobbler(proc2.getInputStream(), "OUT ");
                errorGobbler2.start();
                outputGobbler2.start();
                try {
                    int exitVal2 = proc2.waitFor();
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                //result = outputGobbler2.IsSuccess();
            }
            };
        
        thread.start();

        

        // any output?
        
        // kick them off
        

        // any error???
        

        return false;
    }


    // program a 32 bit pic via serial, using external python programming script, return true on success
    public static Boolean ProgramSerial32(String Port, String Firmware) throws IOException
    {
        //"C:\Program Files\Microchip\xc32\v2.50\bin/xc32-objcopy.exe" -I ihex -O binary input.hex test.bin
        var proc1 = Runtime.getRuntime().exec("pic32m-objcopy.exe -I ihex -O binary " + Firmware +" ../python/temp.bin");
  
        StreamGobbler errorGobbler1 = new StreamGobbler(proc1.getErrorStream(), "ERROR");            
    
        // any output?
        StreamGobbler outputGobbler1 = new StreamGobbler(proc1.getInputStream(), "OUTPUT");
            
        // kick them off
        errorGobbler1.start();
        outputGobbler1.start();
                            
        // any error???
        try {
            int exitVal1 = proc1.waitFor();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.out.println("Run python programming... on: " + Port);
        



        var proc2 = Runtime.getRuntime().exec("cmd /c start \"\" ..\\python\\run_py.bat " + Port);//exec("python btl_host.py -v -f temp.bin -d pic32mz -i "+ Port + " -a 0x9D000000");
        //var proc2 = Runtime.getRuntime().exec("python C:/PYTH/btl_host.py -v -f temp.bin -d pic32mz -i "+ Port + " -a 0x9D000000");
        
        StreamGobbler errorGobbler2 = new 
        StreamGobbler(proc2.getErrorStream(), "ERROR");            
    
        // any output?
        StreamGobbler outputGobbler2 = new 
            StreamGobbler(proc2.getInputStream(), "OUTPUT");
            
        // kick them off
        errorGobbler2.start();
        outputGobbler2.start();
                            
        // any error???
        try {
            int exitVal2 = proc2.waitFor();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        return outputGobbler2.IsSuccess();
    }
    // Function to program pic 16 via its bootloader code
    // This never worked correctly, need to extract internal programming approach
    // and modify library
    // modified library now lives under bootloader16bit subfolder
    /*
     * public static void ProgramSerial16(String Port, String FileName) {
     * 
     * try { Bootloader16AbstractFactory factory; Bootloader16TargetDevice dev16;
     * 
     * factory = new Bootloader16AbstractFactoryFastImpl();
     * 
     * Bootloader16Model bootloader16Model = factory.makeBootloader16Model();
     * 
     * // need to access adapterbuilder inside bootloader16model to set serial port
     * details File firmware = new File(FileName);
     * bootloader16Model.setHexFileName(firmware);
     * 
     * bootloader16Model.setSerialPortName(Port);
     * bootloader16Model.setBaudRate(115200); //call program on bootloader16model
     * var x = bootloader16Model.getClass().getDeclaredMethod("program");
     * x.setAccessible(true); x.invoke(bootloader16Model); } catch (Exception e) {
     * 
     * } }
     */

    // Print help message
    public static void PrintUsage() {
        System.out.println("Programming Tool  v1.0");
        System.out.println("Usage:");
        System.out.println("ProgrammingTool [cmd] [port] ([firmware])");
        System.out.println("Commands:");
        System.out.println("R [port] - send reset command to firmware, port should be COMx");
        System.out.println(
                "PEFH [ID] [Firmware] - program EFH 32 bit pic over USB, ID should be HID id (3C by default), Firmware should be path to hex file");
        System.out.println(
                "PDAR [Port] [Firmware] - program DAR 32 bit pic over serial, port should be COMx, Firmware should be path to hex file");
        System.out.println(
                "PDSP [Port] [Firmware] - NOT WORKING! program dspic 16 bit pic over serial, port should be COMx, Firmware should be path to hex file");

        System.out.println(
                "A [ID] [EFHAppFW] [EFHBootsrapFW] [DARAppFW] [DSPAppFW]-  EXPERIMENTAL! attempt automatic firmware swap, with port detection, ID is usb id (3C by default), the rest are hex files for the firmwares");
        System.out.println(
                "START [ID] [EFHAppFW] [EFHBootsrapFW] [DARAppFW] [DSPAppFW]-  EXPERIMENTAL! Start with the board running just bootloaders, and do first load of firmware, parameters the same as with A");
    }

    // Find strings in New that are not in Old, return list
    public static String[] GetNewEntries(String[] New, String[] Old) {
        ArrayList<String> Results = new ArrayList<String>();
        for (String curr : New) {
            boolean isNew = true;
            for (String test : Old) {
                if (test.equals(curr)) {
                    isNew = false;
                }
            }
            if (isNew) {
                Results.add(curr);
            }
        }
        return Results.toArray(new String[0]);
    }

    // send ? to port, record response
    public static String QueryPort(String port) {
        String result = null;

        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(1000);// short timeout due to number of ports queried
        jsscDriverInterface.setDeviceName(port);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        System.out.println("Trying to query port: " + port);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            jsscDriverInterface.getAttachedDevices();// needed to avoid bug
            jsscDriverInterface.connect();
            outputStream = jsscDriverInterface.getOutputStream();
            inputStream = jsscDriverInterface.getInputStream();
            outputStream.write('?');
            TimeUnit.SECONDS.sleep(1);
            var resultBytes = inputStream.readNBytes(7);
            result = new String(resultBytes, StandardCharsets.UTF_8);

        } catch (IOException ex) {

            System.out.println("Device query Failed" + ex.toString());
        } catch (InterruptedException ex) {
            System.out.println("sleep failed" + ex.toString());
        } finally {
            try {
                jsscDriverInterface.disconnect();
            } catch (IOException ex) {
                System.out.println("Device failed to close");
            }

        }
        return result;
    }

    // send char to port, record response
    public static String Send_query_to_port(String port, char ch) {
        String result = null;

        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(1000);// short timeout due to number of ports queried
        jsscDriverInterface.setDeviceName(port);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        System.out.println("Trying to send char to: " + port);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            jsscDriverInterface.connect();
            outputStream = jsscDriverInterface.getOutputStream();
            inputStream = jsscDriverInterface.getInputStream();
            outputStream.write(ch);
            TimeUnit.SECONDS.sleep(1);
            var resultBytes = inputStream.readNBytes(7);
            result = new String(resultBytes, StandardCharsets.UTF_8);

        } catch (IOException ex) {

            System.out.println("Device query Failed" + ex.toString());
        } catch (InterruptedException ex) {
            System.out.println("sleep failed" + ex.toString());
        } finally {
            try {
                jsscDriverInterface.disconnect();
            } catch (IOException ex) {
                System.out.println("Device failed to close");
            }

        }
        return result;
    }

    public static void Send_char_cmd_to_port(String Port, char ch) {
        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(5000);
        jsscDriverInterface.setDeviceName(Port);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        System.out.println("Trying to Send_char_cmd_to_port: " + Port);
        OutputStream outputStream = null;
        try {
            jsscDriverInterface.getAttachedDevices();// needed to avoid bug
            jsscDriverInterface.connect();
            outputStream = jsscDriverInterface.getOutputStream();
            outputStream.write(ch);
            jsscDriverInterface.disconnect();
        } catch (IOException ex) {
            System.out.println("Send_char_cmd_to_port Failed" + ex.toString());
        }
    }

    public static String Send_char_to_port(String port, char ch) {
        String result = null;

        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(1000);// short timeout due to number of ports queried
        jsscDriverInterface.setDeviceName(port);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        System.out.println("Trying to send char to: " + port);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            jsscDriverInterface.getAttachedDevices();
            jsscDriverInterface.connect();
            outputStream = jsscDriverInterface.getOutputStream();
            inputStream = jsscDriverInterface.getInputStream();
            outputStream.write(ch);
            TimeUnit.SECONDS.sleep(1);

            // System.out.println("readbyte: " + inputStream.read());
            byte resultBytes[] = new byte[7];
            System.out.println("port: " + port + " returned: " + inputStream.read(resultBytes, 0, 7) + " bytes");
            {
                result = new String(resultBytes, StandardCharsets.UTF_8);
            }
        } catch (IOException ex) {
            System.out.println("Device query didn't return value.");
            // System.out.println("Device query Failed" + ex.toString());
        } catch (InterruptedException ex) {
            System.out.println("sleep failed" + ex.toString());
        }

        try {
            jsscDriverInterface.disconnect();
        } catch (IOException ex) {
            System.out.println("Device failed to close");
        }

        if (result == null)
            return "";
        return result;
    }

    // send ? to port, record response
    public static String AdvanceToEndOfFrame(String port) {
        String result = null;

        JSSCSerialPortAdapter jsscDriverInterface = new JSSCSerialPortAdapter();
        jsscDriverInterface.setTimeOut(1000);// short timeout due to number of ports queried
        jsscDriverInterface.setDeviceName(port);
        jsscDriverInterface.baudRate = 115200;
        jsscDriverInterface.dataBits = 8;
        jsscDriverInterface.stopBits = 1;

        System.out.println("Trying to nudge port: " + port);
        InputStream inputStream = null;
        OutputStream outputStream = null;

        for (int i = 0; i <= 16; i++) {
            try {
                jsscDriverInterface.connect();
                outputStream = jsscDriverInterface.getOutputStream();
                inputStream = jsscDriverInterface.getInputStream();
                outputStream.write('?');
                TimeUnit.SECONDS.sleep(1);
                var resultBytes = inputStream.readNBytes(1);
                result = new String(resultBytes, StandardCharsets.UTF_8);
                break;

            } catch (IOException ex) {

                System.out.println("Device query Failed" + ex.toString());
            } catch (InterruptedException ex) {
                System.out.println("sleep failed" + ex.toString());
            } finally {
                try {
                    jsscDriverInterface.disconnect();
                } catch (IOException ex) {
                    System.out.println("Device failed to close");
                }

            }
        }

        return result;
    }

    // query a range of ports, recording the responses
    public static String[] QueryPorts(String[] ports) {
        ArrayList<String> Results = new ArrayList<String>();
        for (String port : ports) {
            String result = QueryPort(port);
            if (result == null) {
                result = "";

            }
            Results.add(result);
        }

        return Results.toArray(new String[0]);
    }

    public static void rerun_port(String port) {
        SerialPort serialPort = new SerialPort(port);
        try {
            serialPort.openPort();//Open serial port
            serialPort.setParams(9600, 8, 1, 0);//Set params.
            byte[] buffer = serialPort.readBytes(10);//Read 10 bytes from serial port
            serialPort.closePort();//Close serial port
        }
        catch (SerialPortException ex) {
            System.out.println(ex);
        }
    }
    // return port thats response matches message
    public static String FindPort(String message, String[] listIDs, String[] listPorts) {
        boolean found = false;
        String port = "error";
        for (int i = 0; i < listIDs.length; i++) {
            String curr = listIDs[i];
            if (curr.equals(message)) {
                found = true;
                port = listPorts[i];
            }
        }
        return port;
    }

    // Automatically program sequence, detecting ports
    public static void AutoProgram(String USBBootloaderID, String EFHAppFW, String EFHBootstrapFW, String DARAppFW,
            String DSPAppFW, boolean StartWithBootloader) throws IOException, InterruptedException {
        System.out.println("Automatic programmer v1.0");

        String[] PortsBeforeBootstrap = GetAttachedPorts();
        // get ports that are available before start

        TimeUnit.SECONDS.sleep(1);
        System.out.println("Program EFH with bootstrap...");
        ProgramUSB32(USBBootloaderID, EFHBootstrapFW);
        System.out.println("Program EFH with bootstrap complete");
        TimeUnit.SECONDS.sleep(2);

        System.out.println("Continue with Bootstrap firmware...");

        String[] NewPorts2 = GetAttachedPorts(); // get ports that are available after attaching (should be
                                                 // PortsBeforeBootstrap+ 3 bootstrap serial devices)

        String[] AddedPorts2 = GetNewEntries(NewPorts2, PortsBeforeBootstrap);
        

        if (AddedPorts2.length != 3) {
            System.out.println("ERROR: Incorrect number of new ports found!!");
            return;
        }

        //String[] PortIDs2 = QueryPorts(AddedPorts2); // send ? to each port, get responses

        System.out.println("Findning EFH...");
        var EFH_bootstrap = "";
        for (String port : AddedPorts2) {
            TimeUnit.MILLISECONDS.sleep(200);
            var ret = Send_char_to_port(port, '?');
            System.out.println("Response from port: " + port + " -> " + ret);
            if (ret.equals("EFH2 Bo")) {
                EFH_bootstrap = port;
                break;
            }
        }
        
        System.out.println("Sending 'l' - lock command...");
        Send_char_to_port(EFH_bootstrap, 'l');
        System.out.println("Findning DAR...");
        var DAR_port = "";
        for (String port : AddedPorts2) {
            TimeUnit.MILLISECONDS.sleep(500);
            if(port == EFH_bootstrap) {continue;}
            var ret = Send_char_to_port(port, '?');
            System.out.println("Response from port: " + port + " -> " + ret);
            if (ret.equals("UART1 i")) {
                DAR_port = port;
                break;
            }
        }

        if(DAR_port == ""){
            System.out.println("ERROR - unable to find port for DAR device.");
            return;
        }

        //System.out.println("Sending 'u' - unlock command...");
        //Send_char_to_port(EFH_bootstrap, 'u');

        System.out.println("Skipped 'u' command");

        TimeUnit.SECONDS.sleep(2);
        
        System.out.println("Sending 'h' - recover DAR command...");
        Send_char_to_port(EFH_bootstrap, 'h');
        TimeUnit.MILLISECONDS.sleep(300);

        

        // program DAR repeatedly until success ( usually fails first go )
        
        for (int i = 1; i < 20; i++) {
            System.out.println("Program DAR with application... on port " + DAR_port + " / processing unit: " + i);
            var proc3 = Runtime.getRuntime().exec("../c_sharp/Release/COMrefresh.exe");
            TimeUnit.SECONDS.sleep(2);

            ProgramSerial32(DAR_port, DARAppFW);
            TimeUnit.MILLISECONDS.sleep(500);
            while(Files.exists(Paths.get("../python/py_in_run.temp")) == true){
                TimeUnit.SECONDS.sleep(2);
            }
            if(Files.exists(Paths.get("../python/py_sucessed.temp")) == true){
                Files.delete(Paths.get("../python/py_sucessed.temp"));
                break;
            }

            if(i%5 == 0){
                System.out.println("Sending 'h' command...");
                Send_char_to_port(EFH_bootstrap, 'h');
                var proc4 = Runtime.getRuntime().exec("../c_sharp/Release/COMrefresh.exe");
                TimeUnit.MILLISECONDS.sleep(500);
            }

        }
        System.out.println("Program DAR with application complete");

        System.out.println("Refresh COM ports.");
        TimeUnit.SECONDS.sleep(2);
        var proc5 = Runtime.getRuntime().exec("../c_sharp/Release/COMrefresh.exe");
        TimeUnit.SECONDS.sleep(2);


        System.out.println("Reset EFH to bootloader...");
        Send_char_to_port(EFH_bootstrap, 'r');

        TimeUnit.SECONDS.sleep(4);

        System.out.println("Program EFH with application...");
        ProgramUSB32(USBBootloaderID, EFHAppFW);
        System.out.println("Program EFH with application complete");
        System.out.println("");
        System.out.println("+---------------------------------+");
        System.out.println("| P1 Firmware Update Successful ! |");
        System.out.println("+---------------------------------+");
    }

    // Automatically program sequence, detecting ports
    public static void AutoProgram2(String USBBootloaderID, String EFHAppFW, String EFHBootstrapFW, String DARAppFW,
            String DSPAppFW, boolean StartWithBootloader) throws IOException, InterruptedException {
        System.out.println("Automatic programmer v1.0");
        // StartWithBootloader = true;
        Scanner s = new Scanner(System.in);
        /*
         * System.out.
         * println("Please detach device USB cables from computer, and press enter to continue..."
         * ); s.nextLine(); TimeUnit.SECONDS.sleep(2);
         * 
         * if (!StartWithBootloader) {
         * 
         * String[] OtherPorts = GetAttachedPorts(); //get any ports in PC that are not
         * ours
         * 
         * System.out.
         * println("Please attach USB cable to debug usart, wait for devices to be set up, and press enter to continue..."
         * ); s.nextLine(); TimeUnit.SECONDS.sleep(2); String[] NewPorts =
         * GetAttachedPorts(); //get ports that are available after attaching (should be
         * Otherports+ 4 debug serial devices) String[] AddedPorts =
         * GetNewEntries(NewPorts, OtherPorts); //should be 4 debug serial devices
         * 
         * if (AddedPorts.length!=4) {
         * System.out.println("ERROR: Incorrect number of new ports found!!"); return; }
         * 
         * System.out.println("Identify Ports...");
         * 
         * String[] PortIDs = QueryPorts(AddedPorts); // send ? to each port, get
         * responses
         * 
         * var dspicDebug = FindPort("DSPIC A",PortIDs, AddedPorts);
         * 
         * 
         * if (dspicDebug.equals("error")) {
         * System.out.println("ERROR: DSPIC Application firmware debug port not found!"
         * ); return; } var darDebug = FindPort("DAR App",PortIDs, AddedPorts);
         * 
         * if (darDebug.equals("error")) {
         * System.out.println("ERROR: DAR Application firmware debug port not found!");
         * return; }
         * 
         * var efhDebug = FindPort("EFH App",PortIDs, AddedPorts);
         * 
         * if (efhDebug.equals("error")) {
         * System.out.println("ERROR: EFH firmware debug port not found!"); return; }
         * 
         * System.out.println("Reset EFH controller into bootloader...");
         * 
         * //reset EFH app to bootloader SendSerialResetCommand(efhDebug);
         * 
         * 
         * System.out.println("Reset into bootloader complete"); }
         */
        String[] PortsBeforeBootstrap = GetAttachedPorts(); // get ports that are available after attaching (should be
                                                            // Otherports+ 4 debug serial devices if
                                                            // !startswithbootloader, just system ports otherwise)

        TimeUnit.SECONDS.sleep(2);
        System.out.println("Program EFH with bootstrap...");
        ProgramUSB32(USBBootloaderID, EFHBootstrapFW);
        System.out.println("Program EFH with bootstrap complete");

        System.out.println("Now please reset the board, and press enter to continue....");
        s.nextLine();

        String[] NewPorts2 = GetAttachedPorts(); // get ports that are available after attaching (should be
                                                 // PortsBeforeBootstrap+ 3 bootstrap serial devices)

        String[] AddedPorts2 = GetNewEntries(NewPorts2, PortsBeforeBootstrap);

        if (AddedPorts2.length != 3) {
            System.out.println("ERROR: Incorrect number of new ports found!!");
            return;
        }

        String[] PortIDs2 = QueryPorts(AddedPorts2); // send ? to each port, get responses

        String dspicBootloader = "error";
        String darBootloader = "error";

        if (!StartWithBootloader) {
            // Not starting with bootloader, so expect ports to respond
            /// Check serial ports from bootstrap are responding
            dspicBootloader = FindPort("DSPIC A", PortIDs2, AddedPorts2);
            if (dspicBootloader.equals("errror")) {
                System.out.println("ERROR: EFH bootloader firmware DSPIC port not found!");
                return;
            }

            darBootloader = FindPort("DAR App", PortIDs2, AddedPorts2);
            if (darBootloader.equals("error")) {
                System.out.println("ERROR: EFH bootloader firmware DAR  port not found!");
                return;
            }

        }

        var efhBootloaderCommand = FindPort("EFH Boo", PortIDs2, AddedPorts2);
        if (efhBootloaderCommand.equals("error")) {
            System.out.println("ERROR: EFH bootloader firmware control port not found!");
            return;
        }

        if (!StartWithBootloader) {
            // we know ports, so program correct ports
            System.out.println("resetting DAR and DSPIC....");
            SendSerialResetCommand(darBootloader);
            SendSerialResetCommand(dspicBootloader);

            System.out.println("Waiting for reset....");
            TimeUnit.SECONDS.sleep(2);
            System.out.println("Program DAR with application...");
            // program DAR repeatedly until success ( usually fails first go )
            for (int i = 0; i < 10; i++) {
                if (ProgramSerial32(darBootloader, DARAppFW))
                    break;
                TimeUnit.SECONDS.sleep(5);
            }
            System.out.println("Program DAR with application complete");

            // System.out.println("TODO: Program dsPIC with application...");
            // ProgramSerial16
            // System.out.println("Program dsPIC with application complete");
        } else {
            // we dont know ports, so guess
            ArrayList<String> potentialPortsList = new ArrayList<String>();
            for (String curr : AddedPorts2) {
                potentialPortsList.add(curr);
            }
            potentialPortsList.remove(efhBootloaderCommand);

            var potentialPorts = potentialPortsList.toArray(new String[0]);
            int j = 0;
            var res1 = AdvanceToEndOfFrame(potentialPorts[j]);
            TimeUnit.SECONDS.sleep(2);
            System.out.println("Try to program DAR with application on either port...");

            // program DAR repeatedly until success ( usually fails first go )
            for (int i = 0; i < 5; i++) {
                if (ProgramSerial32(potentialPorts[j], DARAppFW)) {
                    // now we know which port is which
                    darBootloader = potentialPorts[j];
                    dspicBootloader = potentialPorts[1 - j];
                    break;
                }

                TimeUnit.SECONDS.sleep(5);

            }

            if (darBootloader.equals("error")) {
                j = 1 - j;
                var res2 = AdvanceToEndOfFrame(potentialPorts[j]); // clear any crud from port
                TimeUnit.SECONDS.sleep(2);
                for (int i = 0; i < 5; i++) {
                    if (ProgramSerial32(potentialPorts[j], DARAppFW)) {
                        // now we know which port is which
                        darBootloader = potentialPorts[j];
                        dspicBootloader = potentialPorts[1 - j];
                        break;
                    }
                    TimeUnit.SECONDS.sleep(5);
                }
            }

            if (darBootloader.equals("error")) {
                System.out.println("ERROR: Unable to locate DAR bootloader!");
                return;
            }
            System.out.println("Program DAR with application complete");

            // System.out.println("TODO: Program dsPIC with application...");
            // ProgramSerial16
            // System.out.println("Program dsPIC with application complete");
        }

        System.out.println("Waiting a bit....");
        TimeUnit.SECONDS.sleep(5);
        System.out.println("Reset EFH into bootloader...");
        SendSerialResetCommand(efhBootloaderCommand);
        System.out.println("Reset EFH into bootloader complete");
        System.out.println("Waiting for usb device....");
        TimeUnit.SECONDS.sleep(5);
        System.out.println("Program EFH with application...");
        ProgramUSB32(USBBootloaderID, EFHAppFW);
        System.out.println("Program EFH with application complete");
        System.out.println("Auto program now complete!");
    }

    private static void SendSerialResetCommand(String darBootloader) {
    }

    public static boolean IsMinimumArgsCountTooLow(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Too Few Arguments!");
            PrintUsage();
            return true;
        }
        return false;
    }

    public static boolean CheckArgumentLength(String[] args, int num) {
        if (args.length != num) {
            System.out.println("Error: Incorrect number of arguments!");
            PrintUsage();
            return false;
        }
        return true;
    }

    public static void main(String[] args) throws Exception {

        if (IsMinimumArgsCountTooLow(args)) {
            return;
        }

        switch (args[0]) {
        case "R":
            if (!CheckArgumentLength(args, 2))
                return;
            SendSerialResetCommand(args[1]);
            break;

        case "PEFH":
            if (!CheckArgumentLength(args, 3))
                return;
            ProgramUSB32(args[1], args[2]);
            break;

        case "PDAR":
            if (!CheckArgumentLength(args, 3))
                return;
            ProgramSerial32(args[1], args[2]);
            break;

        case "PDSP":
            System.out.println("This function is not implemented yet!");
            if (!CheckArgumentLength(args, 4))
                return;
            break;

        case "A":
            System.out.println("This function is experimental!");
            if (!CheckArgumentLength(args, 6))
                return;

            AutoProgram(args[1], args[2], args[3], args[4], args[5], false);
            break;
        case "START":
            System.out.println("This function is experimental!");

            AutoProgram(args[1], args[2], args[3], args[4], args[5], true);
            break;
        default:
            System.out.println("Error: Invalid Command!");
            PrintUsage();
            break;
        }

    }
}
