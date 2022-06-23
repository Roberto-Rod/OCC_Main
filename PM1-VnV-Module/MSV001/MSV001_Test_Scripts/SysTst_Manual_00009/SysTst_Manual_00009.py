
from datetime import datetime
from pickle import FALSE, NONE, TRUE

import os
import sys
import pandas as pd
import numpy as np


class SysTst_Manual_00009(object):
    """
        This class implements the SysTst_Manual_00009 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        self.timeout_limit = 10.0
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00009/SysTst_Manual_00009" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00009 Test\n"

        # Take note of date and time
        self.test_start_time = datetime.now().strftime("%d/%m/%Y, %H:%M:%S")
        self.line1 = "\nDate: " + self.test_start_time
        # date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")

        # request tester's name
        print("Please enter your name:\n")
        self.tester_name = input()
        self.line2 = "\nTester Name: " + self.tester_name

        # request HW version
        print("Please enter the hardware version:\n")
        self.hw_version = input()
        self.line3 = "\nHardware Version: " + self.hw_version

        # request LSC SW version
        print("Please enter the LSC Controller SW version:\n")
        self.LSC_sw_version = input()
        self.line4 = "\nLSC Controller SW version: " + self.LSC_sw_version

        # request PDA SW version
        print("Please enter the PDA Controller SW version:\n")
        self.PDA_sw_version = input()
        self.line5 = "\nPDA Controller SW version: " + self.PDA_sw_version

        # request PE SW version
        print("Please enter the PE Controller SW version:\n")
        self.PE_sw_version = input()
        self.line6 = "\nPE Controller SW version: " + self.PE_sw_version

        # request PI SW version
        print("Please enter the PI Controller SW version:\n")
        self.PI_sw_version = input()
        self.line7 = "\nPI Controller SW version: " + self.PI_sw_version

        with open(self.test_report_file, 'w') as f:
            self.header = [self.title, self.line1, self.line2, self.line3, self.line4, self.line5, self.line6, self.line7]
            f.writelines(self.header)
        f.close()

    def check_test_log_folder_exists(self):
        """
            This function checks if the test report folder exists and creates it if it does not.
        """

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00009"

        if not os.path.isdir(self.MSV001_log_folder_dir):
            print("MSV001_Logs does not exist. Creating directory...")

            try:
                os.makedirs(self.MSV001_log_folder_dir)
            except OSError as error:
                print(error)

    def check_prerequisits_are_met(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.prerequisits_met = ''
            print("\nHave the test prerequisits been met? Please type y or n (yes or no): ")
            self.prerequisits_met = input()
            if not (self.prerequisits_met == "y" or self.prerequisits_met == "Y"):
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00009.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close() 


    def check_dut_is_powered_on(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_on = ''
            print("\nPerform a short button press and ensure PM1 DUT powers up. Verify is PM1 DUT POWERED_ON? Please type y or n (yes or no): ")      
            self.dut_power_on =  input()
            if not (self.dut_power_on == "y" or self.dut_power_on == "Y"):
                print("SysTst_Manual_00009 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00009 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00009 Power ON Test : PASS")   

        # close test report file
        f.close()  


    def check_dut_is_powered_off(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_off = ''
            print("\nPerform a long button press and ensure PM1 DUT powers down. Verify PM1 DUT POWERED_OFF? Please type y or n (yes or no): ")    
            self.dut_power_off =  input()
            if not (self.dut_power_off == "y" or self.dut_power_off == "Y"):
                print("SysTst_Manual_00009 Power OFF Test : FAIL")
                f.write("\nSysTst_Manual_00009 Power OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 Power OFF Test : PASS")
                f.write("\nSysTst_Manual_00009 Power OFF Test : PASS")    

        # close test report file
        f.close() 


    def check_main_screen_is_displayed(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check the camera is active
            self.dut_status = ''
            print("\nVerify that: The camera is active and displaying images? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00009 Camera Active Test : FAIL")
                f.write("\nSysTst_Manual_00009 Camera Active Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 Camera Active Test : PASS")
                f.write("\nSysTst_Manual_00009 Camera Active Test : PASS")   
            
            # Check the scan button
            self.dut_status = ''
            print("\nVerify that: The scan button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00009 Scan Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00009 Scan Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 Scan Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00009 Scan Button Displayed Test : PASS")
            
            # Check the settings button
            self.dut_status = ''
            print("\nVerify that: The settings button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00009 Settings Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00009 Settings Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 Settings Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00009 Settings Button Displayed Test : PASS")
            
            # Check the charge level indicator
            self.dut_status = ''
            print("\nVerify that: The charge level indicator is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00009 Charge Level Indicator Test : FAIL")
                f.write("\nSysTst_Manual_00009 Charge Level Indicator Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 Charge Level Indicator Test : PASS")
                f.write("\nSysTst_Manual_00009 Charge Level Indicator Test : PASS")
    
        # close test report file
        f.close() 
    
    def check_read_file_matches_written_file(self) -> NONE:
        """
        
        """

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Get the file which was sent to be written to EEPROM  
            written_file = pd.read_csv("C:\Occuity\EEPROM\eeprom_data_for_upload.csv",header=None)
            # Select only the portion of data that is written to EEPROM (starts at column 6)
            written_file = written_file.iloc[:,6:]
            # print(written_file)

            # Get the file which was read from the EEPROM
            read_file = pd.read_csv("C:\Occuity\EEPROM\eeprom_data_downloaded.csv",header=None)
            # Select only the portion of data that is written to EEPROM (starts at column 6)
            read_file = read_file.iloc[:,6:]
            # print(read_file)

            diff_df = written_file.compare(read_file)
            if diff_df.empty == True:
                print("SysTst_Manual_00009 EEPROM File Check Test - files match: PASS")
                f.write("\nSysTst_Manual_00009 EEPROM File Check Test - files match: PASS")
            else:
                print("SysTst_Manual_00009 EEPROM File Check Test - files do NOT match: FAIL")
                f.write("\nSysTst_Manual_00009 EEPROM File Check Test - files do NOT match: FAIL")

            diff_df = np.where(written_file[:] == read_file[:], True, False)
            diff_df = pd.DataFrame(diff_df)
            diff_df.to_csv (r'C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00009/SysTst_Manual_00009_EEPROM.csv', index = None, header=None)
            # print(diff_df)

        # close test report file
        f.close()

    def check_dcs_tool_has_written_and_read_eeprom(self) -> None:

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_status =  ''
            print("Follow step 4 in MSV-001 Test Protocol - Ensure DCS tool reports 'EEPROM saved and verified OK'...")
            print("DCS tool reported EEPROM saved and verified OK? Please type y or n (yes or no):")
            self.dut_status =  input()

            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00009 EEPROM Verification Test : FAIL")
                f.write("\nSysTst_Manual_00009 EEPROM Verification Test : FAIL")
                f.write("\n\nSysTst_Manual_00009 EEPROM Verification Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00009 EEPROM Verification Test : PASS")
                f.write("\nSysTst_Manual_00009 EEPROM Verification Test : PASS")

        # close test report file
        f.close()


if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00009
    """

    # Instantiate a test object
    man_sys_tst_009 = SysTst_Manual_00009()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_009.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_009.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_009.check_prerequisits_are_met()

    # Ensure DUT is ON 
    man_sys_tst_009.check_dut_is_powered_on()

    # Check the main screen is displayed - step [3]
    man_sys_tst_009.check_main_screen_is_displayed()

    # Use DCS tool to write and read EEPROM, ensure this has been done bwfore continuing  - step [4] 
    man_sys_tst_009.check_dcs_tool_has_written_and_read_eeprom()

    # Check the files written and read are a match - step [5]
    man_sys_tst_009.check_read_file_matches_written_file()

    # Ensure DUT is OFF - step [6]
    man_sys_tst_009.check_dut_is_powered_off()

    # If we got this far, the test is complete and has passed - step [7]
    # Open test report file
    with open(man_sys_tst_009.test_report_file, 'a') as f:

        # Test complete
        f.write("\n\nSysTst_Manual_00009 Test Complete : PASS") 
        print("\n\nSysTst_Manual_00009 Test Complete : PASS") 
    # close test report file
    f.close()

   