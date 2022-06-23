import shutil, os
import sys
import json
import statistics
import time
import pandas as pd
from datetime import datetime
from pickle import FALSE, NONE, TRUE



mypath = "C:/Occuity/PM1V1"
version_string = "1.01 build 0"

class SysTst_Manual_00010(object):
    """
        This class implements the SysTst_Manual_00010 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:
        
        # self.logfile_handle = -1
        self.csv_scan_data_file_list = []
        self.json_scan_file_list = []
        self.bad_scans_list = []
        self.test_fail = TRUE
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00010/SysTst_Manual_00010" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00010 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00010"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00010.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00010 Test Incomplete : FAIL")
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
                    print("SysTst_Manual_00010 Scan Data Reliability Test : Data loaded - " , data_len , "rows.")
                    f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : Data loaded - " + str(data_len) + " rows.")
                # close test report file
                f.close()
                return data
         
    def process_new_files(self, new_files, old_files):

        with open(self.test_report_file, 'a') as f:

            for file in (new_files-old_files):
                ext = os.path.splitext(file)
                # print("ext[0] : ", ext[0])
                # print("ext[1] : ", ext[1])
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
                        self.check_data(data)
                    print("=================================================")
                    f.write("\n=================================================")
                if ext[1] == ".csv":
                    self.csv_scan_data_file_list.append(mypath + "/" + file)
                    # print("path ", mypath, "file ", file)
            # print("json file list", self.json_scan_file_list)
        # close test report file
        f.close()
        return new_files   
    
    def check_data(self, data):

        with open(self.test_report_file, 'a') as f:

            # go through each scan and extract data
            error_present = False

            for index, record in enumerate(data):

                bits_array = record['Header']['Status']['Flags']
                if index == 0:
                    new_gain = record['Header']['Status']['Gain']
                    new_scans_count = record['Header']['Status']['Count']
                    new_direction_bit = (bits_array & 0b100000000) == 256
                else:
                    new_gain = record['Header']['Status']['Gain']
                    new_scans_count = record['Header']['Status']['Count']
                    new_direction_bit = (bits_array & 0b100000000) == 256
                    # Check if the new scan is consecutive (allow 1 scan missing when gain changes)
                    if not record['Header']['IsComplete'] and\
                            ((new_gain == old_gain and (new_scans_count - old_scans_count) != 1) or
                            (new_gain != old_gain and (new_scans_count - old_scans_count) != 2)):
                        f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": missing scans.")
                        print("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": missing scans.")
                        # Check if this scan is already on the list and add it if it is not
                        if new_scans_count not in self.bad_scans_list:
                            self.bad_scans_list.append(new_scans_count)
                        error_present = True
                    # If the number of scans is > 25, then...
                    #if new_scans_count > 25:
                        # Check if the new scan direction is opposite to previous scan (allow same direction when gain changes)
                        #if (not record['Header']['IsComplete'] and index != len(data)-1) and\
                        #        ((new_direction_bit == old_direction_bit and new_gain == old_gain) or
                        #         (new_direction_bit != old_direction_bit and new_gain != old_gain)):
                        #    logdata_obj.print_log("Error in scan " + str(new_scans_count) + ": wrong scan direction.")
                        #    error_present = True

                # Check if IsComplete flag is in the last scan
                if record['Header']['IsComplete'] and index != len(data)-1:
                    f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": wrong IsComplete flag location.")
                    print("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": wrong IsComplete flag location.")
                    # Check if this scan is already on the list and add it if it is not
                    if new_scans_count not in self.bad_scans_list:
                        self.bad_scans_list.append(new_scans_count)
                    error_present = True

                # Check if the scan starts with 1, 2, 3 and ends with 5000, 4999, 4998
                if new_direction_bit:
                    if record['DataPoints'][-1] != 1 or\
                        record['DataPoints'][-2] != 2 or\
                        record['DataPoints'][-3] != 3 or\
                        record['DataPoints'][0] != 5000 or\
                        record['DataPoints'][1] != 4999 or\
                        record['DataPoints'][2] != 4998:
                        f.write("\nError in scan " + str(new_scans_count) + ": incorrect scan start or end.")
                        print("\nError in scan " + str(new_scans_count) + ": incorrect scan start or end.")
                        self.bad_scans_list.append(new_scans_count)
                        error_present = True
                else:
                    if record['DataPoints'][0] != 1 or\
                        record['DataPoints'][1] != 2 or\
                        record['DataPoints'][2] != 3 or\
                        record['DataPoints'][-1] != 5000 or\
                        record['DataPoints'][-2] != 4999 or\
                        record['DataPoints'][-3] != 4998:
                        f.write("\nError in scan " + str(new_scans_count) + ": incorrect scan start or end.")
                        print("\nError in scan " + str(new_scans_count) + ": incorrect scan start or end.")
                        # Check if this scan is already on the list and add it if it is not
                        if new_scans_count not in self.bad_scans_list:
                            self.bad_scans_list.append(new_scans_count)
                        error_present = True

                # Check zero offset is correct
                DC_offset = statistics.median(record['DataPoints'])
                if DC_offset < 100 and not record['Header']['IsComplete'] and index == len(data):
                    f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": wrong zero offset.")
                    print("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": wrong zero offset.")
                    # Check if this scan is already on the list and add it if it is not
                    if new_scans_count not in self.bad_scans_list:
                        self.bad_scans_list.append(new_scans_count)
                    error_present = True

                # Check if checksum is correct
                checksum_wrong = record['Header']['ChecksumWrong']
                if checksum_wrong != 0:
                    f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": wrong checksum.")
                    print("\nSysTst_Manual_00010 Scan Data Reliability Test : Error in scan " + str(new_scans_count) + ": wrong checksum.")
                    # Check if this scan is already on the list and add it if it is not
                    if new_scans_count not in self.bad_scans_list:
                        self.bad_scans_list.append(new_scans_count)
                    error_present = True

                old_gain = new_gain
                old_scans_count = new_scans_count
                # old_direction_bit = new_direction_bit

            if error_present:
                print("SysTst_Manual_00010 Scan Data Reliability Test : Errors found.")
                f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : Errors found.")
                # self.bad_scans_list.append(new_scans_count)
                print("bad scan list", self.bad_scans_list)
                # playsound("error.mp3")
            else:
                print("SysTst_Manual_00010 Scan Data Reliability Test : File correct.")
                f.write("\nSysTst_Manual_00010 Scan Data Reliability Test : File correct.")
                # playsound("success.mp3")

        # close test report file
        f.close()
    
    def list_files(self):
        temp_set = set()
        for file in os.listdir(mypath):
            full_path = os.path.join(mypath, file)
            if os.path.isfile(full_path):
                temp_set.add(file)
        return temp_set
    
    def move_scan_data_files(self):

        for file_js in self.json_scan_file_list:
            shutil.copy(file_js, self.MSV001_log_folder_dir)
        
        for file_csv in self.csv_scan_data_file_list:
            shutil.copy(file_csv, self.MSV001_log_folder_dir)
        
        print("CSV and JSON scan data files moved to MSV001_Logs/SysTst_Manual_00010 folder...")
    
    def check_bad_scan_file_list(self):

        print("Checking csv files...")

         # Open test report file
        with open(self.test_report_file, 'a') as f:

            # Check if the list is empty and only search for bad scans if it is not
            if not self.bad_scans_list == []:

                for csv_file in range(len(self.csv_scan_data_file_list)):

                    file_to_read = pd.read_csv(self.csv_scan_data_file_list[csv_file],header=None)
                    # Select only the first column which contains the scan count
                    file_to_read = file_to_read.iloc[:,[0]]
                    print("Checking csv file : ", self.csv_scan_data_file_list[csv_file])
                    # print("Scan count \n", file_to_read)

                    # Check if each bad scan has been included in the scan data csv files
                    for bad_scan in range(len(self.bad_scans_list)):

                        if bad_scan in file_to_read.values:
                            print("Bad scan ", str(self.bad_scans_list[bad_scan]), " found in csv file ", self.csv_scan_data_file_list[csv_file])
                        else:
                            self.test_fail = FALSE

            else:
                self.test_fail = FALSE
                print("Bad scan list is empty, there are no bad scans..")

            # Test complete
            # Check the test result
            if self.test_fail == True:
                f.write("\n\nSysTst_Manual_00010 Test Complete : FAIL") 
                print("\n\nSysTst_Manual_00010 Test Complete : FAIL")
            else:
                f.write("\n\nSysTst_Manual_00010 Test Complete : PASS") 
                print("\n\nSysTst_Manual_00010 Test Complete : PASS")

        # close test report file
        f.close()



    def main_loop(self):

        tic = time.time()
        reference_set = self.list_files()
        retry = 1
        reply = 'y'

        print("SysTst_Manual_00010 Scan Data - DCS version " + version_string + " started.")
        print("=================================================")

        with open(self.test_report_file, 'a') as f:
            f.write("SysTst_Manual_00010 Scan Data - DCS version " + version_string + " started.")
            f.write("\n=================================================")
        # close test report file
        f.close()
        
        while True and (reply == 'y' or reply == 'Y'):
            if not retry <= 3:
                break
            toc = time.time()
            if toc - tic > 1:
                tic = time.time()
                new_set = self.list_files()
                if len(new_set - reference_set) > 0:
                    
                    print("Retry: ", retry)
                    reference_set = self.process_new_files(new_set, reference_set)
                    retry += 1

                    # Ask if user wants to continue if the number of retries has not been reached
                    if retry <= 3:
                        reply = ''
                        print("Would you like to capture another scan file? Please type y or n (yes or no): ")
                        reply = input()

            
if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00010
    """

    # Instantiate a test object
    man_sys_tst_010 = SysTst_Manual_00010()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_010.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_010.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_010.check_prerequisits_are_met()

    # Run the scan collection tool to collect 3 scan files
    man_sys_tst_010.main_loop()

    # Copy the json and csv files and store in the log file directory
    man_sys_tst_010.move_scan_data_files()
    
    # Check the csv file list for bad scans
    man_sys_tst_010.check_bad_scan_file_list()


   