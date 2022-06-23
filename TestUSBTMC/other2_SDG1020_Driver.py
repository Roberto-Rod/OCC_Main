
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
import time
#import binascii

# Channels list
#ch_list = ["C1", "C2"]
# Wave Types
#wave_type = ["SINE", "SQUARE", "RAMP", "PULSE", "NOISE", "ARB", "DC" , "PRBS" , "IQ"]

# Functions

# Turns a channel OFF
# Parameters: Channel C1 or C2
def turn_channel_OFF(channel):
    print("\nTurning OFF channel " + channel)
    sdg1020.write(channel + ":OUTP OFF")

# Turns a channel ON
# Parameters: Channel C1 or C2
def turn_channel_ON(channel):
    print("\nTurning ON channel " + channel)
    sdg1020.write(channel + ":OUTP ON")

# Turns OFF both channels
# Parameters: None
def turn_OFF_channels():
    print("\nTurning both channels OFF...")
    sdg1020.write("C1:OUTP OFF")
    sdg1020.write("C2:OUTP OFF")

# Check if the output of channel 1 is ON
# Parameters: None
# Return: Boolean 
def check_if_C1_ON():
    #print(sdg1020.query("C1:OUTPut?"))
    sdg1020.write("C1:OUTP?")
    response = sdg1020.read()
    #print("State query response: " + response)
    response = response.split()
    response = response[1].split(',')
    ch1_state = response[0]
    #print(ch1_state)
    #print(response.split(','))
    #print(response[1])

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
def check_if_C2_ON():
    #print(sdg1020.query("C1:OUTPut?"))
    sdg1020.write("C2:OUTP?")
    response = sdg1020.read()
    #print("State query response: " + response)
    response = response.split()
    response = response[1].split(',')
    ch2_state = response[0]
    #print(ch2_state)
    #print(response.split(','))
    #print(response[1])

    if ch2_state == "ON":
        print("\nC2 is ON!")
        return TRUE
    elif ch2_state == "OFF":
        print("\nC2 is OFF!")
        return FALSE
    else:
        print("\nWarning:Unknown channel 2 state!!!")



# Sets a basic wave in one of the two channels available (C1 and C2)
def set_basic_wave(channel, wave_type, frequency, amplitude, offset):
    print("\nSetting channel " + channel + " with a " + wave_type + " wave of " + frequency + "KHz, " + amplitude + "V amplitude with " + offset + "V offset.\n")
    sdg1020.write(channel + ":BSWV WVTP, " + wave_type + ", FRQ," + frequency + ", AMP," + amplitude + ",OFST, " + offset )

rm = pyvisa.ResourceManager()
rm.list_resources()
sdg1020 = rm.open_resource('USB0::0xF4ED::0xEE3A::SDG00001130273::INSTR')
print(sdg1020.query("*IDN?"))


# Set a wave using the following parameters
# Parameters Channel, Type of wave, Frequency, Amplitude, Offset
channel   = "C1"
wave_type = "ARB"
frequency = "1000"
amplitude = "1"
offset    = "0"  


# Turn both channels OFF
turn_OFF_channels()

check_if_C1_ON()
check_if_C2_ON()

#print(sdg1020.query("C1:OUTPut?"))

set_basic_wave(channel, wave_type, frequency, amplitude, offset)
# Turn Channel ON
turn_channel_ON(channel)
time.sleep(5)

# Turn Channel output OFF
turn_channel_OFF(channel)
check_if_C1_ON()
check_if_C2_ON()
rm.close()

#set_basic_wave("C1:BSWV WVTP,RAMP,FRQ,5000HZ,AMP,1V,OFST,0V")