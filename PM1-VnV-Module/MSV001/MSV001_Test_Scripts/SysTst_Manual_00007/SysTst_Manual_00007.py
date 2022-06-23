
from datetime import datetime
from pickle import FALSE, NONE, TRUE

import os
import sys

from numpy import int16


class SysTst_Manual_00007(object):
    """
        This class implements the SysTst_Manual_00007 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        self.timeout_limit = 10.0
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00007/SysTst_Manual_00007" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00007 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00007"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00007.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
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
                print("SysTst_Manual_00007 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00007 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00007 Power ON Test : PASS")   

        # close test report file
        f.close()  


    def check_dut_is_powered_off(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_off = ''
            print("\nPerform a long button press and ensure PM1 DUT powers down. Verify PM1 DUT POWERED_OFF? Please type y or n (yes or no): ")    
            self.dut_power_off =  input()
            if not (self.dut_power_off == "y" or self.dut_power_off == "Y"):
                print("SysTst_Manual_00007 Power OFF Test : FAIL")
                f.write("\nSysTst_Manual_00007 Power OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Power OFF Test : PASS")
                f.write("\nSysTst_Manual_00007 Power OFF Test : PASS")    

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
                print("SysTst_Manual_00007 Camera Active Test : FAIL")
                f.write("\nSysTst_Manual_00007 Camera Active Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Camera Active Test : PASS")
                f.write("\nSysTst_Manual_00007 Camera Active Test : PASS")   
            
            # Check the scan button
            self.dut_status = ''
            print("\nVerify that: The scan button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Scan Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Scan Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Scan Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Scan Button Displayed Test : PASS")
            
            # Check the settings button
            self.dut_status = ''
            print("\nVerify that: The settings button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Settings Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Settings Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Settings Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Settings Button Displayed Test : PASS")
            
            # Check the charge level indicator
            self.dut_status = ''
            print("\nVerify that: The charge level indicator is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Charge Level Indicator Test : FAIL")
                f.write("\nSysTst_Manual_00007 Charge Level Indicator Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Charge Level Indicator Test : PASS")
                f.write("\nSysTst_Manual_00007 Charge Level Indicator Test : PASS")
    
        # close test report file
        f.close() 
    
    def check_device_settings_option_displayed( self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Options Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Options Available Test : PASS")   
            
            # Check device settings option is removed from screen
            self.dut_status = ''
            print("\nVerify that the device settings option is removed from screen, and back to the main screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Removed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Removed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Option Removed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Option Removed Test : PASS")
     
        # close test report file
        f.close() 
    

    def check_device_settings_screen_displayed(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : PASS")   
            
            # Check device settings screen is displayed
            self.dut_status = ''
            print("\nVerify that the device settings screen is displayed with an option to modify the screen brightness levels? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
     
        # close test report file
        f.close()
    
    def check_brightness_is_reduced(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Verify that the screen brightness is reduced as the sliding bar is moved
            self.dut_status = ''
            print("\nVerify that the screen brightness is reduced as the sliding bar is moved? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : PASS")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : PASS")   
            
            # Monitor the PDA terminal (COM5) and verify it prints  “EEPROM - settings saved OK”
            self.dut_status = ''
            print("\nVerify that the “EEPROM - settings saved OK” statement was printed in COM5? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Settings Stored Test : FAIL")
                f.write("\nSysTst_Manual_00007 Settings Stored Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Stored Test : PASS")
                f.write("\nSysTst_Manual_00007 Settings Stored Test : PASS")
            
            # Check device is back on main screen
            self.dut_status = ''
            print("\nVerify that: The device is displaying the mains screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Return to Main Screen Test : PASS")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : PASS")
            
            # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : PASS")   
            
            # Check device settings screen is displayed
            self.dut_status = ''
            print("\nVerify that the device settings screen is displayed with an option to modify the screen brightness levels? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
            
            # Check setting were stored
            self.dut_status = ''
            print("\nVerify that the screen brightness levels are set to the minimum value as per step [7]? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Store Minimum Brightness Settings Test : FAIL")
                f.write("\nSysTst_Manual_00007 Store Minimum Brightness Settings Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Store Minimum Brightness Settings Test : PASS")
                f.write("\nSysTst_Manual_00007 Store Minimum Brightness Settings Test : PASS")   

        # close test report file
        f.close()
    
    def check_brightness_is_increased(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Verify that the screen brightness is increased as the sliding bar is moved
            self.dut_status = ''
            print("\nVerify that the screen brightness is increased as the sliding bar is moved? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : PASS")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : PASS")   
            
            # Monitor the PDA terminal (COM5) and verify it prints  “EEPROM - settings saved OK”
            self.dut_status = ''
            print("\nVerify that the “EEPROM - settings saved OK” statement was printed in COM5? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
            
            # Check device is back on main screen
            self.dut_status = ''
            print("\nVerify that: The device is displaying the mains screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Return to Main Screen Test : PASS")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : PASS")
            
            # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : PASS")   
            
            # Check device settings screen is displayed
            self.dut_status = ''
            print("\nVerify that the device settings screen is displayed with an option to modify the screen brightness levels? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
            
            # Check setting were stored
            self.dut_status = ''
            print("\nVerify that the screen brightness levels are set to the maximum value as per step [9]? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Store Minimum Brightness Settings Test : FAIL")
                f.write("\nSysTst_Manual_00007 Store Minimum Brightness Settings Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Store Minimum Brightness Settings Test : PASS")
                f.write("\nSysTst_Manual_00007 Store Minimum Brightness Settings Test : PASS")   

        # close test report file
        f.close()
    
    
    def check_cancelling_settings(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Verify that the screen brightness is reduced as the sliding bar is moved
            self.dut_status = ''
            print("\nVerify that the screen brightness is reduced as the sliding bar is moved? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : PASS")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : PASS")   
            
            # Monitor the PDA terminal (COM5) and verify it does NOT prints  “EEPROM - settings saved OK”
            self.dut_status = ''
            print("\nVerify that the “EEPROM - settings saved OK” statement was NOT printed in COM5? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Settings NOT Stored Test : FAIL")
                f.write("\nSysTst_Manual_00007 Settings NOT Stored Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Settings NOT Stored Test : PASS")
                f.write("\nSysTst_Manual_00007 Settings NOT Stored Test : PASS")
            
            # Check device is back on main screen
            self.dut_status = ''
            print("\nVerify that: The device is displaying the mains screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Return to Main Screen Test : PASS")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : PASS")
            
            # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : PASS")   
            
            # Check device settings screen is displayed
            self.dut_status = ''
            print("\nVerify that the device settings screen is displayed with an option to modify the screen brightness levels? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
            
            # Check setting were NOT stored
            self.dut_status = ''
            print("\nVerify that the screen brightness levels are set to the maximum value as per step [9]? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Check Settings NOT Stored Test : FAIL")
                f.write("\nSysTst_Manual_00007 Check Settings NOT Stored Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Check Settings NOT Stored Test : PASS")
                f.write("\nSysTst_Manual_00007 Check Settings NOT Stored Test : PASS")   

        # close test report file
        f.close()
    
    def check_brightness_is_midlevel_through_power_cycle(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Verify that the screen brightness is reduced as the sliding bar is moved
            self.dut_status = ''
            print("\nVerify that the screen brightness is reduced as the sliding bar is moved? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Brightness Sliding Bar Test : PASS")
                f.write("\nSysTst_Manual_00007 Brightness Sliding Bar Test : PASS")   
            
            # Monitor the PDA terminal (COM5) and verify it prints  “EEPROM - settings saved OK”
            self.dut_status = ''
            print("\nVerify that the “EEPROM - settings saved OK” statement was printed in COM5? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Mid-level Settings Stored Test : FAIL")
                f.write("\nSysTst_Manual_00007 Mid-level Settings Stored Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Mid-level Settings Stored Test : PASS")
                f.write("\nSysTst_Manual_00007 Mid-level Settings Stored Test : PASS")
            
            # Check device is back on main screen
            self.dut_status = ''
            print("\nVerify that: The device is displaying the main screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Return to Main Screen Test : PASS")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : PASS")
            
            # Ensure DUT is OFF - step [12]
            self.check_dut_is_powered_off()
            
            # Ensure DUT is ON - step [12]
            self.check_dut_is_powered_on()

            # Check the main screen is displayed correctly - step [12]
            self.check_main_screen_is_displayed()
        
        # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Option Available Test : PASS")   
            
            # Check device settings screen is displayed
            self.dut_status = ''
            print("\nVerify that the device settings screen is displayed with an option to modify the screen brightness levels? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
                f.write("\nSysTst_Manual_00007 Device Settings Screen Displayed Test : PASS")
            
            # Check setting were stored
            self.dut_status = ''
            print("\nVerify that the screen brightness levels are set to the mid-level value as per step [13]? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Store Mid-level Brightness Settings Test : FAIL")
                f.write("\nSysTst_Manual_00007 Store Mid-level Brightness Settings Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Store Mid-level Brightness Settings Test : PASS")
                f.write("\nSysTst_Manual_00007 Store Mid-level Brightness Settings Test : PASS") 
            
            # Check device is back on main screen step [16]
            self.dut_status = ''
            print("\nVerify that: The device is displaying the main screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Return to Main Screen Test : PASS")
                f.write("\nSysTst_Manual_00007 Return to Main Screen Test : PASS")

        # close test report file
        f.close()

    def check_extended_settings_menu(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that ONLY the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 ONLY Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 ONLY Device Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 ONLY Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 ONLY Device Settings Option Available Test : PASS")
        
            # Check USB cable is connected
            retries = 0
            print("Is the USB cable connected between PC and CN2 on PM1 PCBA? Please type y or n (yes or no): ")
            reply = input()
            retries += 1

            while not (reply == "y" or reply == "Y" or retries >= 3):
                print("Is the USB cable connected between PC and CN2 on PM1 PCBA? Please type y or n (yes or no): ")
                reply = input()
                retries += 1

            # Check extended menu options are available
            self.dut_status = ''
            print("\nVerify that extended settings options are made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Extended Settings Options Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Extended Settings Options Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Extended Settings Options Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Extended Settings Options Available Test : PASS")

            # Check USB cable is disconnected
            retries = 0
            print("Is the USB cable disconnected from CN2 on PM1 PCBA? Please type y or n (yes or no): ")
            reply = input()
            retries += 1

            while not (reply == "y" or reply == "Y" or retries >= 3):
                print("Is the USB cable disconnected from CN2 on PM1 PCBA? Please type y or n (yes or no): ")
                reply = input()
                retries += 1
            
             # Check device settings option is made available on screen
            self.dut_status = ''
            print("\nVerify that ONLY the device settings option is made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 ONLY Device Settings Option Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 ONLY Device Option Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 ONLY Device Settings Option Available Test : PASS")
                f.write("\nSysTst_Manual_00007 ONLY Device Settings Option Available Test : PASS")
        
            # Check USB cable is connected
            retries = 0
            print("Is the USB cable connected between PC and CN2 on PM1 PCBA? Please type y or n (yes or no): ")
            reply = input()
            retries += 1

            while not (reply == "y" or reply == "Y" or retries >= 3):
                print("Is the USB cable connected between PC and CN2 on PM1 PCBA? Please type y or n (yes or no): ")
                reply = input()
                retries += 1

            # Check extended menu options are available
            self.dut_status = ''
            print("\nVerify that extended settings options are made available on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00007 Extended Settings Options Available Test : FAIL")
                f.write("\nSysTst_Manual_00007 Extended Settings Options Available Test : FAIL")
                f.write("\n\nSysTst_Manual_00007 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00007 Extended Settings Options Available Test : PASS")
                f.write("\nSysTst_Manual_00007 Extended Settings Options Available Test : PASS")

        # close test report file
        f.close()


if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00007
    """

    # Instantiate a test object
    man_sys_tst_007 = SysTst_Manual_00007()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_007.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_007.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_007.check_prerequisits_are_met()

    # Ensure DUT is ON 
    man_sys_tst_007.check_dut_is_powered_on()

    # Check the main screen is displayed correctly - step [3]
    man_sys_tst_007.check_main_screen_is_displayed()

    # Check device settings option is available/removed with LCD_TAP - steps [4] and [5] 
    man_sys_tst_007.check_device_settings_option_displayed()

    # Check we can enter the device settings screen 
    man_sys_tst_007.check_device_settings_screen_displayed()

    # Check we can reduce LCD brightness
    man_sys_tst_007.check_brightness_is_reduced()

    # Check we can increase LCD brightness
    man_sys_tst_007.check_brightness_is_increased()

    # Check we can cancel the settings change
    man_sys_tst_007.check_cancelling_settings()

    # Check we can set brightness to mid level and remember settings through power cycle
    man_sys_tst_007.check_brightness_is_midlevel_through_power_cycle()

    # Check extended settings when USB is connected to CN2 - steps [17] to [20]
    man_sys_tst_007.check_extended_settings_menu()

    # Ensure DUT is OFF - step [21]
    man_sys_tst_007.check_dut_is_powered_off()

    # If we got this far, the test is complete and has passed - step [13]
    # Open test report file
    with open(man_sys_tst_007.test_report_file, 'a') as f:

        # Test complete
        f.write("\n\nSysTst_Manual_00007 Test Complete : PASS") 
        print("\n\nSysTst_Manual_00007 Test Complete : PASS") 
    # close test report file
    f.close()

   