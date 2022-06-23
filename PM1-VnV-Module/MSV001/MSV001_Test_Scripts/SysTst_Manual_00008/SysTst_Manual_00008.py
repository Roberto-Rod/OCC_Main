
from datetime import datetime
from pickle import FALSE, NONE, TRUE

import os
import sys


class SysTst_Manual_00008(object):
    """
        This class implements the SysTst_Manual_00008 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:

        self.measurement = 1
        self.measured_val = 0
        self.lp_mode_timeout_OFF_limit = 1080.0 # 18 minutes
        self.lp_mode_timeout_limit = 20.0 # 20 seconds
        self.time_tolerance = 0.1   # 10% tolerance in timing
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00008/SysTst_Manual_00008" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00008 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00008"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00008.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
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
                print("SysTst_Manual_00008 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00008 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00008 Power ON Test : PASS")   

        # close test report file
        f.close()  


    def check_dut_is_powered_off(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_off = ''
            print("\nVerify PM1 DUT POWERED_OFF? Please type y or n (yes or no): ")    
            self.dut_power_off =  input()
            if not (self.dut_power_off == "y" or self.dut_power_off == "Y"):
                print("SysTst_Manual_00008 Power OFF Test : FAIL")
                f.write("\nSysTst_Manual_00008 Power OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Power OFF Test : PASS")
                f.write("\nSysTst_Manual_00008 Power OFF Test : PASS")    

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
                print("SysTst_Manual_00008 Camera Active Test : FAIL")
                f.write("\nSysTst_Manual_00008 Camera Active Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Camera Active Test : PASS")
                f.write("\nSysTst_Manual_00008 Camera Active Test : PASS")   
            
            # Check the scan button
            self.dut_status = ''
            print("\nVerify that: The scan button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Scan Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00008 Scan Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Scan Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00008 Scan Button Displayed Test : PASS")
            
            # Check the settings button
            self.dut_status = ''
            print("\nVerify that: The settings button is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Settings Button Displayed Test : FAIL")
                f.write("\nSysTst_Manual_00008 Settings Button Displayed Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Settings Button Displayed Test : PASS")
                f.write("\nSysTst_Manual_00008 Settings Button Displayed Test : PASS")
            
            # Check the charge level indicator
            self.dut_status = ''
            print("\nVerify that: The charge level indicator is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Charge Level Indicator Test : FAIL")
                f.write("\nSysTst_Manual_00008 Charge Level Indicator Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Charge Level Indicator Test : PASS")
                f.write("\nSysTst_Manual_00008 Charge Level Indicator Test : PASS")
    
        # close test report file
        f.close() 
    
    def check_dut_is_in_low_power(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
        
            # Check dut is in low power
            self.dut_status = ''
            print("\nVerify that: DUT is in low power state (black screen)? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 In Low Power State Test : FAIL")
                f.write("\nSysTst_Manual_00008 In Low Power State Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 In Low Power State Test : PASS")
                f.write("\nSysTst_Manual_00008 In Low Power State Test : PASS")

        # close test report file
        f.close()
    
    def check_dut_exits_low_power(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
        
            # Check dut exited low power
            self.dut_status = ''
            print("\nVerify that: DUT exits low power state (screen is active and showing main screen)? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Exit Low Power State Test : FAIL")
                f.write("\nSysTst_Manual_00008 Exit Low Power State Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Exit Low Power State Test : PASS")
                f.write("\nSysTst_Manual_00008 Exit Low Power State Test : PASS")

        # close test report file
        f.close()
    
    def check_low_power_mode_timeout(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
        
            # Check dut exited low power
            self.dut_status = ''
            print("\nVerify that: DUT exits low power state (screen is active and showing main screen)? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Exit Low Power State Test : FAIL")
                f.write("\nSysTst_Manual_00008 Exit Low Power State Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Exit Low Power State Test : PASS")
                f.write("\nSysTst_Manual_00008 Exit Low Power State Test : PASS")
            
            # Check stopwatch is ready
            retries = 0
            print("Is the stopwatch ready? Please type y or n (yes or no): ")
            reply = input()
            retries += 1

            while not (reply == "y" or reply == "Y" or retries >= 3):
                print("Is the stopwatch ready? Please type y or n (yes or no): ")
                reply = input()
                retries += 1
            
            # Check dut has entered low power mode
            self.dut_status = ''
            print("\nVerify that: DUT is in low power state (black screen)? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 In Low Power State Test : FAIL")
                f.write("\nSysTst_Manual_00008 In Low Power State Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 In Low Power State Test : PASS")
                f.write("\nSysTst_Manual_00008 In Low Power State Test : PASS")
            
            # Wait for 17 Wait for 17 minutes and monitor the DUT closely for the next minute, looking out for the turn OFF Tune.
            # Check dut turns OFF

            self.check_dut_is_powered_off()
            
            # Check the timeout value
            lp_measured_timeout = 0.0

            print("Please enter the measured time in seconds taken for the DUT to turn OFF when in low power state:")
            lp_measured_timeout = float(input())

            if lp_measured_timeout <= (self.lp_mode_timeout_OFF_limit * self.time_tolerance + self.lp_mode_timeout_OFF_limit):

                print("SysTst_Manual_00008 OFF Low Power Mode Timeout Test : PASS")
                f.write("\nSysTst_Manual_00008 OFF Low Power Mode Timeout Test : PASS")
            else:
                print("SysTst_Manual_00008 OFF Low Power Mode Timeout Test : FAIL \nMax Limit = " + str(self.lp_mode_timeout_limit) + "; Measured timeout  = " + str(lp_measured_timeout))
                f.write("\nSysTst_Manual_00008 Off Low Power Mode Timeout Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                # sys.exit()
            
            # Check dut is OFF and cannot be turned ON by an LCD_TAP
            print("Perform an LDC_TAP and monitor the DUT. Verify that the device remains OFF (no activity on the screen, no tunes played).")

        # close test report file
        f.close()
    
    def check_dut_on_reduced_voltage(self, voltage : float ):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_status = ''
            print("\nReduce the PSU voltage supply to " + str(voltage) + ". Verify that the device remains ON? Please type y or n (yes or no):" )

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Low Battery in ON State Test : FAIL")
                f.write("\nSysTst_Manual_00008 Low Battery in ON State Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Low Battery in ON State Test : PASS")
                f.write("\nSysTst_Manual_00008 Low Battery in ON State Test : PASS")

            self.dut_status = ''
            print("\nTouch the scan button to initiate a scan.Verify device is able to achieve a scan measurement and display it on screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Low Battery Scan Test : FAIL \nDUT failed to scan with supply voltage = " + str(voltage))
                f.write("\nSysTst_Manual_00008 Low Battery Scan Test : FAIL \nDUT failed to scan with supply voltage = " + str(voltage))
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Low Battery Scan Test : PASS")
                f.write("\nSysTst_Manual_00008 Low Battery Scan Test : PASS")

        # close test report file
        f.close()
    
    def check_dut_turns_off_when_low_battery(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Check dut turns OFF
            self.check_dut_is_powered_off()

            self.dut_status = ''
            print("Perform an LDC_TAP and monitor the DUT: Verify remains turned OFF? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Turn OFF in Low Battery Test : FAIL")
                f.write("\nSysTst_Manual_00008 Turn OFF in Low Battery Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Turn OFF in Low Battery Test : PASS")
                f.write("\nSysTst_Manual_00008 Turn OFF in Low Battery Test : PASS")
            
            self.dut_status = ''
            print("Perform an BUT_SHORT_PRESS and monitor the DUT: Verify remains turned OFF? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Turn ON in Low Battery Test : FAIL")
                f.write("\nSysTst_Manual_00008 Turn ON in Low Battery Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Turn ON in Low Battery Test : PASS")
                f.write("\nSysTst_Manual_00008 Turn ON in Low Battery Test : PASS")

            self.dut_status = ''
            print("Perform an BUT_LONG_PRESS and monitor the DUT: Verify remains turned OFF? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Turn ON in Low Battery Test : FAIL")
                f.write("\nSysTst_Manual_00008 Turn ON in Low Battery Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Turn ON in Low Battery Test : PASS")
                f.write("\nSysTst_Manual_00008 Turn ON in Low Battery Test : PASS")

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
                print("SysTst_Manual_00008 Scan Start Test : FAIL")
                f.write("\nSysTst_Manual_00008 Scan Start Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Scan Start Test : PASS")
                f.write("\nSysTst_Manual_00008 Scan Start Test  PASS")   
            
            # Check Laser ON indicator is being displayed during scanning
            self.dut_status = ''
            print("\nVerify that: Laser ON indicator is being displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Laser ON Indicator Test : FAIL")
                f.write("\nSysTst_Manual_00008 Laser ON Indicator Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Laser ON Indicator Test : PASS")
                f.write("\nSysTst_Manual_00008 Laser ON Indicator Test : PASS")  
            
            # Check Progress bar shows scanning progress 
            self.dut_status = ''
            print("\nVerify that: Progress bar shows scanning progress? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Progress Bar Test : FAIL")
                f.write("\nSysTst_Manual_00008 Progress Bar Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Progress Bar Test : PASS")
                f.write("\nSysTst_Manual_00008 Progress Bar Test : PASS")
            
            # Check Alignment circle is shown and changes from red to green when the measurement is complete
            self.dut_status = ''
            print("\nVerify that: Alignment circle is shown and changes from red to green? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Alignment circle Shown Test : FAIL")
                f.write("\nSysTst_Manual_00008 Alignment circle Shown Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Alignment circle Shown Test : PASS")
                f.write("\nSysTst_Manual_00008 Alignment circle Shown Test : PASS")
            
            # Check Scan is complete
            self.dut_status = ''
            print("\nVerify that: Scan is complete? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Scan Complete Test : FAIL")
                f.write("\nSysTst_Manual_00008 Scan Complete Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Scan Complete Test : PASS")
                f.write("\nSysTst_Manual_00008 Scan Complete Test : PASS")
            
            # Check Alignment circle is removed from camera image
            self.dut_status = ''
            print("\nVerify that: Alignment circle is removed from camera image? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Alignment Circle Removed Test : FAIL")
                f.write("\nSysTst_Manual_00008 Alignment Circle Removed Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Alignment Circle Removed Test : PASS")
                f.write("\nSysTst_Manual_00008 Alignment Circle Removed Test : PASS")
            
            # Check Camera freezes with image when scan was performed
            self.dut_status = ''
            print("\nVerify that: Camera freezes with image when scan was performed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Camera Freezes with Image Test : FAIL")
                f.write("\nSysTst_Manual_00008 Camera Freezes with Image Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00008 Camera Freezes with Image Test : PASS")
                f.write("\nSysTst_Manual_00008 Camera Freezes with Image Test : PASS")
            
            # Check Measurement value is displayed in green and enter the measurement as request by the prompt window
            self.dut_status = ''
            print("\nVerify that: Measurement " + str(self.measurement) + " value is displayed in green? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00008 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : FAIL")
                f.write("\nSysTst_Manual_00008 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("Please enter the value of the measurement in whole units of um (micrometres) as displayed on the PM1 screen:")
                # store the measurement to use later
                self.measured_val = int(input(),base=10)
                print("SysTst_Manual_00008 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : PASS")
                f.write("\nSysTst_Manual_00008 Green Measurement " + str(self.measurement) + " = " + str(self.measured_val) + " Value Test : PASS")
                self.measurement += 1
 
        # close test report file
        f.close()


    def check_enter_lp_timeout(self):

         # Open test report file
        with open(self.test_report_file, 'a') as f:

             # Check the timeout value
            lp_measured_timeout = 0.0
            print("Please enter the measured time in seconds taken for the DUT to enter low power state:")
            lp_measured_timeout = float(input())

            if lp_measured_timeout <= (self.lp_mode_timeout_OFF_limit * self.time_tolerance + self.lp_mode_timeout_OFF_limit):

                print("SysTst_Manual_00008 Low Power Mode Timeout Test : PASS")
                f.write("\nSysTst_Manual_00008 Low Power Mode Timeout Test : PASS")
            else:
                print("SysTst_Manual_00008 Low Power Mode Timeout Test : FAIL \nMax Limit = " + str(self.lp_mode_timeout_OFF_limit) + "; Measured timeout  = " + str(lp_measured_timeout))
                f.write("\nSysTst_Manual_00008 Low Power Mode Timeout Test : FAIL")
                f.write("\n\nSysTst_Manual_00008 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close()

if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00008
    """

    # Instantiate a test object
    man_sys_tst_008 = SysTst_Manual_00008()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_008.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_008.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_008.check_prerequisits_are_met()

    # Ensure DUT is ON 
    man_sys_tst_008.check_dut_is_powered_on()

    # Check the main screen is displayed - step [3]
    man_sys_tst_008.check_main_screen_is_displayed()

    # Check the DUT is in low power state after 1 minute
    man_sys_tst_008.check_dut_is_in_low_power()

    # Check stopwatch is ready
    print("Is the stopwatch ready? Please type y or n (yes or no): ")
    reply = input()


    print("Start the timer when the DUT enter low power")
    # Check the timeout
    man_sys_tst_008.check_enter_lp_timeout()

    print("Is the stopwatch ready? Please type y or n (yes or no): ")
    reply = input()

    print("Start the timer when the DUT enter low power")
    # Check the timeout
    man_sys_tst_008.check_enter_lp_timeout()

    # Check the DUT exits low power state
    man_sys_tst_008.check_dut_exits_low_power()
    
    # Check low power mode timeout, dut should turn OFF after 18 consecutive minutes of being in low power state
    man_sys_tst_008.check_low_power_mode_timeout()

    # Ensure DUT is ON after button press - step [8]
    man_sys_tst_008.check_dut_is_powered_on()

    # Check dut remains ON when the voltage is reduced to 7.0V - value may change
    man_sys_tst_008.check_dut_on_reduced_voltage(7.0)

    # Check dut remains ON when the voltage is reduced to 6.8V - value may change
    man_sys_tst_008.check_dut_on_reduced_voltage(6.8)

    # Check dut turns OFF when voltage is reduced to TBD - enter the battery voltage limit in __init__
    man_sys_tst_008.check_dut_turns_off_when_low_battery()

    # Check dut turns ON once the bateery voltage is back to normal
    man_sys_tst_008.check_dut_is_powered_on()

    # Check dut can complete a scan measurement
    man_sys_tst_008.check_normal_scan_action()

    # Ensure DUT is OFF - step 
    man_sys_tst_008.check_dut_is_powered_off()

    # If we got this far, the test is complete and has passed - step 
    # Open test report file
    with open(man_sys_tst_008.test_report_file, 'a') as f:

        # Test complete
        f.write("\n\nSysTst_Manual_00008 Test Complete : PASS") 
        print("\n\nSysTst_Manual_00008 Test Complete : PASS") 
    # close test report file
    f.close()

   