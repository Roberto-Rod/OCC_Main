import os
import sys
from datetime import datetime
from pickle import FALSE, TRUE


class SysTst_Manual_00015(object):
    """
        This class implements the SysTst_Manual_00015 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:

        self.MAIN_SCREEN_MAX_CUR = 400.0 # 400mA
        self.LOW_POWER_MAX_CUR = 200.0 # 200mA
        self.LOW_POWER_MAX_TIMEOUT = 20.0 # 20seconds
        self.main_screen_readings_list = []
        self.main_screen_readings_cnt = 0
        self.low_power_readings_list = []
        self.low_power_readings_cnt = 0
        self.low_power_time_readings_list = []
        self.low_power_time_readings_cnt = 0
        self.test_fail = []
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00015/SysTst_Manual_00015" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00015 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00015"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00015.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00015 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close()    

    def request_and_check__main_screen_reading(self, voltage):

        with open(self.test_report_file, 'a') as f:

            # Request reading from user
            reading = 0.0
            print("Please enter the current reading (in mA) whilst main screen is ON:")
            reading = float(input())
            self.main_screen_readings_cnt += 1
            print("Vpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Main Screen reading " + str(self.main_screen_readings_cnt) + " in mA : " + str(reading))
            f.write("\nVpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Main Screen reading " + str(self.main_screen_readings_cnt) + " in mA : " + str(reading))
            self.main_screen_readings_list.append(reading)
            print(self.main_screen_readings_list)

            # Check the measurement is within limits
            if reading <= self.MAIN_SCREEN_MAX_CUR:
                
                print("Vpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Main Screen Current Test : PASS")
                f.write("\nVpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Main Screen Current Test : PASS")
                self.test_fail.append(FALSE)
            else:
                print("SysTst_Manual_00015 Main Screen Current Test : FAIL")
                f.write("\nSysTst_Manual_00015 Main Screen Current Test : FAIL")
                self.test_fail.append(TRUE)

        # close test report file
        f.close()

    def request_and_check_lp_reading(self, voltage):

        with open(self.test_report_file, 'a') as f:

            # Request reading from user
            reading = 0.0
            print("Please enter the current reading (in mA) whilst in Low Power:")
            reading = float(input())
            self.low_power_readings_cnt += 1
            print("Vpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Low Power reading " + str(self.low_power_readings_cnt) + " in mA : " + str(reading))
            f.write("\nVpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Low Power reading " + str(self.low_power_readings_cnt) + " in mA : " + str(reading))
            self.low_power_readings_list.append(reading)
            print(self.low_power_readings_list)

            # Check the measurement is within limits
            if reading <= self.LOW_POWER_MAX_CUR:
                
                print("Vpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Low Power Current Test : PASS")
                f.write("\nVpsu (V) " + str(voltage) + " - SysTst_Manual_00015 Low Power Current Test : PASS")
                self.test_fail.append(FALSE)
            else:
                print("SysTst_Manual_00015 Low Power Current Test : FAIL")
                f.write("\nSysTst_Manual_00015 Low Power Current Test : FAIL")
                self.test_fail.append(TRUE)

        # close test report file
        f.close()
    
    def request_and_check_lp_timeout(self):

        with open(self.test_report_file, 'a') as f:

            # Request reading from user
            reading = 0.0
            print("Please enter the time taken to enter Low Power:")
            reading = float(input())
            self.low_power_time_readings_cnt += 1
            print("SysTst_Manual_00015 Low Power Timeout reading " + str(self.low_power_time_readings_cnt) + " in ms : " + str(reading))
            f.write("\nSysTst_Manual_00015 Low Power Timeout reading " + str(self.low_power_time_readings_cnt) + " in ms : " + str(reading))
            self.low_power_time_readings_list.append(reading)
            print(self.low_power_time_readings_list)

            # Check the measurement is within limits
            if reading > self.LOW_POWER_MAX_TIMEOUT:
                
                print("SysTst_Manual_00015 Low Power Timeout Test : PASS")
                f.write("\nSysTst_Manual_00015 Low Power Timeout Test : PASS")
                self.test_fail.append(FALSE)
            else:
                print("SysTst_Manual_00015 Low Power Timeout Test : FAIL")
                f.write("\nSysTst_Manual_00015 Low Power Timeout Test : FAIL")
                self.test_fail.append(TRUE)

        # close test report file
        f.close()

    def check_final_test_results(self):

        with open(self.test_report_file, 'a') as f:

            # print("Test results list", self.test_fail)
            # Check the final results list
            if TRUE in self.test_fail:
                print("SysTst_Manual_00015 - Power Consumption Test Complete: FAIL")
                f.write("\n\nSysTst_Manual_00015 - Power Consumption Test Complete: FAIL")
            else:
                print("SysTst_Manual_00015 - Power Consumption Test Complete: PASS")
                f.write("\n\nSysTst_Manual_00015 - Power Consumption Test Complete: PASS")
        
        # close test report file
        f.close()

            
if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00015
    """

    # Instantiate a test object
    man_sys_tst_015 = SysTst_Manual_00015()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_015.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_015.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_015.check_prerequisits_are_met()

    # Request current measurements as per the protocol
    print("Change the LCD brightness level to its minimum value and return to the main screen. Take a current reading.")
    man_sys_tst_015.request_and_check__main_screen_reading(7.5)

    # Request low power mode reading
    print("Wait for DUT to enter low power mode.  Take a current reading.")
    man_sys_tst_015.request_and_check_lp_reading(7.5)

    # Request and check low power timeout
    man_sys_tst_015.request_and_check_lp_timeout()

    # Request low power mode reading
    man_sys_tst_015.request_and_check_lp_reading(7.5)

    # Request current measurements as per the protocol
    print("Perform a BUT_SHORT_PRESS to wake up DUT and display the main screen. Take a reading when in the main screen.")
    man_sys_tst_015.request_and_check__main_screen_reading(7.5)

    # Request current measurements as per the protocol - step [7]
    print("Change the LCD brightness level to its maximum value and return to the main screen. Take a current reading.")
    man_sys_tst_015.request_and_check__main_screen_reading(7.5)

    # Request low power mode reading
    print("Wait for DUT to enter low power mode.  Take a current reading.")
    man_sys_tst_015.request_and_check_lp_reading(7.5)

    # Request low power mode reading after 1 minute 
    print("Wait for 1 minute in low power state and take a reading.")
    man_sys_tst_015.request_and_check_lp_reading(7.5)

    # Request current measurements as per the protocol - step [8]
    print("Change the LCD brightness level to its mid-level value and return to the main screen. Take a current reading.")
    man_sys_tst_015.request_and_check__main_screen_reading(7.5)

    # Request low power mode reading
    print("Wait for DUT to enter low power mode.  Take a current reading.")
    man_sys_tst_015.request_and_check_lp_reading(7.5)

    # Request low power mode reading after 1 minute 
    print("Wait for 1 minute in low power state and take a reading.")
    man_sys_tst_015.request_and_check_lp_reading(7.5)

    # get measurements at low voltage   - step [9]
    # Request low power mode reading after 1 minute 
    print("Reduce the PSU output voltage to 6.8V. Wait for 1 minute in low power state and take a reading.")
    man_sys_tst_015.request_and_check_lp_reading(6.8)

    # Request current measurements as per the protocol 
    print("Perform a BUT_SHORT_PRESS to wake up DUT and display the main screen. Take a reading when in the main screen.")
    man_sys_tst_015.request_and_check__main_screen_reading(6.8)

    # Request current measurements as per the protocol - step [10]
    print("Change the LCD brightness level to its maximum value and return to the main screen. Take a current reading.")
    man_sys_tst_015.request_and_check__main_screen_reading(6.8)

    # Request low power mode reading
    print("Wait for DUT to enter low power mode.  Take a current reading.")
    man_sys_tst_015.request_and_check_lp_reading(6.8)

    # Request low power mode reading after 1 minute 
    print("Wait for 1 minute in low power state and take a reading.")
    man_sys_tst_015.request_and_check_lp_reading(6.8)

    # Request current measurements as per the protocol 
    print("Perform a BUT_SHORT_PRESS to wake up DUT and display the main screen. Take a reading when in the main screen.")
    man_sys_tst_015.request_and_check__main_screen_reading(6.8)

    # Check DUT turns OFF
    print("\nPerform a long button press and ensure PM1 DUT powers down.")

    # Check overall test results, if either of the tests had a measurement beyond limits, this should yield a FAIL
    man_sys_tst_015.check_final_test_results()


