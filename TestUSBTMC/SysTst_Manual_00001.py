#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, occuity Limited <roberto.rodrigues@occuity.com>
# All rights reserved.
#


from cmath import pi
from datetime import datetime
from pickle import FALSE, NONE, TRUE
from tkinter import Tk, filedialog
import sys

# Define the code and data space limits for all microcontrollers
dsPIC33CK128MP203_code_limit    = 0x19999
PIC32MZ1024EFH100_code_limit    = 0xCCCCC
PIC24FJ64GA702_code_limit       = 0x19999
PIC32MZ2064DAR169_code_limit    = 0x199999
dsPIC33CK128MP203_data_limit    = 0x3999
PIC32MZ1024EFH100_data_limit    = 0x73333
PIC24FJ64GA702_data_limit       = 0x3999
PIC32MZ2064DAR169_data_limit    = 0x90000



def get_project_folder_path():
    """ 
        This function retrieves the location of the project folder paths
    """
    root = Tk() # pointing root to Tk() to use it as Tk() in program.
    root.withdraw() # Hides small tkinter window.
    ''
    root.attributes('-topmost', True) # Opened windows will be active. above all windows despite of selection.
    ''
    open_file = filedialog.askdirectory() # Returns opened path as str
    print(open_file)
    return open_file


def test_code_space_usage(lsc_path, pda_path, pe_path, pi_path):

    with open(test_report_file, 'a') as f:

        # # LSC project
        # print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
        # lsc_path = get_project_folder_path()
        print("\nVerifying SRS-003 Program memory size for dsPIC33CK128MP203...")
        f.write("\n\nVerifying SRS-003 Program memory size for dsPIC33CK128MP203...")
        with open(lsc_path + '/dist/default/production/LSC_Firmware.X.production.map') as file:
            for line in file:
                if (line.startswith("""                 Total "program" memory used (bytes):         """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-4])

                    code_space = int(line[-4], base=16)

                    try:
                        assert(code_space < dsPIC33CK128MP203_code_limit), 'FAIL. Code space exceeded for dsPIC33CK128MP203'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Code space exceeded for dsPIC33CK128MP203: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()

        # # PDA project
        # print("Please navigate to the Firmware.X folder for the PDA MPLAB project using the dialog box.")
        # pda_path = get_project_folder_path()
        print("Verifying SRS-003 Program memory size for PIC32MZ1024EFH100...")
        f.write("\nVerifying SRS-003 Program memory size for PIC32MZ1024EFH100...")
        with open(pda_path + '/dist/PIC32MZ2048EFH100/production/PDAB_Firmware.X.production.map') as file:
            for line in file:
                if (line.startswith("""         Total Program Memory used  :     """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-11])

                    code_space = int(line[-11], base=16)

                    try:
                        assert(code_space < PIC32MZ1024EFH100_code_limit), 'FAIL. Code space exceeded for PIC32MZ1024EFH100'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Code space exceeded for PIC32MZ1024EFH100: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()

        # # PE project
        # print("Please navigate to the Firmware.X folder for the PE MPLAB project using the dialog box.")
        # pe_path = get_project_folder_path()
        print("Verifying SRS-003 Program memory size for PIC24FJ64GA702...")
        f.write("\nVerifying SRS-003 Program memory size for PIC24FJ64GA702...")
        with open(pe_path + '/dist/default/production/Environment-Firmware.X.production.map') as file:
            for line in file:
                if (line.startswith("""                 Total "program" memory used (bytes):         """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-4])

                    code_space = int(line[-4], base=16)

                    try:
                        assert(code_space < PIC24FJ64GA702_code_limit), 'FAIL. Code space exceeded for PIC24FJ64GA702'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Code space exceeded for PIC24FJ64GA702: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()

        # # PI project
        # print("Please navigate to the Firmware.X folder for the PI MPLAB project using the dialog box.")
        # pi_path = get_project_folder_path()
        print("Verifying SRS-003 Program memory size for PIC32MZ2064DAR169...")
        f.write("\nVerifying SRS-003 Program memory size for PIC32MZ2064DAR169...")
        with open(pi_path + '/dist/Main_Board_Rev_C/production/PIB_Firmware.X.production.map') as file:
            for line in file:
               if (line.startswith("""         Total Program Memory used  :     """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-11])

                    code_space = int(line[-11], base=16)

                    try:
                        assert(code_space < PIC32MZ2064DAR169_code_limit), 'FAIL. Code space exceeded for PIC32MZ2064DAR169'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Code space exceeded for PIC32MZ2064DAR169: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()
        f.write("\nProgram Memory Test PASSED.")
    # Close test report file
    f.close()
    return TRUE

