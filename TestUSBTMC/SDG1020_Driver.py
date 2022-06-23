
#*IDN\sSDG,SDG1020,SDG00001130273,1.01.01.23R1,02-00-00-19-24\n
# Manufacturer Name:    Siglent Technologies Co. Ltd
# Model Name:           SDG1020
# Manufacturer ID:      0xF4ED
# Model Code:           0xEE3A           
# USB Serial Number:    SDG00001130273
# Firmware Version:     1.01.01.23R1
# Hardware Version:     02-00-00-19-24

"""Pachymeter Automated Software Verification Rig SDG1020 Signal Generator Device Driver"""

from pickle import FALSE, TRUE
import pyvisa


class SDG1020Class(object):
    def __init__(self):
        rm = pyvisa.ResourceManager()
        rm.list_resources()
        self.sdg1020 = rm.open_resource('USB0::0xF4ED::0xEE3A::SDG00001130273::INSTR')
        print("\nConnection established with the SDG1020 AWG: " + self.sdg1020.query("*IDN?"))

    # Close connection with SDG1020
    def sdg1020_close_connection(self):
        print("\nConnection with the SDG1020 AWG closed!")
        self.sdg1020.close()

    # Turns a channel OFF
    # Parameters: Channel C1 or C2
    def sdg1020_turn_channel_OFF(self, channel):
        print("\nTurning OFF channel " + channel)
        self.sdg1020.write(channel + ":OUTP OFF")

    # Turns a channel ON
    # Parameters: Channel C1 or C2
    def sdg1020_turn_channel_ON(self, channel):
        print("\nTurning ON channel " + channel)
        self.sdg1020.write(channel + ":OUTP ON")

    # Turns OFF both channels
    # Parameters: None
    def sdg1020_turn_OFF_channels(self):
        print("\nTurning both channels OFF...")
        self.sdg1020.write("C1:OUTP OFF")
        self.sdg1020.write("C2:OUTP OFF")

    # Check if the output of channel 1 is ON
    # Parameters: None
    # Return: Boolean 
    def sdg1020_check_if_C1_ON(self):
        self.sdg1020.write("C1:OUTP?")
        response = self.sdg1020.read()
        #print("State query response: " + response)
        response = response.split()
        response = response[1].split(',')
        ch1_state = response[0]

        if ch1_state == "ON":
            print("\nC1 is ON!")
            return TRUE
        elif ch1_state == "OFF":
            print("\nC1 is OFF!")
            return FALSE
        else:
            print("\nWarning:Unknown channel 1 state!!!")

    # Check if the output of channel 2 is ON
    # Parameters: None
    # Return: Boolean 
    def sdg1020_check_if_C2_ON(self):
        self.sdg1020.write("C2:OUTP?")
        response = self.sdg1020.read()
        #print("State query response: " + response)
        response = response.split()
        response = response[1].split(',')
        ch2_state = response[0]

        if ch2_state == "ON":
            print("\nC2 is ON!")
            return TRUE
        elif ch2_state == "OFF":
            print("\nC2 is OFF!")
            return FALSE
        else:
            print("\nWarning:Unknown channel 2 state!!!")

    # Sets a basic wave in one of the two channels available (C1 and C2)
    def sdg1020_set_basic_wave(self, channel, wave_type, frequency, amplitude, offset, phase):
        print("\nSetting channel " + channel + " with a " + wave_type + " sweeping wave of " + str(frequency) + "Hz, " + str(amplitude) + "V amplitude with " + str(2 * (float(offset))) + "V offset," + " phase " + str(float(phase)))
        self.sdg1020.write(channel + ":BSWV WVTP, " + wave_type + ", FRQ," + str(frequency) + ", AMP," + str(amplitude) + ",OFST," + str(offset) + ",PHSE," + str(phase))

    # Function to send any general query
    def sdg1020_send_query(self, channel, query):
        return self.sdg1020.query(channel + query)
    
     # Function to write any general command
    def sdg1020_send_command(self, channel, command):
        self.sdg1020.write(channel + command)
    
    # Function to read device's response
    def sdg1020_read_response(self):
        return self.sdg1020.read()

    # Function to reset the device
    def sdg1020_reset_device(self):
        self.sdg1020.write("*RST")
    
    # Set a sweeping wave
    def sdg1020_set_sweeping_wave(self, channel, wave_type, start_freq, amplitude, offset, phase, sweep_time, stop_freq):
        print("\nSetting channel " + channel + " with a " + wave_type + " sweeping wave of " + str(start_freq) + "Hz, " + str(amplitude) + "V amplitude with " + str(2 * (float(offset))) + "V offset," + " phase " + str(float(phase)))
        self.sdg1020.write(channel + ":BSWV WVTP, " + wave_type + ", FRQ," + str(start_freq) + ", AMP," + str(amplitude) + ",OFST," + str(offset) + ",PHSE," + str(phase))
        self.sdg1020.write(channel, ":SWWV STATE,ON,TIME," + str((float(sweep_time))) + ",START," + str(start_freq) + "Hz, " +",STOP,"+ str(stop_freq) + "HZ,TRSR,INT,TRMD,OFF,SWMD,LINE,DIR,UP")