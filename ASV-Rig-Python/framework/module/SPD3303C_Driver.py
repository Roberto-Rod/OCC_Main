
#*IDN\sSiglent\sTechnologies,SPD3303C,NPD3ECAQ1R0177,1.02.01.01.03R6,V1.3\n
# Manufacturer Name:    Siglent Technologies
# Model Name:           SPD3303C
# Manufacturer ID:      0x0483
# Model Code:           0x7540
# USB Serial Number:    SDG00001130273
# Firmware Version:     1.02.01.01.03R6
# Hardware Version:     V1.3


"""Pachymeter Automated Software Verification Rig SPD 3303C Power Supply Device Driver"""


import pyvisa
import time

class SPD330Class(object):
    def __init__(self):
        rm = pyvisa.ResourceManager()
        rm.list_resources()
        self.spd3303 = rm.open_resource('USB0::0x0483::0x7540::SPD3EEDD5R3305::INSTR')
        print(self.spd3303)
        self.spd3303.write("*IDN?")
        time.sleep(0.02)
        reply = self.spd3303.read()
        print("\nConnection established with  the SPD3303C PSU: " + reply)

    # Close connection with SPD3303
    def spd3303_close_connection(self):
        self.spd3303.close()
        print("\nConnection with the SPD3303C PSU closed!")

    # Get device error
    def spd3303_get_sys_error(self):
        self.spd3303.write("SYSTem:ERRor?")
        time.sleep(0.02)
        return self.spd3303.read()
        #print("System Error => " + reply)

    # Configure channel 1 voltage and current limit
    def spd3303_CH1_configure_VC(self, voltage, current):
        self.spd3303.write("CH1:VOLTage " + str(voltage))
        time.sleep(0.05)
        self.spd3303.write("CH1:CURRent " + str(current))
        time.sleep(0.05)

    # Configure channel 2 voltage and current limit
    def spd3303_CH2_configure_VC(self, voltage, current):
        self.spd3303.write("CH2:VOLTage " + str(voltage))
        time.sleep(0.05)
        self.spd3303.write("CH2:CURRent " + str(current))
        time.sleep(0.05)

    # Configure both channels
    def spd3303_CH1_and_CH2_configure_VC(self, CH1voltage, CH1current, CH2voltage, CH2current):
        self.spd3303.write("CH1:VOLTage " + str(CH1voltage))
        time.sleep(0.05)
        self.spd3303.write("CH1:CURRent " + str(CH1current))
        time.sleep(0.05)
        self.spd3303.write("CH2:VOLTage " + str(CH2voltage))
        time.sleep(0.05)
        self.spd3303.write("CH2:CURRent " + str(CH2current))
        time.sleep(0.05)

    # Turn ON channel 1
    def spd3303_CH1_turn_ON(self):
        self.spd3303.write("OUTPut CH1, ON")
        time.sleep(0.05)

    # Turn ON channel 2
    def spd3303_CH2_turn_ON(self):
        self.spd3303.write("OUTPut CH2, ON")
        time.sleep(0.05)

    # Turn OFF channel 1
    def spd3303_CH1_turn_OFF(self):
        self.spd3303.write("OUTPut CH1, OFF")
        time.sleep(0.05)

    # Turn OFF channel 2
    def spd3303_CH2_turn_OFF(self):
        self.spd3303.write("OUTPut CH2, OFF")
        time.sleep(0.05)

    # Select channel track configuration
    # OUTPut <SOURce>, <state>
    # NR1>:={0[Independent] | 1[Series] | 2[Parallel]}
    def spd3303_configure_operation_mode(self, mode):
        self.spd3303.write("OUTPut:TRACK ", str(mode))
        time.sleep(0.05)

    # Measure current on a given channel
    def spd3303_measure_current(self, channel):
        self.spd3303.write("MEASure:CURRent? ", channel)
        time.sleep(0.05)
        return float(self.spd3303.read())

    # Measure voltage on a given channel
    def spd3303_measure_voltage(self, channel):
        self.spd3303.write("MEASure:VOLTage? ", channel)
        time.sleep(0.05)
        return float(self.spd3303.read())

    # Save configuration
    def spd3303_save_configuration(self, storage):
        self.spd3303.write("*SAV ", str(storage))
        time.sleep(0.1)

     # Recall configuration
    def spd3303_recall_configuration(self, storage):
        self.spd3303.write("*RCL ", str(storage))
        time.sleep(0.1)

    # get system version
    def spd3303_get_system_version(self):
        self.spd3303.write("SYSTem:VERSion?")
        time.sleep(0.05)
        return self.spd3303.read()

    # Get device status
    def spd3303_get_sys_status(self):
        self.spd3303.write("SYSTem:STATus?")
        time.sleep(0.02)
        status_hex = self.spd3303.read()
        #print("System Status => " + status_hex)

        status = int(status_hex, base=16)

        # if (status == 4):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 OFF;\n0: CH2 OFF;")
        # elif (status == 8):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Parallel mode;\n0: CH1 OFF;\n0: CH2 OFF;")
        # elif (status == 10):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Parallel mode;\n0: CH1 OFF;\n0: CH2 OFF;")
        # elif (status == 12):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Series mode;\n0: CH1 OFF;\n0: CH2 OFF;")
        # elif (status == 21):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 OFF;")
        # elif (status == 38):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 OFF;\n0: CH2 ON;")
        # elif (status == 52):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 53):
        #     print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 54):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 55):
        #     print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 58):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 59):
        #     print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n1: CH2 CC mode;\n01: Parallel mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 60):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 61):
        #     print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n0: CH2 CV mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 62):
        #     print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
        # elif (status == 63):
        #     print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n1: CH2 CC mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
        # else:
        #     print("Invalid device status code!")

        return status