def test_data_space_usage(lsc_path, pda_path, pe_path, pi_path):

    with open(test_report_file, 'a') as f:

        # LSC project
        print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
        # lsc_path = get_project_folder_path()
        print("Verifying SRS-004 Data memory size for dsPIC33CK128MP203...")
        f.write("\n\nVerifying SRS-004 Data memory size for dsPIC33CK128MP203...")
        with open(lsc_path + '/dist/default/production/LSC_Firmware.X.production.map') as file:
            for line in file:
                if (line.startswith("""                 Total "data" memory used (bytes):         """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-4])

                    code_space = int(line[-4], base=16)

                    try:
                        assert(code_space < dsPIC33CK128MP203_data_limit), 'FAIL. Data memory space exceeded for dsPIC33CK128MP203'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Data memory space exceeded for dsPIC33CK128MP203: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()

        # PDA project
        print("Please navigate to the Firmware.X folder for the PDA MPLAB project using the dialog box.")
        # pda_path = get_project_folder_path()
        print("Verifying SRS-004 Data memory size for PIC32MZ1024EFH100...")
        f.write("\nVerifying SRS-004 Data memory size for PIC32MZ1024EFH100...")
        with open(pda_path + '/dist/PIC32MZ2048EFH100/production/PDAB_Firmware.X.production.map') as file:
            for line in file:
                if (line.startswith("""            Total Data Memory used  :     """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-11])

                    code_space = int(line[-11], base=16)

                    try:
                        assert(code_space < PIC32MZ1024EFH100_data_limit), 'FAIL. Data memory space exceeded for PIC32MZ1024EFH100'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Data memory space exceeded for PIC32MZ1024EFH100: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()

        # PE project
        print("Please navigate to the Firmware.X folder for the PE MPLAB project using the dialog box.")
        # pe_path = get_project_folder_path()
        print("Verifying SRS-004 Data memory size for PIC24FJ64GA702...")
        f.write("\nVerifying SRS-004 Data memory size for PIC24FJ64GA702...")
        with open(pe_path + '/dist/default/production/Environment-Firmware.X.production.map') as file:
            for line in file:
                if (line.startswith("""                 Total "data" memory used (bytes):         """)):
                    #print(line)
                    line = line.split(' ')
                    #print(line[-4])

                    code_space = int(line[-4], base=16)

                    try:
                        assert(code_space < PIC24FJ64GA702_data_limit), 'FAIL. Data memory space exceeded for PIC24FJ64GA702'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Data memory space exceeded for PIC24FJ64GA702: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()

        # PI project
        print("Please navigate to the Firmware.X folder for the PE MPLAB project using the dialog box.")
        # pi_path = get_project_folder_path()
        print("Verifying SRS-004 Data memory size for PIC32MZ2064DAR169...")
        f.write("\nVerifying SRS-004 Data memory size for PIC32MZ2064DAR169...")
        with open(pi_path + '/dist/Main_Board_Rev_C/production/PIB_Firmware.X.production.map') as file:
            for line in file:
               if (line.startswith("""            Total Data Memory used  :     """)):
                    # print(line)
                    line = line.split(' ')
                    # print(line[-11])

                    code_space = int(line[-11], base=16)

                    try:
                        assert(code_space < PIC32MZ2064DAR169_data_limit), 'FAIL. Data memory space exceeded for PIC32MZ2064DAR169'
                        print("PASS")
                        f.write("\nPASS")
                    except AssertionError as error:
                        f.write("\nFAIL - Data memory space exceeded for PIC32MZ2064DAR169: " + str(code_space))
                        print(error)
                        # Close test report file
                        f.close()
                        return FALSE
        # Close memory map file
        file.close()
        f.write("\nData Memory Test PASSED.")
    # Close test report file
    f.close()
    return TRUE

