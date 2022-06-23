import os
import sys
from datetime import datetime
from pickle import FALSE, TRUE
import subprocess


class SysTst_Manual_00013(object):
    """
        This class implements the SysTst_Manual_00013 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:

        self.test_fail = []
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00013/SysTst_Manual_00013" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00013 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00013"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00013.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00013 Test Incomplete : FAIL")
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
                print("SysTst_Manual_00013 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00013 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00013 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00013 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00013 Power ON Test : PASS")   

        # close test report file
        f.close()
    
    
    def run_test_step4(self):
        # subprocess.call([r'C:/Repos/PM1-VnV-Module/MSV001/SV001_Test_Scripts/SysTst_Manual_00013/SysTst_Manual_00013_TestStep4.bat'])
        subprocess.call([r'C:/Temp/MSV001/MSV001_Test_Scripts/SysTst_Manual_00013/SysTst_Manual_00013_TestStep4.bat'])
        input_response = ''
        print("Was the Firmware Upload Successful? Please type y or n (yes or no): ")
        input_response = input()

        if not (input_response == "y" or input_response == "Y"):
            self.test_fail.append(TRUE)
        else:
            self.test_fail.append(FALSE)

    def run_test_step7(self):
        # subprocess.call([r'C:/Repos/PM1-VnV-Module/MSV001/SV001_Test_Scripts/SysTst_Manual_00013/SysTst_Manual_00013_TestStep7.bat'])
        subprocess.call([r'C:/Temp/MSV001/MSV001_Test_Scripts/SysTst_Manual_00013/SysTst_Manual_00013_TestStep7.bat'])
        input_response = ''
        print("Was the Firmware Upload Successful? Please type y or n (yes or no): ")
        input_response = input()

        if not (input_response == "y" or input_response == "Y"):
            self.test_fail.append(TRUE)
        else:
            self.test_fail.append(FALSE)

    def check_final_test_results(self):

        with open(self.test_report_file, 'a') as f:

            # print("Test results list", self.test_fail)
            # Check the final results list
            if TRUE in self.test_fail:
                print("SysTst_Manual_00013 - Bootloader Test Complete: FAIL")
                f.write("\n\nSysTst_Manual_00013 - Bootloader Test Complete: FAIL")
            else:
                print("SysTst_Manual_00013 - Bootloader Test Complete: PASS")
                f.write("\n\nSysTst_Manual_00013 - Bootloader Test Complete: PASS")
        
        # close test report file
        f.close()
   
        
if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00013
    """

    # Instantiate a test object
    man_sys_tst_013 = SysTst_Manual_00013()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_013.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_013.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_013.check_prerequisits_are_met()

    # Check DUT is powered ON
    man_sys_tst_013.check_dut_is_powered_on()

    # Program DUT with test firmware versions using bootloader
    man_sys_tst_013.run_test_step4()

    # Check DUT is powered ON
    man_sys_tst_013.check_dut_is_powered_on()

    # Program DUT with latest versions using bootloader
    man_sys_tst_013.run_test_step7()

    # Check overall test results, if either of programming steps failed, this should yield a FAIL
    man_sys_tst_013.check_final_test_results()
