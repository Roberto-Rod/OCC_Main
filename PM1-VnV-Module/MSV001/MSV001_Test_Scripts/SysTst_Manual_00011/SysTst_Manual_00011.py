import shutil, os
import sys
import json
import xlsxwriter
import statistics
import time
import pandas as pd
from datetime import datetime
from pickle import FALSE, NONE, TRUE



mypath = "C:/Occuity/PM1V1"
version_string = "1.01 build 0"

class SysTst_Manual_00011(object):
    """
        This class implements the SysTst_Manual_00011 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        # self.logfile_handle = -1
        self.csv_scan_data_file_list = []
        self.processed_excel_file_list = []
        self.json_scan_file_list = []
        self.bad_scans_list = []
        self.test_fail = TRUE
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00011/SysTst_Manual_00011" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00011 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00011"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00011.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00011 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close() 

    def is_open(self, file_name):
        if os.path.exists(file_name):
            try:
                os.rename(file_name, file_name) #can't rename an open file so an error will be thrown
                return False
            except:
                return True
        raise NameError

    def load_json(self, filename):

        # Open test report file
        with open(self.test_report_file, 'a') as f:
            data = []

            while self.is_open(filename):
                pass

            try:
                jsf = open(filename, 'r')
            except IOError:
                return data
            else:
                with jsf:
                    data = json.load(jsf)
                data_len = len(data)
                if data_len > 0:
                    print("SysTst_Manual_00011 Scan Data Reliability Test : Data loaded - " , data_len , "rows.")
                    f.write("\nSysTst_Manual_00011 Scan Data Reliability Test : Data loaded - " + str(data_len) + " rows.")
                # close test report file
                f.close()
                return data
         
    def process_new_files(self, new_files, old_files):

        with open(self.test_report_file, 'a') as f:

            for file in (new_files-old_files):
                ext = os.path.splitext(file)
                if ext[1] == ".json":
                    # f.write("\nprocess_new_files=================================================")
                    print("=================================================")
                    # f.write("\nprocess_new_files=================================================")
                    print("Processing : " + file)
                    f.write("\nProcessing : " + file)
                    data = []
                    while not data:
                        data = self.load_json(os.path.join(mypath, file))
                        self.json_scan_file_list.append(mypath + "/" + file)
                    print("=================================================")
                    f.write("\n=================================================")
                if ext[1] == ".csv":
                    self.csv_scan_data_file_list.append(mypath + "/" + file)
                    print("path ", mypath, "file ", file)
                    # Create an excel file with the same name as the CSV scan data file
                    self.processed_excel_file_list.append(self.MSV001_log_folder_dir + "/" + ext[0] + "_Analysis.xlsx")
                    print("Excel file list", self.processed_excel_file_list)
                    f.write("\nExcel file list", self.processed_excel_file_list)


            # print("json file list", self.json_scan_file_list)
        # close test report file
        f.close()
        return new_files   

    def list_files(self):
        temp_set = set()
        for file in os.listdir(mypath):
            full_path = os.path.join(mypath, file)
            if os.path.isfile(full_path):
                temp_set.add(file)
        return temp_set
    
    def move_scan_data_files(self):

        with open(self.test_report_file, 'a') as f:

            for file_js in self.json_scan_file_list:
                shutil.copy(file_js, self.MSV001_log_folder_dir)
            
            for file_csv in self.csv_scan_data_file_list:
                shutil.copy(file_csv, self.MSV001_log_folder_dir)
            
            print("CSV and JSON scan data files moved to MSV001_Logs/SysTst_Manual_00011 folder...")
            f.write("\nCSV and JSON scan data files moved to MSV001_Logs/SysTst_Manual_00011 folder...")
            print("SysTst_Manual_00011 has completed. Please process and verify the results.")
            f.write("\nSysTst_Manual_00011 has completed. Please process and verify the results.")
        
        # close test report file
        f.close()
    
    def create_excel_analysis_files(self):

        for file in self.processed_excel_file_list:

            workbook = xlsxwriter.Workbook(file)
            print("Creating the excel file...")
            worksheet = workbook.add_worksheet()

            worksheet.write('A1', 'ADC Samples')
            print("Writing to the excel file...")

            workbook.close()



    def main_loop(self):

        tic = time.time()
        reference_set = self.list_files()
        retry = 1
        reply = 'y'

        print("SysTst_Manual_00011 Check Scan Data Files - DCS version.")
        print("=================================================")

        with open(self.test_report_file, 'a') as f:
            f.write("\nSysTst_Manual_00011 Check Scan Data Files.")
            f.write("\n=================================================")
        # close test report file
        f.close()
        
        while True:
            if not retry <= 3:
                break
            toc = time.time()
            if toc - tic > 1:
                tic = time.time()
                new_set = self.list_files()
                if len(new_set - reference_set) > 0:
                    
                    print("Measurement: ", retry)
                    reference_set = self.process_new_files(new_set, reference_set)
                    retry += 1

            
if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00011
    """

    # Instantiate a test object
    man_sys_tst_011 = SysTst_Manual_00011()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_011.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_011.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_011.check_prerequisits_are_met()

    # Run the scan collection tool to collect 3 scan files
    man_sys_tst_011.main_loop()
    
    # Create the excel files to process the results
    man_sys_tst_011.create_excel_analysis_files()
  
    # Copy the json and csv files and store in the log file directory
    man_sys_tst_011.move_scan_data_files()

   