def get_test_report_header_details():
    """
        This function creates a test report text file
    """
    # Title line
    title = "Software Verification Specification SV001 - SysTst_Manual_00001 Test\n"

    # Take note of date and time
    test_start_time = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
    line1 = "\nDate: " + test_start_time
    # date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")

    # request tester's name
    print("Please enter your name:\n")
    tester_name = input()
    line2 = "\nTester Name: " + tester_name

    # request HW version
    print("Please enter the hardware version:\n")
    hw_version = input()
    line3 = "\nHardware Version: " + hw_version

    # request PE SW version
    print("Please enter the PE Controller SW version:\n")
    PE_sw_version = input()
    line4 = "\nPE Controller SW version: " + PE_sw_version

    # request PI SW version
    print("Please enter the PI Controller SW version:\n")
    PI_sw_version = input()
    line5 = "\nPI Controller SW version: " + PI_sw_version

    # request PDA SW version
    print("Please enter the PDA Controller SW version:\n")
    PDA_sw_version = input()
    line6 = "\nPDA Controller SW version: " + PDA_sw_version

    # request LSC SW version
    print("Please enter the LSC Controller SW version:\n")
    LSC_sw_version = input()
    line7 = "\nLSC Controller SW version: " + LSC_sw_version

    with open(test_report_file, 'w') as f:
        header = [title, line1, line2, line3, line4, line5, line6, line7]
        f.writelines(header)
    f.close()


# # Define the code and data space limits for all microcontrollers
# dsPIC33CK128MP203_code_limit    = 0x19999
# PIC32MZ1024EFH100_code_limit    = 0xCCCCC
# PIC24FJ64GA702_code_limit       = 0x19999
# PIC32MZ2064DAR169_code_limit    = 0x199999
# dsPIC33CK128MP203_data_limit    = 0x3999
# PIC32MZ1024EFH100_data_limit    = 0x73333
# PIC24FJ64GA702_data_limit       = 0x3999
# PIC32MZ2064DAR169_data_limit    = 0x90000

date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
test_report_file = "./../SV001/SV001_Logs/SysTst_Manual_00001_" + date + ".txt"

if __name__ == '__main__':

    #
    lsc_path = NONE
    pda_path = NONE
    pe_path  = NONE
    pi_path  = NONE

    # Create the test report file
    get_test_report_header_details()

    # get project folder paths
    file_box_count = 0
    # LSC project
    print("lsc_path = " + str(lsc_path))
    while (lsc_path == NONE or lsc_path == '') and file_box_count < 3:
        print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
        lsc_path = get_project_folder_path()
        file_box_count += 1
    print("lsc_path = " + str(lsc_path))
    if (lsc_path == NONE or lsc_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        # PDA project
        print("pda_path = " + str(pda_path))
        while (pda_path == NONE or pda_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PDA MPLAB project using the dialog box.")
            pda_path = get_project_folder_path()
            file_box_count += 1

    if (pda_path == NONE or pda_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        print("pe_path = " + str(pe_path))
        # PE project
        while (pe_path == NONE or pe_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PE MPLAB project using the dialog box.")
            pe_path = get_project_folder_path()
            file_box_count += 1

    if (pe_path == NONE or pe_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        print("pi_path = " + str(pi_path))
        # PI project
        while (pi_path == NONE or pi_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PI MPLAB project using the dialog box.")
            pi_path = get_project_folder_path()
            file_box_count += 1

    if (pi_path == NONE or pi_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()

    # Check code and data space
    if test_code_space_usage(lsc_path, pda_path, pe_path, pi_path) == TRUE and test_data_space_usage(lsc_path, pda_path, pe_path, pi_path) == TRUE:
        print("\nSysTst_Manual_00001 Test Complete: PASS")
        with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00001 Test Complete: PASS")
        f.close()
    else:
        print("\nSysTst_Manual-00001 Test Complete: FAIL")
        with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00001 Test Complete: FAIL")
        f.close()

