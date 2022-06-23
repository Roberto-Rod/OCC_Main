
from posixpath import split
import xml.etree.ElementTree as ET
from datetime import datetime
from pickle import FALSE, NONE, TRUE
from tkinter import Tk, filedialog
import sys
import os


class SysTst_Manual_00002(object):
    """
        This class implements the SysTst_Manual_00002 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        # Define the microcontrollers for each PESS
        self.lsc_pess_device     = "dsPIC33CK128MP203"
        self.pda_pess_device     = "PIC32MZ1024EFH100"
        self.pe_pess_device      = "PIC24FJ64GA702"
        self.pi_pess_device      = "PIC32MZ2064DAR169"

        # create and initialize variables for the project folder paths
        self.lsc_path = NONE
        self.pda_path = NONE
        self.pe_path  = NONE
        self.pi_path  = NONE

        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00002/SysTst_Manual_00002" + self.date + ".txt"


    def get_project_folder_path(self):
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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00002"

        if not os.path.isdir(self.MSV001_log_folder_dir):
            print("MSV001_Logs does not exist. Creating directory...")

            try:
                os.makedirs(self.MSV001_log_folder_dir)
            except OSError as error:
                print(error)

    def test_coding_language_selection(self, target_device, folder_path):
        """
            Check the project configurations.xml file and ensure only valid source files are used.
        """
        self.target_device = target_device
        self.folder_path = folder_path

        tree = ET.parse(folder_path + "/configurations.xml")
        # "C:/Repos/PM1/PI-Module/PIB_Firmware/firmware/PIB_Firmware.X/nbproject/project.xml"
        # tree = ET.parse(folder_path + "/project.xml")
        root = tree.getroot()
        # print("Root tag is: " ,root.tag)
        # print("Root attrib is: " ,root.attrib)

        with open(self.test_report_file, 'a') as f:
            print("\nVerifying SRS-02010 Coding language for " + self.target_device + "...")
            f.write("\n\nVerifying SRS-02010 Coding language for " + self.target_device + "...")

            # Check target devices and confirm valid inputs
            try:
                assert ((self.target_device == self.lsc_pess_device) or (self.target_device == self.pda_pess_device) 
                        or (self.target_device == self.pe_pess_device) or (self.target_device == self.pi_pess_device)), 'FAIL. Invalid microcontroller selection'
            except AssertionError as error:
                print(error)
                f.write("\nSysTst_Manual_00002 Language Selection Test: FAIL - " + str(error))
                return FALSE
            
            # Start the test
            if (self.target_device == self.lsc_pess_device) or (self.target_device == self.pe_pess_device):
                for languageToolchain in root.iter('languageToolchain'):
                    languageToolchain = languageToolchain.text
                    for languageToolchainVersion in root.iter('languageToolchainVersion'):
                        languageToolchainVersion = languageToolchainVersion.text

                        # if (languageToolchain == "XC16") and (languageToolchainVersion == "1.60"):
                        #     print("PASS : ", languageToolchain, languageToolchainVersion)
                        # else:
                        #     print("FAIL : ", languageToolchain, languageToolchainVersion)

                        try:
                            assert ((languageToolchain == "XC16") and (languageToolchainVersion == "1.60")), 'Invalid compiler selection'
                        except AssertionError as message:
                            print("SysTst_Manual_00002 Language Selection Test: FAIL - " + str(message))
                            f.write("\nSysTst_Manual_00002 Language Selection Test: FAIL - " + str(message))
                            # Close the test report file
                            f.close()
                            return FALSE
            
            if (self.target_device == self.pda_pess_device) or (self.target_device == self.pi_pess_device):
                for languageToolchain in root.iter('languageToolchain'):
                    languageToolchain = languageToolchain.text
                    for languageToolchainVersion in root.iter('languageToolchainVersion'):
                        languageToolchainVersion = languageToolchainVersion.text

                        # if (languageToolchain == "XC32") and (languageToolchainVersion == "2.50"):
                        #     print("PASS : ", languageToolchain, languageToolchainVersion)
                        # else:
                        #     print("FAIL : ", languageToolchain, languageToolchainVersion)

                        try:
                            assert ((languageToolchain == "XC32") and (languageToolchainVersion == "2.50")), 'Invalid compiler selection'
                        except AssertionError as message:
                            print("SysTst_Manual_00002 Language Selection Test: FAIL - " + str(message))
                            f.write("\nSysTst_Manual_00002 Language Selection Test: FAIL - " + str(message))
                            # Close the test report file
                            f.close()
                            return FALSE
            print("SysTst_Manual_00002 Language Selection Test: PASS")
            f.write("\nSysTst_Manual_00002 Language Selection Test: PASS")
            # Close the test report file
            f.close()
            return TRUE
            
                
 
    def test_target_device_selection(self, target_device, folder_path):
        """
            Check the project configurations.xml file and ensure the correct microcontrollers are used.
        """

        self.target_device = target_device
        self.folder_path = folder_path

        tree = ET.parse(folder_path + "/configurations.xml")
        root = tree.getroot()

        with open(self.test_report_file, 'a') as f:
            print("\nVerifying SRS-02020 Processor requirements for " + self.target_device + "...")
            f.write("\n\nVerifying SRS-02020 Processor requirements for " + self.target_device + "...")

            # Check target devices and confirm valid inputs
            try:
                assert ((self.target_device == self.lsc_pess_device) or (self.target_device == self.pda_pess_device) 
                        or (self.target_device == self.pe_pess_device) or (self.target_device == self.pi_pess_device)), 'Invalid microcontroller selection'
            except AssertionError as error:
                print(error)
                f.write("\nSysTst_Manual_00002 Language Selection Test: FAIL - " + str(error))
                return FALSE

            for targetDevice in root.iter('targetDevice'):
                # Verify it is the correct microcontroller for this project configuration 
                try:
                    assert targetDevice.text == self.target_device, 'Wrong device selection, expected: ' + self.target_device + " - found: " + targetDevice.text
                    print("SysTst_Manual_00002 Language Selection Test: PASS")
                    f.write("\nSysTst_Manual_00002 Language Selection Test: PASS")
                except AssertionError as message:
                    print("SysTst_Manual_00002 Language Selection Test: FAIL - " + str(message))
                    f.write("\nSysTst_Manual_00002 Language Selection Test: FAIL - " + str(message))
                    # Close the test report file
                    f.close()
                    return FALSE

            # f.write("\nTarget Device Test for " + target_device + " PASSED.")
        # Close the test report file
        f.close()
        return TRUE

    




# date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
# test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00002/SysTst_Manual_00002" + date + ".txt"

if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00002
    """

     # Instantiate a test object
    man_sys_tst_002 = SysTst_Manual_00002()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_002.check_test_log_folder_exists()

    # Create the test report file
    # man_sys_tst_002.get_test_report_header_details()

    # get project folder paths
    file_box_count = 0
    # LSC project
    print("lsc_path = " + str(man_sys_tst_002.lsc_path))
    while (man_sys_tst_002.lsc_path == NONE or man_sys_tst_002.lsc_path == '') and file_box_count < 3:
        print("Please navigate to the nbproject folder for the LSC MPLAB project using the dialog box.")
        man_sys_tst_002.lsc_path = man_sys_tst_002.get_project_folder_path()
        file_box_count += 1
    print("lsc_path = " + str(man_sys_tst_002.lsc_path))
    if (man_sys_tst_002.lsc_path == NONE or man_sys_tst_002.lsc_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        # PDA project
        print("pda_path = " + str(man_sys_tst_002.pda_path))
        while (man_sys_tst_002.pda_path == NONE or man_sys_tst_002.pda_path == '') and file_box_count < 3:
            print("Please navigate to the nbproject folder for the PDA MPLAB project using the dialog box.")
            man_sys_tst_002.pda_path = man_sys_tst_002.get_project_folder_path()
            file_box_count += 1

    if (man_sys_tst_002.pda_path == NONE or man_sys_tst_002.pda_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        print("pe_path = " + str(man_sys_tst_002.pe_path))
        # PE project
        while (man_sys_tst_002.pe_path == NONE or man_sys_tst_002.pe_path == '') and file_box_count < 3:
            print("Please navigate to the nbproject folder for the PE MPLAB project using the dialog box.")
            man_sys_tst_002.pe_path = man_sys_tst_002.get_project_folder_path()
            file_box_count += 1

    if (man_sys_tst_002.pe_path == NONE or man_sys_tst_002.pe_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        print("pi_path = " + str(man_sys_tst_002.pi_path))
        # PI project
        while (man_sys_tst_002.pi_path == NONE or man_sys_tst_002.pi_path == '') and file_box_count < 3:
            print("Please navigate to the nbproject folder for the PI MPLAB project using the dialog box.")
            man_sys_tst_002.pi_path = man_sys_tst_002.get_project_folder_path()
            file_box_count += 1

    if (man_sys_tst_002.pi_path == NONE or man_sys_tst_002.pi_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    
    # Open test report file
    with open(man_sys_tst_002.test_report_file, 'a') as f:

        # Run the tests
        # Test target device selection
        if (   man_sys_tst_002.test_target_device_selection(man_sys_tst_002.lsc_pess_device, man_sys_tst_002.lsc_path)  != TRUE
            or man_sys_tst_002.test_target_device_selection(man_sys_tst_002.pda_pess_device, man_sys_tst_002.pda_path)  != TRUE 
            or man_sys_tst_002.test_target_device_selection(man_sys_tst_002.pe_pess_device, man_sys_tst_002.pe_path)    != TRUE
            or man_sys_tst_002.test_target_device_selection(man_sys_tst_002.pi_pess_device, man_sys_tst_002.pi_path))   != TRUE:

            target_device_test = FALSE
            print("\nSysTst_Manual_00002 - Target Selection Test: FAIL")
            # with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00002 - Target Selection Test: FAIL")
            # f.close()            
        else:
            target_device_test = TRUE
            print("\nSysTst_Manual_00002 - Target Selection Test: PASS")
            # with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00002 - Target Selection Test: PASS")
            # f.close()

        # Test coding language
        if (   man_sys_tst_002.test_coding_language_selection(man_sys_tst_002.lsc_pess_device, man_sys_tst_002.lsc_path)    != TRUE
            or man_sys_tst_002.test_coding_language_selection(man_sys_tst_002.pda_pess_device, man_sys_tst_002.pda_path)    != TRUE
            or man_sys_tst_002.test_coding_language_selection(man_sys_tst_002.pe_pess_device, man_sys_tst_002.pe_path)      != TRUE
            or man_sys_tst_002.test_coding_language_selection(man_sys_tst_002.pi_pess_device, man_sys_tst_002.pi_path))     != TRUE:  

            coding_language_test = FALSE
            print("\nSysTst_Manual_00002 - Coding Language Test: FAIL")
            # with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00002 - Coding Language Test: FAIL")
            # f.close()
        else:
            coding_language_test = TRUE
            print("\nSysTst_Manual_00002 - Coding Language Test: PASS")
            # with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00002 - Coding Language Test: PASS")
            # f.close()

        # Check final test results
        if target_device_test == TRUE and coding_language_test == TRUE:
            print("\nSysTst_Manual_00002 Test Complete: PASS")
            # with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00002 Test Complete: PASS")
            # f.close()
        else:
            print("\nSysTst_Manual-00002 Test Complete: FAIL")
            # with open(test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00002 Test Complete: FAIL")
    f.close()

   