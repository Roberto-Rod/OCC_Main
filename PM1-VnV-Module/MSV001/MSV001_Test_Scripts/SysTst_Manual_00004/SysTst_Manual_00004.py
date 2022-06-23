
from datetime import datetime
from pickle import FALSE, NONE, TRUE

import os
import sys


class SysTst_Manual_00004(object):
    """
        This class implements the SysTst_Manual_00004 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00004/SysTst_Manual_00004" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00004 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00004"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00004.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close() 
    
    def check_dc_power_is_applied(self):
        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_on = ''
            print("\nTurn the PSU output ON and apply power to the PM1 DUT. Verify PSU is ON, and DUT remains OFF? Please type y or n (yes or no): ")      
            self.dut_power_on =  input()
            if not (self.dut_power_on == "y" or self.dut_power_on == "Y"):
                print("SysTst_Manual_00004 Power Application Test : FAIL")
                f.write("\nSysTst_Manual_00004 Power Application Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 PPower Application Test : PASS")
                f.write("\nSysTst_Manual_00004 Power Application Test : PASS")   

        # close test report file
        f.close()   


    def check_dut_is_powered_on(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_on = ''
            print("\nPerform a short button press and ensure PM1 DUT powers up. Verify is PM1 DUT POWERED_ON? Please type y or n (yes or no): ")      
            self.dut_power_on =  input()
            if not (self.dut_power_on == "y" or self.dut_power_on == "Y"):
                print("SysTst_Manual_00004 Power ON Test : FAIL")
                f.write("\nSysTst_Manual_00004 Power ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 Power ON Test : PASS")
                f.write("\nSysTst_Manual_00004 Power ON Test : PASS")   

        # close test report file
        f.close()    

    def check_dut_is_powered_off(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_power_off = ''
            print("\nPerform a long button press and ensure PM1 DUT powers down. Verify PM1 DUT POWERED_OFF? Please type y or n (yes or no): ")    
            self.dut_power_off =  input()
            if not (self.dut_power_off == "y" or self.dut_power_off == "Y"):
                print("SysTst_Manual_00004 Power OFF Test : FAIL")
                f.write("\nSysTst_Manual_00004 Power OFF Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 Power OFF Test : PASS")
                f.write("\nSysTst_Manual_00004 Power OFF Test  PASS")    

        # close test report file
        f.close() 

    def check_dut_activated_ok(self):
        
        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_status = ''
            print("\nVerify that: Display turns ON (illuminated) showing loading splash screen? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Display ON Test : FAIL")
                f.write("\nSysTst_Manual_00004 Display ON Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 Display ON Test : PASS")
                f.write("\nSysTst_Manual_00004 Display ON Test  PASS")  

            self.dut_status = ''
            print("\nVerify that: Turn On tune is played? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Turn On Tune Test : FAIL")
                f.write("\nSysTst_Manual_00004 Turn On Tune Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 Turn On Tune Test : PASS")
                f.write("\nSysTst_Manual_00004 Turn On Tune Test  PASS")  

            self.dut_status = ''
            print("\nVerify that: Version numbers are displayed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Version Numbers Test : FAIL")
                f.write("\nSysTst_Manual_00004 Version Numbers Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 Version Numbers Test : PASS")
                f.write("\nSysTst_Manual_00004 Version Numbers Test  PASS")    
            
            self.dut_status = ''
            print("\nVerify that: LRS is Active?  Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 LRS is Active Test : FAIL")
                f.write("\nSysTst_Manual_00004 LRS is Active Test : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()
            else:
                print("SysTst_Manual_00004 LRS is Active Test : PASS")
                f.write("\nSysTst_Manual_00004 LRS is Active Test  PASS")  

        # close test report file
        f.close() 
    
    def check_lrs_com_port_activations(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            self.dut_status = ''
            print("\nVerify that: Has LRS Activation concluded (if its ongoing, wait until it stops)? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Wait for LRS Activation : FAIL")
                f.write("\nSysTst_Manual_00004 Wait for LRS Activation : FAIL")
                f.write("\n\nSysTst_Manual_00004 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

            # Continue to check LRS activation time
            print("Please observe the stopwatch and enter the total time in seconds : ")
            lrs_activation_time = float(input())

            max_limit = 360.0

            if lrs_activation_time <= max_limit:
                print("SysTst_Manual_00004 LRS Activation Test : PASS")
                f.write("\nSysTst_Manual_00004 LRS Activation Test  PASS")  
            else:
                print("SysTst_Manual_00004 LRS Activation Time Test: FAIL. Max Limit = 360s, LRS Activation time = ", str(lrs_activation_time))
                f.write("\nSysTst_Manual_00004 LRS Activation Time Test : FAIL")
            
            # Continue to check Tuning Fail message
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Any occurrences of Tuning Fail message? Please type y or n (yes or no):")

            self.dut_status =  input()
            if self.dut_status == "y" or self.dut_status == "Y":
                print("SysTst_Manual_00004 Tuning Fail Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Tuning Fail Message Test : FAIL")
            else:
                print("SysTst_Manual_00004 Tuning Fail Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Tuning Fail Message Test  PASS")  
            
            # Continue to check Reset message
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Any occurrences of Reset message? Please type y or n (yes or no):")

            self.dut_status =  input()
            if self.dut_status == "y" or self.dut_status == "Y":
                print("SysTst_Manual_00004 Reset Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Reset Message Test : FAIL")
            else:
                print("SysTst_Manual_00004 Reset Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Reset Message Test  PASS")    
            
             # Continue to check Activation Time message
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Screen displays Activation Time > 45s message? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Activation Time > 45s : FAIL")
                f.write("\nSysTst_Manual_00004 Activation Time > 45s : FAIL")
            else:
                print("SysTst_Manual_00004 Activation Time > 45s : PASS")
                f.write("\nSysTst_Manual_00004 Activation Time > 45s  PASS")   

        # close test report file
        f.close() 
    
    def check_resonant_frequency(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Check resonant frequency message was printed
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Resonant Frequency message printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Resonant Frequency Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Resonant Frequency Message Test : FAIL")
            else:
                print("SysTst_Manual_00004 Resonant Frequency Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Resonant Frequency Message Test  PASS")
            
            # Check resonant frequency
            print("\nPlease observe the LRS Communication Terminal. Please enter Current drive frequency FREQ1: ")
            freq1 = input()
            print("\nPlease observe the LRS Communication Terminal. Please enter Resonant frequency FREQ2: ")
            freq2 = input()

            if freq1 == freq2:
                print("SysTst_Manual_00004 Current and Resonant Frequency Test : PASS")
                f.write("\nSysTst_Manual_00004 Current and Resonant Frequency Test  PASS")
            else:
                print("SysTst_Manual_00004 Current and Resonant Frequency Test : FAIL")
                f.write("\nSysTst_Manual_00004 Current and Resonant Frequency Test  FAIL")
            
            # CONTINUE TO CHECK SAVE SETTINGS MESSAGE
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Save settings message printed? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Save Settings Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Save Settings Message Test : FAIL")
            else:
                print("SysTst_Manual_00004 Save Settings Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Save Settings Message Test  PASS")
        
        # close test report file
        f.close()
    
    def check_lrs_activation_time(self):

        # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Check resonant frequency is the same as before
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Resonant Frequency FREQ2 same as previous step? Please type y or n (yes or no):")

            self.dut_status =  input()
            if not (self.dut_status == "y" or self.dut_status == "Y"):
                print("SysTst_Manual_00004 Resonant Frequency Check Test : FAIL")
                f.write("\nSysTst_Manual_00004 Resonant Frequency Check Test : FAIL")
            else:
                print("SysTst_Manual_00004 Resonant Frequency Check Test : PASS")
                f.write("\nSysTst_Manual_00004 Resonant Frequency Check Test  PASS")
            
            # Check lrs activation time
            lrs_activation_time_limit = 15.0
            print("\nPlease enter the LRS activation time duration: ")
            lrs_activation_time = float(input())

            if lrs_activation_time <= lrs_activation_time_limit:
                print("SysTst_Manual_00004 Current and Resonant Frequency Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Current and Resonant Frequency Message Test  PASS")
            else:
                print("SysTst_Manual_00004 Current and Resonant Frequency Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Current and Resonant Frequency Message Test  FAIL")
            
            # Continue to check Tuning Fail message
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Any occurrences of Tuning Fail message? Please type y or n (yes or no):")

            self.dut_status =  input()
            if self.dut_status == "y" or self.dut_status == "Y":
                print("SysTst_Manual_00004 Tuning Fail Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Tuning Fail Message Test : FAIL")
            else:
                print("SysTst_Manual_00004 Tuning Fail Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Tuning Fail Message Test  PASS")  
            
            # Continue to check Reset message
            self.dut_status = ''
            print("\nPlease observe the LRS Communication Terminal. Verify that: Any occurrences of Reset message? Please type y or n (yes or no):")

            self.dut_status =  input()
            if self.dut_status == "y" or self.dut_status == "Y":
                print("SysTst_Manual_00004 Reset Message Test : FAIL")
                f.write("\nSysTst_Manual_00004 Reset Message Test : FAIL")
            else:
                print("SysTst_Manual_00004 Reset Message Test : PASS")
                f.write("\nSysTst_Manual_00004 Reset Message Test  PASS") 
        
        # close test report file
        f.close()
 

if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00004
    """

    # Instantiate a test object
    man_sys_tst_004 = SysTst_Manual_00004()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_004.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_004.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_004.check_prerequisits_are_met()

    # Apply DC power to the board
    man_sys_tst_004.check_dc_power_is_applied()

    # Check stopwatch is ready
    retries = 0
    print("Is the stopwatch ready? Please type y or n (yes or no): ")
    reply = input()

    while not (reply == "y" or reply == "Y" or retries <= 3):
        print("Is the stopwatch ready? Please type y or n (yes or no): ")
        reply = input()
        retries += 1
 
    # Ensure DUT is ON
    man_sys_tst_004.check_dut_is_powered_on()

    # Check the activation passed
    man_sys_tst_004.check_dut_activated_ok()

    # Check LRS COM port for messages
    man_sys_tst_004.check_lrs_com_port_activations()

    # Check resonant frequency messages
    man_sys_tst_004.check_resonant_frequency()

    # Ensure DUT is OFF
    man_sys_tst_004.check_dut_is_powered_off()

    # Ensure DUT is ON
    man_sys_tst_004.check_dut_is_powered_on()

    # Check resonant frequency and LRS activation time
    man_sys_tst_004.check_lrs_activation_time()
    
    # Ensure DUT is OFF
    man_sys_tst_004.check_dut_is_powered_off()

    # If we got this far, the test is complete and has passed
    # Open test report file
    with open(man_sys_tst_004.test_report_file, 'a') as f:

        # Test complete
        f.write("\n\nSysTst_Manual_00004 Test Complete : PASS") 
        print("\n\nSysTst_Manual_00004 Test Complete : PASS") 
    # close test report file
    f.close()

   