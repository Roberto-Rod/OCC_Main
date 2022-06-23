// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Collection;
import java.util.ArrayList;
import java.util.List;
import purejavacomm.UnsupportedCommOperationException;
import purejavacomm.PortInUseException;
import java.io.IOException;
import java.nio.channels.ByteChannel;
import console16bit.Console16bit;
import purejavacomm.CommPortIdentifier;
import purejavacomm.SerialPort;

public class SerialAdapterImpl implements SerialAdapter
{
    private String deviceName;
    private Integer baudRate;
    private SerialPort port;
    private CommPortIdentifier portId;
    private Bootloader16AbstractFactory factory;
    private Console16bit console;
    
    public SerialAdapterImpl(final Bootloader16AbstractFactory factory, final Console16bit console) {
        this.factory = factory;
        this.console = console;
    }
    
    @Override
    public void reportToConsole() {
        this.console.addConsoleText("Selected COM Port and Settings: " + this.deviceName + ", " + this.baudRate + ", 8N1");
    }
    
    @Override
    public AdapterStats getAdapterStats() {
        return new NullAdapterStatsImpl();
    }
    
    @Override
    public String getPort() {
        return this.deviceName;
    }
    
    @Override
    public Integer getBaudRate() {
        return this.baudRate;
    }
    
    @Override
    public ByteChannel getChannel() throws IOException {
        return this.factory.makeByteChannel(this.port.getInputStream(), this.port.getOutputStream());
    }
    
    @Override
    public void open() throws SerialAdapterInUseException, UnsupportedSerialAdapterOperationException {
        this.portId = this.getMapping().get(this.deviceName);
        if (this.portId == null) {
            throw new UnsupportedSerialAdapterOperationException("Port not found.");
        }
        try {
            this.port = (SerialPort)this.portId.open("Test", 1000);
        }
        catch (PortInUseException e) {
            throw new SerialAdapterInUseException((Throwable)e);
        }
        try {
            this.port.setDTR(true);
            this.port.setRTS(true);
            this.port.setSerialPortParams((int)this.baudRate, 8, 1, 0);
            this.port.setDTR(true);
            this.port.setRTS(true);
        }
        catch (UnsupportedCommOperationException e2) {
            throw new UnsupportedSerialAdapterOperationException((Throwable)e2);
        }
    }
    
    @Override
    public void close() {
        this.port.close();
    }
    
    @Override
    public void setBaudRate(final Integer baudRate) {
        this.baudRate = baudRate;
    }
    
    @Override
    public void setDeviceName(final String deviceName) {
        this.deviceName = deviceName;
    }
    
    @Override
    public String getDeviceName() {
        return this.deviceName;
    }
    
    @Override
    public boolean isDeviceNameSet() {
        return this.deviceName != null && !this.deviceName.isEmpty();
    }
    
    @Override
    public List<String> getPorts() {
        return new ArrayList<String>(this.getMapping().keySet());
    }
    
    private Map<String, CommPortIdentifier> getMapping() {
        final Map<String, CommPortIdentifier> mapping = new HashMap<String, CommPortIdentifier>();
        final Enumeration<CommPortIdentifier> portIdentifiers = (Enumeration<CommPortIdentifier>)CommPortIdentifier.getPortIdentifiers();
        while (portIdentifiers.hasMoreElements()) {
            final CommPortIdentifier p = portIdentifiers.nextElement();
            final String name = p.getName();
            mapping.put(name, p);
        }
        return mapping;
    }
}
