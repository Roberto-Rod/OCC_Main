from cmath import pi
from datetime import datetime
from pickle import FALSE, NONE, TRUE
from tkinter import Tk, filedialog
import sys
import os

# Define the code and data space limits for all microcontrollers
dsPIC33CK128MP203_code_limit    = 0x19999
PIC32MZ1024EFH100_code_limit    = 0xCCCCC
PIC24FJ64GA702_code_limit       = 0x19999
PIC32MZ2064DAR169_code_limit    = 0x199999
dsPIC33CK128MP203_data_limit    = 0x3999
PIC32MZ1024EFH100_data_limit    = 0x73333
PIC24FJ64GA702_data_limit       = 0x3999
PIC32MZ2064DAR169_data_limit    = 0x90000


class SysTst_Manual_00001(object):
    def __init__(self):
        # create and initialize variables for the project folder paths
        self.lsc_path = NONE
        self.pda_path = NONE
        self.pe_path  = NONE
        self.pi_path  = NONE

        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00001/SysTst_Manual_00001" + self.date + ".txt"
        
    def get_project_folder_path(self):
        root = Tk() # pointing root to Tk() to use it as Tk() in program.
        root.withdraw() # Hides small tkinter window.
        ''
        root.attributes('-topmost', True) # Opened windows will be active. above all windows despite of selection.
        ''
        open_file = filedialog.askdirectory() # Returns opened path as str
        # print(open_file)
        return open_file
    
    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00001 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00001"

        if not os.path.isdir(self.MSV001_log_folder_dir):
            print("MSV001_Logs does not exist. Creating directory...")

            try:
                os.makedirs(self.MSV001_log_folder_dir)
            except OSError as error:
                print(error)

    def test_code_space_usage(self, lsc_path, pda_path, pe_path, pi_path):

        self.lsc_path = lsc_path
        self.pda_path = pda_path
        self.pe_path = pe_path
        self.pi_path = pi_path

        with open(self.test_report_file, 'a') as f:
            
            # # LSC project
            # print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
            # self.lsc_path = get_project_folder_path()
            print("\nVerifying SRS-003 Program memory size for dsPIC33CK128MP203...")
            f.write("\n\nVerifying SRS-003 Program memory size for dsPIC33CK128MP203...")
            with open(self.lsc_path + '/dist/default/production/LSC_Firmware.X.production.map') as file:
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
            # self.pda_path = get_project_folder_path()
            print("Verifying SRS-003 Program memory size for PIC32MZ1024EFH100...")
            f.write("\nVerifying SRS-003 Program memory size for PIC32MZ1024EFH100...")
            with open(self.pda_path + '/dist/PIC32MZ2048EFH100/production/PDAB_Firmware.X.production.map') as file:
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
            # self.pe_path = get_project_folder_path()
            print("Verifying SRS-003 Program memory size for PIC24FJ64GA702...")
            f.write("\nVerifying SRS-003 Program memory size for PIC24FJ64GA702...")
            with open(self.pe_path + '/dist/default/production/Environment-Firmware.X.production.map') as file:
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
            # self.pi_path = get_project_folder_path()
            print("Verifying SRS-003 Program memory size for PIC32MZ2064DAR169...")
            f.write("\nVerifying SRS-003 Program memory size for PIC32MZ2064DAR169...")
            with open(self.pi_path + '/dist/Main_Board_Rev_C/production/PIB_Firmware.X.production.map') as file:
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

    def test_data_space_usage(self, lsc_path, pda_path, pe_path, pi_path):

        self.lsc_path = lsc_path
        self.pda_path = pda_path
        self.pe_path = pe_path
        self.pi_path = pi_path


        with open(self.test_report_file, 'a') as f:

            # LSC project
            print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
            # self.lsc_path = get_project_folder_path()
            print("Verifying SRS-004 Data memory size for dsPIC33CK128MP203...")
            f.write("\n\nVerifying SRS-004 Data memory size for dsPIC33CK128MP203...")
            with open(self.lsc_path + '/dist/default/production/LSC_Firmware.X.production.map') as file:
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
            # self.pda_path = get_project_folder_path()
            print("Verifying SRS-004 Data memory size for PIC32MZ1024EFH100...")
            f.write("\nVerifying SRS-004 Data memory size for PIC32MZ1024EFH100...")
            with open(self.pda_path + '/dist/PIC32MZ2048EFH100/production/PDAB_Firmware.X.production.map') as file:
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
            # self.pe_path = get_project_folder_path()
            print("Verifying SRS-004 Data memory size for PIC24FJ64GA702...")
            f.write("\nVerifying SRS-004 Data memory size for PIC24FJ64GA702...")
            with open(self.pe_path + '/dist/default/production/Environment-Firmware.X.production.map') as file:
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
            # self.pi_path = get_project_folder_path()
            print("Verifying SRS-004 Data memory size for PIC32MZ2064DAR169...")
            f.write("\nVerifying SRS-004 Data memory size for PIC32MZ2064DAR169...")
            with open(self.pi_path + '/dist/Main_Board_Rev_C/production/PIB_Firmware.X.production.map') as file:
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


