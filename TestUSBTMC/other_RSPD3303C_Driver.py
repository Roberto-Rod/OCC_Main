
#*IDN\sNPD3ECAQ1R0177,1.02.01.01.03,V1.3\n
# Manufacturer Name:    RS
# Model Name:           RSPD3303C
# Manufacturer ID:      0x0483
# Model Code:           0x7540           
# USB Serial Number:    SDG00001130273
# Firmware Version:     1.02.01.01.03
# Hardware Version:     V1.3


"""Pachymeter Automated Software Verification Rig RSPD 3303C Power Supply Device Driver"""


from posixpath import split
import pyvisa
import time
#import binascii

rm = pyvisa.ResourceManager()
rm.list_resources()
rspd3303 = rm.open_resource('USB0::0x0483::0x7540::NPD3ECAQ1R0177::INSTR')
#print(rspd3303)
rspd3303.write("*IDN?")
time.sleep(0.1)
reply = rspd3303.read()
print("Instrument ID => " + reply)

rspd3303.write("OUTPut:TRACK 0")
time.sleep(0.1)

# rspd3303.write("OUTPut CH1, ON")
# time.sleep(0.1)
# rspd3303.write("OUTPut CH2, ON")
# time.sleep(0.1)

rspd3303.write("SYSTem:STATus?")
time.sleep(0.1)
status_hex = rspd3303.read()
#print(status_hex)

status = int(status_hex, base=16)


print(status)

if (status == 4):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 OFF;\n0: CH2 OFF;")
elif (status == 8):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Parallel mode;\n0: CH1 OFF;\n0: CH2 OFF;")
elif (status == 10):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Parallel mode;\n0: CH1 OFF;\n0: CH2 OFF;")
elif (status == 12):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Series mode;\n0: CH1 OFF;\n0: CH2 OFF;")
elif (status == 21):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 OFF;")
elif (status == 38):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 OFF;\n0: CH2 ON;")
elif (status == 52):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 53):
    print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n0: CH2 CV mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 54):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 55):
    print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 58):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Independent mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 59):
    print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n1: CH2 CC mode;\n01: Parallel mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 60):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n0: CH2 CV mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 61):
    print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n0: CH2 CV mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 62):
    print("Device status HEX " + status_hex + "\n0: CH1 CV mode;\n1: CH2 CC mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
elif (status == 63):
    print("Device status HEX " + status_hex + "\n1: CH1 CC mode;\n1: CH2 CC mode;\n01: Series mode;\n0: CH1 ON;\n0: CH2 ON;")
else:
    print("Invalid device status code!")   


rm.close()



