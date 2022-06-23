#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, occuity Limited <roberto.rodrigues@occuity.com>
# All rights reserved.
#


"""Pachymeter Automated Software Verification Rig SPD3303C Power Supply test Harness"""

from pickle import FALSE, TRUE
#import pickletools
from datetime import datetime, timedelta
import time
import csv
from framework.module.SPD3303C_Driver import SPD330Class


if __name__ == '__main__':
    """"""
    # request tester's name
    print("Please enter your name without any spaces:\n")
    tester_name = input()

    # Connect to SPD3303
    spd3303_con = SPD330Class()

    # get system version
    print("SPD3303C Power Supply Firmware version: " + spd3303_con.spd3303_get_system_version())

    # Take note of time
    test_start_time = datetime.now()
    print("Test started: " + str(test_start_time))
    # Get system status
    # status = spd3303_con.spd3303_get_sys_status()
    #print("Device status: " + str(status))

    # # Get system error
    # error =  spd3303_con.spd3303_get_sys_error()
    # print("\nDevice error: " + error)

    # Set channel 1 with V = 5 and I = 0.5
    voltCH1 = 7.5
    currCH1 = 0.7
    #spd3303_con.spd3303_CH1_configure_VC(voltCH1, currCH1)

    # Set channel 2 with V = 3 and I = 1
    voltCH2 = 3.75
    currCH2 = 1
    #spd3303_con.spd3303_CH2_configure_VC(voltCH2, currCH2)

    # Configure operation mode
    # {0[Independent] | 1[Series] | 2[Parallel]}
    mod = 0
    spd3303_con.spd3303_configure_operation_mode(mod)

    # # Configure both channels
    # spd3303_con.spd3303_CH1_and_CH2_configure_VC(voltCH1, currCH1, voltCH2, currCH2)

    # Configure channel 1 only
    spd3303_con.spd3303_CH1_configure_VC(voltCH1, currCH1)

    # Turn ON channel 1 and channel 2 ON
    spd3303_con.spd3303_CH1_turn_ON()
    # spd3303_con.spd3303_CH2_turn_ON()

    # Prepare a file to record the results
    # header = ['Time', 'CH1 Current (A)', 'CH1 Voltage (V)', 'CH2 Current (A)', 'CH2 Voltage (V)']
    header = ['Time (s)', 'CH1 Current (A)', 'CH1 Voltage (V)']
    date = datetime.now().strftime("_%Y_%m_%d_%I_%M_%S")
    with open(tester_name + date + '_Testfile.csv','w', encoding='UTF8', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(header)

        # Measure the voltage and current on both channel for 2 seconds
        measure_duration = 600
        measure_start_time = datetime.now()
        sample_rate = 0.2
        while datetime.now() < (measure_start_time + timedelta(seconds=measure_duration)):

            # print(datetime.now())

            current_sample_t = datetime.now()
            elapsed_time = datetime.now() - measure_start_time
            print("Elapsed time: ", elapsed_time)

            # Measure currrent on channel 1
            CH1current = spd3303_con.spd3303_measure_current("CH1")
            # check and print type num variable
            # print(type(CH1current))
            #print("CH1 Current: " + CH1current)
            CH1voltage = spd3303_con.spd3303_measure_voltage("CH1")
            #print("CH1 Voltage: " + CH1voltage)

            # Measure currrent on channel 2
            # CH2current = spd3303_con.spd3303_measure_current("CH2")
            #print("CH2 Current: " + CH2current)
            # CH2voltage = spd3303_con.spd3303_measure_voltage("CH2")
            #print("CH2 Voltage: " + CH2voltage)

            # writer.writerow([datetime.now(), CH1current, CH1voltage, CH2current, CH2voltage])
            while datetime.now() < (current_sample_t + timedelta(seconds=sample_rate)):
                time.sleep(0.001)
            writer.writerow([elapsed_time, CH1current, CH1voltage])
            csvfile.flush()

            # Wait
            #time.sleep(0.01)

    # # get status
    # spd3303_con.spd3303_get_sys_status()

    # # Save current configuration is storage space 2
    # spd3303_con.spd3303_save_configuration(5)
    # time.sleep(1)

    # Turn OFF channel 1 and channel 2
    spd3303_con.spd3303_CH1_turn_OFF()
    # spd3303_con.spd3303_CH2_turn_OFF()

    # # Recall configuration 1
    # spd3303_con.spd3303_recall_configuration(1)

    # Check test duration
    test_end_time = datetime.now()
    print("Test duration = " + str(test_end_time - test_start_time) + " seconds.")

    # Close connection with device
    spd3303_con.spd3303_close_connection()

