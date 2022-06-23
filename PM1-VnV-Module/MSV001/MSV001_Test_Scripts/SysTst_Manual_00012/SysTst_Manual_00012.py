import os
import sys
from datetime import datetime
from pickle import FALSE, TRUE


class SysTst_Manual_00012(object):
    """
        This class implements the SysTst_Manual_00012 test procedure from MSV-001 protocol.
    """
    def __init__(self) -> None:

        self.CCT_ACCURACY_MAX = 5.0
        self.artifact1_dict = {}
        self.art1_measurements_dict = {}
        self.artifact2_dict = {}
        self.art2_measurements_dict = {}
        self.artifact3_dict = {}
        self.art3_measurements_dict = {}
        self.test_fail = []
        self.date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
        self.test_report_file = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00012/SysTst_Manual_00012" + self.date + ".txt"

    def get_test_report_header_details(self):
        """
            This function creates a test report text file
        """
        # Title line
        self.title = "Software Verification Specification MSV001 - SysTst_Manual_00012 Test\n"

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

        self.MSV001_log_folder_dir = "C:/Temp/MSV001/MSV001_Logs/SysTst_Manual_00012"

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
                print("\nPlease ensure test prerequisits are met before launching the SysTst_Manual_00012.bat file. Exiting without execution...")
                f.write("\n\nTest prerequisits NOT met. Exiting without execution...")
                f.write("\n\nSysTst_Manual_00012 Test Incomplete : FAIL")
                # close test report file
                f.close()
                sys.exit()

        # close test report file
        f.close()

    def check_artifact_test_results(self, ref, num):

        with open(self.test_report_file, 'a') as f:

            if num == 1:

                print("Artifact " + str(ref))
                # Check measurements
                for i in self.art1_measurements_dict.get(2):
                    print("Artifact {} Measurement {}".format(ref, i))
                    f.write("\nArtifact {} measurements: {}".format(ref, i))

                    if abs(float(i) - float(self.artifact1_dict[2])) > self.CCT_ACCURACY_MAX:

                        print("SysTst_Manual_00012 - Artifact " + str(ref) + " Measurement exceeds limit: FAIL")
                        f.write("\nSysTst_Manual_00012 - Artifact " + str(ref) + " Measurement exceeds limit: FAIL")
                        self.test_fail.append(TRUE)
                    else:
                        print("SysTst_Manual_00012 -  Artifact " + str(ref) + " Measurement is within limits: PASS")
                        f.write("\nSysTst_Manual_00012 -  Artifact " + str(ref) + " Measurement is within limits: PASS")
                        self.test_fail.append(FALSE)

            elif num == 2:

                print("Artifact " + str(ref))
                # Check measurements
                for i in self.art2_measurements_dict.get(2):
                    print("Artifact {} Measurement {}".format(ref, i))
                    f.write("\nArtifact {} measurements: {}".format(ref, i))

                    if abs(float(i) - float(self.artifact2_dict[2])) > self.CCT_ACCURACY_MAX:

                        print("SysTst_Manual_00012 - Artifact " + str(ref) + " Measurement exceeds limit: FAIL")
                        f.write("\nSysTst_Manual_00012 - Artifact " + str(ref) + " Measurement exceeds limit: FAIL")
                        self.test_fail.append(TRUE)
                    else:
                        print("SysTst_Manual_00012 -  Artifact " + str(ref) + " Measurement is within limits: PASS")
                        f.write("\nSysTst_Manual_00012 -  Artifact " + str(ref) + " Measurement is within limits: PASS")
                        self.test_fail.append(FALSE)

            elif num == 3:

                print("Artifact " + str(ref))
                # Check measurements
                for i in self.art3_measurements_dict.get(2):
                    print("Artifact {} Measurement {}".format(ref, i))
                    f.write("\nArtifact {} measurements: {}".format(ref, i))

                    if abs(float(i) - float(self.artifact3_dict[2])) > self.CCT_ACCURACY_MAX:

                        print("SysTst_Manual_00012 - Artifact " + str(ref) + " Measurement exceeds limit: FAIL")
                        f.write("\nSysTst_Manual_00012 - Artifact " + str(ref) + " Measurement exceeds limit: FAIL")
                        self.test_fail.append(TRUE)
                    else:
                        print("SysTst_Manual_00012 -  Artifact " + str(ref) + " Measurement is within limits: PASS")
                        f.write("\nSysTst_Manual_00012 -  Artifact " + str(ref) + " Measurement is within limits: PASS")
                        self.test_fail.append(FALSE)

            else:
                print("Invalid test artifact number...") 
            
        # close test report file
        f.close() 
    
    def check_final_test_results(self):

        with open(self.test_report_file, 'a') as f:

            # print("Test results list", self.test_fail)
            # Check the final results list
            if TRUE in self.test_fail:
                print("SysTst_Manual_00012 - CCT Measurement Accuracy Test Complete: FAIL")
                f.write("\n\nSysTst_Manual_00012 - CCT Measurement Accuracy Test Complete: FAIL")
            else:
                print("SysTst_Manual_00012 - CCT Measurement Accuracy Test Complete: PASS")
                f.write("\n\nSysTst_Manual_00012 - CCT Measurement Accuracy Test Complete: PASS")
        
        # close test report file
        f.close()
    
    def get_artifact_measurements(self, ref, num):

        artifact_measurements = [] 
    
        i = 1

        while i <= 3:

            print("Please enter the test artifact " + str(num) + " measurement " + str(i) + ": ") 
            artifact_measurements.append(input())
            i += 1

        if num == 1:
            # Add measurements to the dictionary
            self.art1_measurements_dict = {1:ref, 2:artifact_measurements}
            print("SysTst_Manual_00012 - Artifact " + str(ref) + " measurements : ", self.art1_measurements_dict)
        elif num == 2:
            # Add measurements to the dictionary
            self.art2_measurements_dict = {1:ref, 2:artifact_measurements}
            print("SysTst_Manual_00012 - Artifact " + str(ref) + " measurements : ", self.art2_measurements_dict)
        elif num == 3:
            # Add measurements to the dictionary
            self.art3_measurements_dict = {1:ref, 2:artifact_measurements}
            print("SysTst_Manual_00012 - Artifact " + str(ref) + " measurements : ", self.art3_measurements_dict)
        else:
            print("Invalid test artifact number...") 

    
    def get_artifact_reference_and_thickness(self, num):

        with open(self.test_report_file, 'a') as f:

            artifact_ref = ''
            artifact_thickness = ''
            print("Please enter the test artifact " + str(num) + " reference: ")
            artifact_ref = input()
            print("Please enter the test artifact " + str(num) + " measurement known thickness value in um:")   
            artifact_thickness = float(input())

            if num == 1:

                self.artifact1_dict = dict({1:artifact_ref, 2:artifact_thickness})
                # print("Dict 1 : ", self.artifact1_dict)   
                # Write the artifact reference and corresponding data to the log file
                f.write("\nSysTst_Manual_00012 - Test artifact reference: " + str(self.artifact1_dict[1]) + "; Known thickness: " + str(self.artifact1_dict[2]))
            elif num == 2:

                self.artifact2_dict = dict({1:artifact_ref, 2:artifact_thickness})
                # print("Dict 2 : ", self.artifact2_dict)   
                # Write the artifact reference and corresponding data to the log file
                f.write("\nSysTst_Manual_00012 - Test artifact reference: " + str(self.artifact2_dict[1]) + "; Known thickness: " + str(self.artifact2_dict[2]))
            elif num == 3:

                self.artifact3_dict = dict({1:artifact_ref, 2:artifact_thickness})
                # print("Dict 3 : ", self.artifact3_dict)   
                # Write the artifact reference and corresponding data to the log file
                f.write("\nSysTst_Manual_00012 - Test artifact reference: " + str(self.artifact3_dict[1]) + "; Known thickness: " + str(self.artifact3_dict[2]))
            else:
                print("Invalid test artifact number...")   
      

        # close test report file
        f.close()
        return artifact_ref
   


            
if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00012
    """

    # Instantiate a test object
    man_sys_tst_012 = SysTst_Manual_00012()

    # Check if the test reports output directory exists, and create it if it does not exist
    man_sys_tst_012.check_test_log_folder_exists()
    
    # Create the test report file
    man_sys_tst_012.get_test_report_header_details()

    # Start the test procedure
    # Ensure test pre-requisits have been met
    man_sys_tst_012.check_prerequisits_are_met()

    # Request test artifacts reference and known thickness, get measurements, check results
    n = 1
    while n <= 1:

        test_artifact_ref = man_sys_tst_012.get_artifact_reference_and_thickness(n)

        # Request the measurements values
        man_sys_tst_012.get_artifact_measurements(test_artifact_ref, n)

        # Check results
        man_sys_tst_012.check_artifact_test_results(test_artifact_ref, n)

        n += 1
    
    # Check overall test results, if either of the artifacts had a measurement beyond limits, this should yield a FAIL
    man_sys_tst_012.check_final_test_results()

