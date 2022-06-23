
from datetime import datetime
from pickle import FALSE, NONE, TRUE

import os
import sys


class SysTst_Manual_00003(object):
    """
        This class implements the SysTst_Manual_00003 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00003/SysTst_Manual_00003" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00003 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00003"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00003.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00003 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close() 


    def check_dut_is_powered_on(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_on = ''
            print("\nPerform a short button press and ensure PM1 DUT powers up. Verify PM1 DUT POWERED_ON? Please type y or n (yes or no): ")      
            self.dut_power_on =  input()
            if not (self.dut_power_on == "y" or self.dut_power_on == "Y"):
                print("SysTst_Manual_00003 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00003 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00003 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00003 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00003 Power ON Test : PASS")   

        # close test report file
        f.close()    

    def check_dut_is_powered_off(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_off = ''
            print("\nPerform a long button press and ensure PM1 DUT powers down. Verify PM1 DUT POWERED_OFF? Please type y or n (yes or no): ")    
            self.dut_power_off =  input()
            if not (self.dut_power_off == "y" or self.dut_power_off == "Y"):
                print("SysTst_Manual_00003 Power OFF Test : FAIL")
                f.write("\nSysTst_Manual_00003 Power OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00003 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00003 Power OFF Test : PASS")
                f.write("\nSysTst_Manual_00003 Power OFF Test  PASS")    

        # close test report file
        f.close() 

    def check_lda_error_is_displayed(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.lda_error_detected = ''
            print("\nObserve the DUT screen and check the error message."\
            " Verify PM1 DUT screen shows Timed out waiting for versions? Please type y or n (yes or no): ")    
            self.lda_error_detected =  input()
            if not (self.lda_error_detected == "y" or self.lda_error_detected == "Y"):
                print("SysTst_Manual_00003 LDA Error Detection Test : FAIL")
                f.write("\nSysTst_Manual_00003 LDA Error Detection Test : FAIL")
                f.write("\n\nSysTst_Manual_00003 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00003 LDA Error Detection Test : PASS")
                f.write("\nSysTst_Manual_00003 LDA Error Detection Test : PASS")  

        # close test report file
        f.close() 

    def check_lsc_error_is_displayed(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.lda_error_detected = ''
            print("\nObserve the DUT screen and check the error message. Verify PM1 DUT screen shows the LSC Error? Please type y or n (yes or no): ")    
            self.lda_error_detected =  input()
            if not (self.lda_error_detected == "y" or self.lda_error_detected == "Y"):
                print("SysTst_Manual_00003 LSC Error Detection Test : FAIL")
                f.write("\nSysTst_Manual_00003 LSC Error Detection Test : FAIL")
                f.write("\n\nSysTst_Manual_00003 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00003 LSC Error Detection Test : PASS")
                f.write("\nSysTst_Manual_00003 LSC Error Detection Test : PASS")  

        # close test report file
        f.close() 


    def check_camera_error_is_displayed(self):
        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.camera_error_detected = ''
            print("\nObserve the DUT screen and check the error message. Verify PM1 DUT screen shows the camera Error? Please type y or n (yes or no): ")    
            self.camera_error_detected =  input()
            if not (self.camera_error_detected == "y" or self.camera_error_detected == "Y"):
                print("SysTst_Manual_00003 Camera Error Detection Test : FAIL")
                f.write("\nSysTst_Manual_00003 Camera Error Detection Test : FAIL")
                f.write("\n\nSysTst_Manual_00003 Camera Error Detection Test : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00003 Camera Error Detection Test : PASS")
                f.write("\nSysTst_Manual_00003 Camera Error Detection Test : PASS")  

        # close test report file
        f.close() 
    
    def check_laser_switch_error_is_displayed(self):
        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.laser_error_detected = ''
            print("\nObserve the DUT screen and check the error message. Verify PM1 DUT screen shows the laser safety switch Error? Please type y or n (yes or no): ")    
            self.laser_error_detected =  input()
            if not (self.laser_error_detected == "y" or self.laser_error_detected == "Y"):
                print("SysTst_Manual_00003 Laser Safety Switch Error Detection Test : FAIL")
                f.write("\nSysTst_Manual_00003 Laser Safety Switch Error Detection Test : FAIL")
                f.write("\n\nSysTst_Manual_00003 Laser Safety Switch Error Detection Test : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00003 Laser Safety Switch Error Detection Test : PASS")
                f.write("\nSysTst_Manual_00003 Laser Safety Switch Error Detection Test : PASS")  

        # close test report file
        f.close() 
    
    def request_board_setup_change(self, rmv_board, set_board):

        attempts = 0
        print("Reconnect the " + set_board + ", and disconnect the " + rmv_board + " Encoder. Is this complete? Please type y or n (yes or no): ")
        attempts += 1
        dut_ready = input()
        while ((not (dut_ready == "y" or dut_ready == "Y" )) and attempts < 3):
            
            print("Reconnect the LDA board, and disconnect the LSC Encoder board. Is this complete? Please type y or n (yes or no): ")
            dut_ready = input()
            attempts += 1

            if attempts <= 3:
                print("Please get the DUT ready before typing y")
    

if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00003
    """

    # Instantiate a test object
    man_sys_tst_003 = SysTst_Manual_00003()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_003.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_003.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_003.check_prerequisits_are_met()
    
    # Ensure DUT is ON
    man_sys_tst_003.check_dut_is_powered_on()

    # Ensure LDA error is shown
    man_sys_tst_003.check_lda_error_is_displayed()
    
    # Ensure DUT is OFF
    man_sys_tst_003.check_dut_is_powered_off()

    # Allow operator to power OFF DUT, reconnect the LDA board, and disconnect the LSC Encoder board
    man_sys_tst_003.request_board_setup_change("LSC", "LDA")
    
    # Ensure DUT is ON
    man_sys_tst_003.check_dut_is_powered_on()

    # Ensure LSC error is shown
    man_sys_tst_003.check_lsc_error_is_displayed()
    
    # Ensure DUT is OFF
    man_sys_tst_003.check_dut_is_powered_off()

    # Allow operator to power OFF DUT, reconnect the LSC board, and disconnect the camera
    man_sys_tst_003.request_board_setup_change("Camera", "LSC")
    
    # Ensure DUT is ON
    man_sys_tst_003.check_dut_is_powered_on()

    # Ensure LSC error is shown
    man_sys_tst_003.check_camera_error_is_displayed()
    
    # Ensure DUT is OFF
    man_sys_tst_003.check_dut_is_powered_off()

    # Run the laser safety switch test
    # Allow operator to power OFF DUT and change the laser safety circuit switch
    man_sys_tst_003.request_board_setup_change("Laser Safety Switch", "Camera")

    # Run laser safety circuit test
    man_sys_tst_003.check_laser_switch_error_is_displayed()

    # If we got this far, the test is complete and has passed
    # Open test report file
    with open(man_sys_tst_003.test_report_file, 'a') as f:

        # Test complete
        f.write("\n\nSysTst_Manual_00003 Test Complete : PASS") 
        print("\n\nSysTst_Manual_00003 Test Complete : PASS") 
    # close test report file
    f.close()

   