
from datetime import datetime
from pickle import FALSE, NONE, TRUE

import os
import sys

from numpy import int16


class SysTst_Manual_00005(object):
    """
        This class implements the SysTst_Manual_00005 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        self.measurement = 1
        self.measured_val = 0
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00005/SysTst_Manual_00005" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00005 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00005"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00005.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
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
                print("SysTst_Manual_00005 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00005 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00005 Power ON Test : PASS")   

        # close test report file
        f.close()  

    def check_dut_is_powered_on_after_long_press(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_on = ''
            print("\nPerform a long button press, start the timer and ensure PM1 DUT powers up." \
                  "\nStop the timer when the LRS activations stop."
                  "\nVerify PM1 DUT is POWERED_ON after the long button press? Please type y or n (yes or no): ")      
            self.dut_power_on =  input()
            if not (self.dut_power_on == "y" or self.dut_power_on == "Y"):
                print("SysTst_Manual_00005 Power ON with Long Button Press Test : FAIL")
                f.write("\nSysTst_Manual_00005 Power ON with Long Button Press Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Power ON with Long Button Press Test : PASS")
                f.write("\nSysTst_Manual_00005 Power ON with Long Button Press Test : PASS") 
            
            # Check lrs activation time
            lrs_activation_time_limit = 15.0
            print("\nPlease enter the LRS activation time duration: ")
            lrs_activation_time = float(input())

            if lrs_activation_time <= lrs_activation_time_limit:
                print("SysTst_Manual_00005 Current and Resonant Frequency Message Test : PASS")
                f.write("\nSysTst_Manual_00005 Current and Resonant Frequency Message Test : PASS")
            else:
                print("SysTst_Manual_00005 Current and Resonant Frequency Message Test : FAIL")
                f.write("\nSysTst_Manual_00005 Current and Resonant Frequency Message Test : FAIL")  

            self.dut_status = ''
            print("\nVerify that: Display turns ON (illuminated) showing loading splash screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Display ON Test : FAIL")
                f.write("\nSysTst_Manual_00005 Display ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Display ON Test : PASS")
                f.write("\nSysTst_Manual_00005 Display ON Test : PASS")  

            self.dut_status = ''
            print("\nVerify that: Version numbers are displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Version Numbers Test : FAIL")
                f.write("\nSysTst_Manual_00005 Version Numbers Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Version Numbers Test : PASS")
                f.write("\nSysTst_Manual_00005 Version Numbers Test : PASS")    
            
            self.dut_status = ''
            print("\nVerify that: LRS is Active?  Please type y or n (yes or no):")


        # close test report file
        f.close()   

    def check_dut_is_powered_off(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_off = ''
            print("\nPerform a long button press and ensure PM1 DUT powers down. Verify PM1 DUT POWERED_OFF? Please type y or n (yes or no): ")    
            self.dut_power_off =  input()
            if not (self.dut_power_off == "y" or self.dut_power_off == "Y"):
                print("SysTst_Manual_00005 Power OFF Test : FAIL")
                f.write("\nSysTst_Manual_00005 Power OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Power OFF Test : PASS")
                f.write("\nSysTst_Manual_00005 Power OFF Test : PASS")    

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
                print("SysTst_Manual_00005 Camera Active Test : FAIL")
                f.write("\nSysTst_Manual_00005 Camera Active Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Camera Active Test : PASS")
                f.write("\nSysTst_Manual_00005 Camera Active Test : PASS")   
            
            # Check the scan button
            self.dut_status = ''
            print("\nVerify that: The scan button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Scan Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00005 Scan Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Scan Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00005 Scan Button Displayed Test : PASS")
            
            # Check the settings button
            self.dut_status = ''
            print("\nVerify that: The settings button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Settings Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00005 Settings Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Settings Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00005 Settings Button Displayed Test : PASS")
            
            # Check the charge level indicator
            self.dut_status = ''
            print("\nVerify that: The charge level indicator is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Charge Level Indicator Test : FAIL")
                f.write("\nSysTst_Manual_00005 Charge Level Indicator Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Charge Level Indicator Test : PASS")
                f.write("\nSysTst_Manual_00005 Charge Level Indicator Test : PASS")
    
        # close test report file
        f.close() 
    

    def check_settings_were_retrieved(self):
        
        # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check the vstart statement
            self.dut_status = ''
            print("\nVerify that: Settings updated vstart printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Settings Updated vstart Test : FAIL")
                f.write("\nSysTst_Manual_00005 Settings Updated vstart Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Settings Updated vstart Test : PASS")
                f.write("\nSysTst_Manual_00005 Settings Updated vstart Test : PASS")   
            
            # Check the Received settings from PDAB statement
            self.dut_status = ''
            print("\nVerify that: Received settings from PDAB printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Received Settings from PDAB Test : FAIL")
                f.write("\nSysTst_Manual_00005 Received Settings from PDAB Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Received Settings from PDAB Test : PASS")
                f.write("\nSysTst_Manual_00005 Received Settings from PDAB Test : PASS")
            
        # close test report file
        f.close()
    

    def check_normal_scan_action(self):

         # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check scanning starts
            self.dut_status = ''
            print("Press the Start Scan button to initiate a scan of the test artifact.")
            print("\nVerify that: Scan starts? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Scan Start Test : FAIL")
                f.write("\nSysTst_Manual_00005 Scan Start Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Scan Start Test : PASS")
                f.write("\nSysTst_Manual_00005 Scan Start Test  PASS")   
            
            # Check Laser ON indicator is being displayed during scanning
            self.dut_status = ''
            print("\nVerify that: Laser ON indicator is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Laser ON Indicator Test : FAIL")
                f.write("\nSysTst_Manual_00005 Laser ON Indicator Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Laser ON Indicator Test : PASS")
                f.write("\nSysTst_Manual_00005 Laser ON Indicator Test : PASS")  
            
            # Check Progress bar shows scanning progress 
            self.dut_status = ''
            print("\nVerify that: Progress bar shows scanning progress? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Progress Bar Test : FAIL")
                f.write("\nSysTst_Manual_00005 Progress Bar Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Progress Bar Test : PASS")
                f.write("\nSysTst_Manual_00005 Progress Bar Test : PASS")
            
            # Check Alignment circle is shown and changes from red to green when the measurement is complete
            self.dut_status = ''
            print("\nVerify that: Alignment circle is shown and changes from red to green? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Alignment circle Shown Test : FAIL")
                f.write("\nSysTst_Manual_00005 Alignment circle Shown Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Alignment circle Shown Test : PASS")
                f.write("\nSysTst_Manual_00005 Alignment circle Shown Test : PASS")
            
            # Check Scan is complete
            self.dut_status = ''
            print("\nVerify that: Scan is complete? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Scan Complete Test : FAIL")
                f.write("\nSysTst_Manual_00005 Scan Complete Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Scan Complete Test : PASS")
                f.write("\nSysTst_Manual_00005 Scan Complete Test : PASS")
            
            # Check Alignment circle is removed from camera image
            self.dut_status = ''
            print("\nVerify that: Alignment circle is removed from camera image? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Alignment Circle Removed Test : FAIL")
                f.write("\nSysTst_Manual_00005 Alignment Circle Removed Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Alignment Circle Removed Test : PASS")
                f.write("\nSysTst_Manual_00005 Alignment Circle Removed Test : PASS")
            
            # Check Camera freezes with image when scan was performed
            self.dut_status = ''
            print("\nVerify that: Camera freezes with image when scan was performed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Camera Freezes with Image Test : FAIL")
                f.write("\nSysTst_Manual_00005 Camera Freezes with Image Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Camera Freezes with Image Test : PASS")
                f.write("\nSysTst_Manual_00005 Camera Freezes with Image Test : PASS")
            
            # Check Measurement value is displayed in green and enter the measurement as request by the prompt window
            self.dut_status = ''
            print("\nVerify that: Measurement " + str(self.measurement) + " value is displayed in green? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : FAIL")
                f.write("\nSysTst_Manual_00005 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("Please enter the value of the measurement in whole units of um (micrometres) as displayed on the PM1 screen:")
                # store the measurement to use later
                self.measured_val = int(input(),base=10)
                print("SysTst_Manual_00005 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : PASS")
                f.write("\nSysTst_Manual_00005 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : PASS")
                self.measurement += 1
 
        # close test report file
        f.close()
    
    def check_led_statements(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check SCAN BTN statement is printed
            self.dut_status = ''
            print("\nVerify that: SCAN BTN statement is printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 SCAN BTN Test : FAIL")
                f.write("\nSysTst_Manual_00005 SCAN BTN Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 SCAN BTN Test : PASS")
                f.write("\nSysTst_Manual_00005 SCAN BTN Test : PASS")   
            
            # Check LEDs ON statement is printed 
            self.dut_status = ''
            print("\nVerify that: LEDs ON statement is printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 LEDs ON Test : FAIL")
                f.write("\nSysTst_Manual_00005 LEDs ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 LEDs ON Test : PASS")
                f.write("\nSysTst_Manual_00005 LEDs ON Test : PASS")
            
            # Check Measurement processed is printed
            self.dut_status = ''
            print("\nVerify that: Measurement processed is printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Measurement Processed Test : FAIL")
                f.write("\nSysTst_Manual_00005 Measurement Processed Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Measurement Processed Test : PASS")
                f.write("\nSysTst_Manual_00005 Measurement Processed Test : PASS")
            
            # Check LEDs OFF statement is printed 
            self.dut_status = ''
            print("\nVerify that: LEDs OFF statement is printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 LEDs OFF Test : FAIL")
                f.write("\nSysTst_Manual_00005 LEDs OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 LEDs OFF Test : PASS")
                f.write("\nSysTst_Manual_00005 LEDs OFF Test : PASS")
            
        # close test report file
        f.close()
    
    def check_three_consecutive_measurements(self):
        
        # Open test report file
        with open(self.test_report_file, 'a') as f:

            while (self.measurement <= 3):

                print("The camera image should now be frozen on the last collected frame." \
                      "Press the scan button to return to main screen and get the system ready for another scan.")

                # Check the main screen is displayed correctly
                man_sys_tst_005.check_main_screen_is_displayed()

                # Check normal scan action - step [7]
                man_sys_tst_005.check_normal_scan_action()

                # Check the average of the measurements is being displayed
                self.dut_status = ''
                print("Verify that: Average of 3 consecutive measurements is displayed? Please type y or n (yes or no):")

                self.dut_status =  input()
                if not (self.dut_status == "y" or self.dut_status == "Y"):
                    print("SysTst_Manual_00005 Consecutive CCT Measurements Test : FAIL")
                    f.write("\nSysTst_Manual_00005 Consecutive CCT Measurements Test : FAIL")
                    f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                    # close test report file
                    f.close()
                    sys.exit()
                else:
                    print("SysTst_Manual_00005 Consecutive CCT Measurements Test : PASS")
                    f.write("\nSysTst_Manual_00005 Consecutive CCT Measurements Test : PASS")

        # close test report file
        f.close()

    def check_new_measurement_set(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
            
            # Check the clearing of previous set of measurements
            self.dut_status = ''
            print("\nPress the scan button once." \
                  "\nVerify that: Average of 3 consecutive measurements has been cleared from display? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 Clearing Consecutive CCT Measurements Test : FAIL")
                f.write("\nSysTst_Manual_00005 Clearing Consecutive CCT Measurements Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 Clearing Consecutive CCT Measurements Test : PASS")
                f.write("\nSysTst_Manual_00005 Clearing Consecutive CCT Measurements Test : PASS")
            
             # Check the start of a new set of measurements
            self.dut_status = ''
            print("\nPress the scan button once." \
                  "\nVerify that: New set of measurements initiated? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00005 New Consecutive CCT Measurements Test : FAIL")
                f.write("\nSysTst_Manual_00005 New Consecutive CCT Measurements Test : FAIL")
                f.write("\n\nSysTst_Manual_00005 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00005 New Consecutive CCT Measurements Test : PASS")
                f.write("\nSysTst_Manual_00005 New Consecutive CCT Measurements Test : PASS")
        
        # close test report file
        f.close()


if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00005
    """

    # Instantiate a test object
    man_sys_tst_005 = SysTst_Manual_00005()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_005.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_005.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_005.check_prerequisits_are_met()

    # Check stopwatch is ready
    retries = 0
    print("Is the stopwatch ready? Please type y or n (yes or no): ")
    reply = input()
    retries += 1

    while not (reply == "y" or reply == "Y" or retries >= 3):
        print("Is the stopwatch ready? Please type y or n (yes or no): ")
        reply = input()
        retries += 1
 
    # Ensure DUT is ON with long button press
    # Check the activation passed
    man_sys_tst_005.check_dut_is_powered_on_after_long_press()

    # Check the main screen is displayed correctly
    man_sys_tst_005.check_main_screen_is_displayed()

    # Check settings have been retrived
    man_sys_tst_005.check_settings_were_retrieved()

    # Check normal scan action - step [7]
    man_sys_tst_005.check_normal_scan_action()

    # Check LEDs ON/OFF statments are printed when scan initiates - step [8]
    man_sys_tst_005.check_led_statements()

    # get successive measurements - step [9] and step [10]
    man_sys_tst_005.check_three_consecutive_measurements()

    # Chect the start of a new set of measurements - step [11]
    man_sys_tst_005.check_new_measurement_set()

    # Ensure DUT is OFF - step [12]
    man_sys_tst_005.check_dut_is_powered_off()

    # If we got this far, the test is complete and has passed - step [13]
    # Open test report file
    with open(man_sys_tst_005.test_report_file, 'a') as f:

        # Test complete
        f.write("\n\nSysTst_Manual_00005 Test Complete : PASS") 
        print("\n\nSysTst_Manual_00005 Test Complete : PASS") 
    # close test report file
    f.close()

   