if __name__ == '__main__':

     # Instantiate a test object
    man_sys_tst_001 = SysTst_Manual_00001()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_001.check_test_log_folder_exists()

    # Create the test report file
    man_sys_tst_001.get_test_report_header_details()

    # get project folder paths
    file_box_count = 0
    # LSC project
    while (man_sys_tst_001.lsc_path == NONE or man_sys_tst_001.lsc_path == '') and file_box_count < 3:
        print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
        man_sys_tst_001.lsc_path = man_sys_tst_001.get_project_folder_path()
        file_box_count += 1
    if (man_sys_tst_001.lsc_path == NONE or man_sys_tst_001.lsc_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        # PDA project
        while (man_sys_tst_001.pda_path == NONE or man_sys_tst_001.pda_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PDA MPLAB project using the dialog box.")
            man_sys_tst_001.pda_path = man_sys_tst_001.get_project_folder_path()
            print(man_sys_tst_001.pda_path)
            file_box_count += 1
    
    if (man_sys_tst_001.pda_path == NONE or man_sys_tst_001.pda_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        # PE project
        while (man_sys_tst_001.pe_path == NONE or man_sys_tst_001.pe_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PE MPLAB project using the dialog box.")
            man_sys_tst_001.pe_path = man_sys_tst_001.get_project_folder_path()
            file_box_count += 1
    
    if (man_sys_tst_001.pe_path == NONE or man_sys_tst_001.pe_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        # PI project
        while (man_sys_tst_001.pi_path == NONE or man_sys_tst_001.pi_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PI MPLAB project using the dialog box.")
            man_sys_tst_001.pi_path = man_sys_tst_001.get_project_folder_path()
            file_box_count += 1
    
    if (man_sys_tst_001.pi_path == NONE or man_sys_tst_001.pi_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()

    # Check code and data space 
    if (man_sys_tst_001.test_code_space_usage(man_sys_tst_001.lsc_path, man_sys_tst_001.pda_path, man_sys_tst_001.pe_path, man_sys_tst_001.pi_path) == TRUE 
        and man_sys_tst_001.test_data_space_usage(man_sys_tst_001.lsc_path, man_sys_tst_001.pda_path, man_sys_tst_001.pe_path, man_sys_tst_001.pi_path) == TRUE):
        print("\nSysTst_Manual_00001 Test Complete: PASS")
        with open(man_sys_tst_001.test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00001 Test Complete: PASS")
        f.close()
    else:
        print("\nSysTst_Manual-00001 Test Complete: FAIL")
        with open(man_sys_tst_001.test_report_file, 'a') as f:
            f.write("\n\nSysTst_Manual_00001 Test Complete: FAIL")
        f.close()

