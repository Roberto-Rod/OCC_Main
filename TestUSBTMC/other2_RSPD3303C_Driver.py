
"""Pachymeter Automated Software Verification Rig SPD3303C Power Supply test Harness"""

from pickle import FALSE, TRUE
#from pickletools import OpcodeInfo
from datetime import datetime, timedelta
import time
import csv
from SPD3303C_Driver import SPD330Class


if __name__ == '__main__':
    """"""
    # request tester's name
    print("Please enter your first name:")
    first_name = input()
    print("Please enter your last name:")
    last_name = input()
    tester_name = first_name + "_" + last_name

    # Request the test protocol reference
    print("Please enter the protocol reference:")
    protocol_ref = input()
    
    # Connect to SPD3303
    spd3303_con = SPD330Class()

    # get system version
    print("SPD3303C Power Supply Firmware version: " + spd3303_con.spd3303_get_system_version())

    # Take note of time
    test_start_time = datetime.now()
    print("Test started!")
    print(test_start_time)
    #print("Test started!")

    # Set channel 1 with V = 5 and I = 0.5
    voltCH1 = 5.35
    currCH1 = 0.1
    #spd3303_con.spd3303_CH1_configure_VC(voltCH1, currCH1)

    # Set channel 2 with V = 3 and I = 1
    voltCH2 = 3.75
    currCH2 = 1
    #spd3303_con.spd3303_CH2_configure_VC(voltCH2, currCH2)

    # Configure operation mode
    # {0[Independent] | 1[Series] | 2[Parallel]}
    mod = 1
    spd3303_con.spd3303_configure_operation_mode(mod)

    # # Configure both channels
    spd3303_con.spd3303_CH1_and_CH2_configure_VC(voltCH1, currCH1, voltCH2, currCH2)

    # Turn ON channel 1 and channel 2 ON 
    spd3303_con.spd3303_CH1_turn_ON()
    spd3303_con.spd3303_CH2_turn_ON()

    # Prepare a file to record the results
    header = ['Time', 'CH1 Current (A)', 'CH1 Voltage (V)', 'CH2 Current (A)', 'CH2 Voltage (V)']
    date = datetime.now().strftime("%Y_%m_%d")
    #with open(tester_name + date + '_Testfile.csv','w', encoding='UTF8', newline='') as csvfile:
    with open(tester_name + "_" + protocol_ref + "_"  + date + '.csv','w', encoding='UTF8', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(header)

        # Measure the voltage and current on both channel for 2 seconds
        measure_duration = 10
        measure_start_time = datetime.now()
        while datetime.now() < (measure_start_time + timedelta(seconds=measure_duration)):

            print(datetime.now())
            
            # Measure currrent on channel 1
            CH1current = spd3303_con.spd3303_measure_current("CH1")
            #print("CH1 Current: " + CH1current)
            CH1voltage = spd3303_con.spd3303_measure_voltage("CH1")
            #print("CH1 Voltage: " + CH1voltage)

            # Measure currrent on channel 2
            CH2current = spd3303_con.spd3303_measure_current("CH2")
            #print("CH2 Current: " + CH2current)  
            CH2voltage = spd3303_con.spd3303_measure_voltage("CH2")
            #print("CH2 Voltage: " + CH2voltage)

            writer.writerow([datetime.now(), CH1current, CH1voltage, CH2current, CH2voltage]) 
            csvfile.flush()

            # Wait
            time.sleep(0.1)

    # Turn OFF channel 1 and channel 2
    spd3303_con.spd3303_CH1_turn_OFF()
    spd3303_con.spd3303_CH2_turn_OFF()

    # Check test duration
    test_end_time = datetime.now()
    print("Test duration = " + str(test_end_time - test_start_time) + " seconds.")

    # Close connection with device
    spd3303_con.spd3303_close_connection()


