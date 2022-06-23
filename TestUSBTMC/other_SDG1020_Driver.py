
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
import binascii

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
    sdg1020.write("C1:OUTP?")
    response = sdg1020.read()
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
def check_if_C2_ON():
    sdg1020.write("C2:OUTP?")
    response = sdg1020.read()
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


#Little endian, 16-bit 2's complement
wave_points = [0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0xff7f]
def create_wave_file():
    """create a file"""
    f = open("wave1.bin", "wb")
    for a in wave_points:
        b = hex(a)
        b = b[2:]
        len_b = len(b)
        if (0 == len_b):
            b = '0000'
        elif (1 == len_b):
            b = '000' + b
        elif (2 == len_b):
            b = '00' + b
        elif (3 == len_b):
            b = '0' + b
        c = binascii.a2b_hex(b) #Hexadecimal integer to ASCii encoded string
        f.write(c)
    f.close()


def send_wave_data(sdg1020):
    """send wave1.bin to the device"""
    f = open("wave1.bin", "rb") #wave1.bin is the waveform to be sent
    data = f.read()
    print ("write bytes:",len(data))
    sdg1020.write("C1:WVDT WVNM,wave1,FREQ,2000.0,AMPL,4.0,OFST,0.0,PHASE,0.0,WAVEDATA,%s" % (data))
    #"X" series (SDG1000X/SDG2000X/SDG6000X/X-E)
    sdg1020.write("C1:ARWV NAME,wave1")
    f.close()


def get_wave_data(sdg1020):
    """get wave from the device"""
    f = open("wave2.bin", "wb") #save the waveform as wave2.bin
    sdg1020.write("WVDT? user,wave1") #"X" series (SDG1000X/SDG2000X/SDG6000X/X-E)
    time.sleep(1)
    data = sdg1020.read()
    data_pos = data.find("WAVEDATA,") + len("WAVEDATA,")
    print (data[0:data_pos])
    wave_data = data[data_pos:]
    print ("read bytes:",len(wave_data))
    f.write(wave_data)
    f.close()


if __name__ == '__main__':
    """"""
    #sdg1020 = rm.get_instrument(sdg1020, timeout=5000, chunk_size = 40*1024)
    create_wave_file()
    send_wave_data(sdg1020)
    get_wave_data(sdg1020)
    rm.close()

