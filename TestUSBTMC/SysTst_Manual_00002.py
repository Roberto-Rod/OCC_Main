
from posixpath import split
import xml.etree.ElementTree as ET
from datetime import datetime
from pickle import FALSE, NONE, TRUE
from tkinter import Tk, filedialog
import sys


def get_project_folder_path():
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

def get_test_report_header_details():
    """
        This function creates a test report text file
    """
    # Title line
    title = "Software Verification Specification SV001 - SysTst_Manual_00001 Test\n"

    # Take note of date and time
    test_start_time = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
    line1 = "\nDate: " + test_start_time
    # date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")

    # request tester's name
    print("Please enter your name:\n")
    tester_name = input()
    line2 = "\nTester Name: " + tester_name

    # request HW version
    print("Please enter the hardware version:\n")
    hw_version = input()
    line3 = "\nHardware Version: " + hw_version

    # request PE SW version
    print("Please enter the PE Controller SW version:\n")
    PE_sw_version = input()
    line4 = "\nPE Controller SW version: " + PE_sw_version

    # request PI SW version
    print("Please enter the PI Controller SW version:\n")
    PI_sw_version = input()
    line5 = "\nPI Controller SW version: " + PI_sw_version

    # request PDA SW version
    print("Please enter the PDA Controller SW version:\n")
    PDA_sw_version = input()
    line6 = "\nPDA Controller SW version: " + PDA_sw_version

    # request LSC SW version
    print("Please enter the LSC Controller SW version:\n")
    LSC_sw_version = input()
    line7 = "\nLSC Controller SW version: " + LSC_sw_version

    with open(test_report_file, 'w') as f:
        header = [title, line1, line2, line3, line4, line5, line6, line7]
        f.writelines(header)
    f.close()


def test_coding_language_selection(target_device, folder_path):
    """
        Check the project configurations.xml file and ensure only valid source files are used.
    """
    
    # Check target devices and confirm valid inputs
    try:
        assert (target_device == "dsPIC33CK128MP203") or (target_device == "PIC32MZ1024EFH100") or (target_device == "PIC24FJ64GA702") or (target_device == "PIC32MZ2064DAR169"), 'FAIL. Invalid microcontroller selection'
    except AssertionError as error:
        print(error)
        return FALSE
    

    tree = ET.parse(folder_path)
    root = tree.getroot()

    print("Verifying SRS-02010 Coding language for " + target_device + "...")
    for itemPath in root.iter('itemPath'):
        #print(itemPath.text)
        file_list = itemPath.text.split('.')
        #print(file_list)

        # #if (file_list[1] != "NULL")
        file_ext_list = str(file_list[-1])
        #print(file_ext_list)

        if file_ext_list != "h" and file_ext_list != "c" and file_ext_list != "sh" and file_ext_list != "S" and file_ext_list != "s" and file_ext_list != "mc3" and file_ext_list != "yml" and file_ext_list != "xml" and file_ext_list != "prj" and file_ext_list != "ld" and file_ext_list != "Makefile":
            print("FAILED, project includes prohibited files: " + file_list[0] + "." + file_ext_list)
        # else:
            print("PASS")
        
        # try:
        #     assert file_ext_list == "h" or file_ext_list == "c" or file_ext_list == "sh" or file_ext_list == "S" or file_ext_list == "s" or file_ext_list == "mc3" or file_ext_list == "yml" or file_ext_list == "xml" or file_ext_list == "prj" or file_ext_list == "ld" or file_ext_list == "Makefile", 'FAILED. Project includes prohibited source files: ' + file_ext_list
        #     #print("PASS")
        # except AssertionError as error:
        #     print(error)
    print("PASS")

def test_target_device_selection(target_device, folder_path):
    """
        Check the project configurations.xml file and ensure the correct microcontrollers are used.
    """

    # Check target devices and confirm valid inputs
    try:
        assert (target_device == "dsPIC33CK128MP203") or (target_device == "PIC32MZ1024EFH100") or (target_device == "PIC24FJ64GA702") or (target_device == "PIC32MZ2064DAR169"), 'FAIL. Invalid microcontroller selection'
    except AssertionError as error:
        print(error)
        return FALSE
    

    tree = ET.parse(folder_path)
    root = tree.getroot()

    for targetDevice in root.iter('targetDevice'):
        print("Verifying SRS-002 Processor requirements for " + target_device + "...")

        # Verify it is the correct microcontroller for this project configuration
        # if(targetDevice.text != target_device):
        #     print("FAILED. Wrong device selection:", targetDevice.text)
        
        try:
            assert targetDevice.text == target_device, 'FAILED. Wrong device selection, expected: ' + target_device
            print("PASS")
        except AssertionError as error:
            print(error)


date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
test_report_file = "./../SV001/SV001_Logs/SysTst_Manual_00002_" + date + ".txt"

if __name__ == '__main__':
    """
        PM1 Software Verification - MSV-001-SysTst_Manual_00002
    """

    #
    lsc_path = NONE
    pda_path = NONE
    pe_path  = NONE
    pi_path  = NONE

    # Create the test report file
    get_test_report_header_details()

    # get project folder paths
    file_box_count = 0
    # LSC project
    print("lsc_path = " + str(lsc_path))
    while (lsc_path == NONE or lsc_path == '') and file_box_count < 3:
        print("Please navigate to the Firmware.X folder for the LSC MPLAB project using the dialog box.")
        lsc_path = get_project_folder_path()
        file_box_count += 1
    print("lsc_path = " + str(lsc_path))
    if (lsc_path == NONE or lsc_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        # PDA project
        print("pda_path = " + str(pda_path))
        while (pda_path == NONE or pda_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PDA MPLAB project using the dialog box.")
            pda_path = get_project_folder_path()
            file_box_count += 1

    if (pda_path == NONE or pda_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        print("pe_path = " + str(pe_path))
        # PE project
        while (pe_path == NONE or pe_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PE MPLAB project using the dialog box.")
            pe_path = get_project_folder_path()
            file_box_count += 1

    if (pe_path == NONE or pe_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()
    else:

        file_box_count = 0
        print("pi_path = " + str(pi_path))
        # PI project
        while (pi_path == NONE or pi_path == '') and file_box_count < 3:
            print("Please navigate to the Firmware.X folder for the PI MPLAB project using the dialog box.")
            pi_path = get_project_folder_path()
            file_box_count += 1

    if (pi_path == NONE or pi_path == '') and file_box_count >= 3:
        print("Please enter a valid folder path for the project!!! Exiting without execution!!!")
        sys.exit()


    # Test 
    test_target_device_selection("dsPIC33CK128MP203", lsc_path)
    test_coding_language_selection("dsPIC33CK128MP203", lsc_path)
    # Test 
    test_target_device_selection("PIC32MZ1024EFH100", pda_path)
    test_coding_language_selection("PIC32MZ1024EFH100", pda_path)
    # Test 
    test_target_device_selection("PIC24FJ64GA702", pe_path)
    test_coding_language_selection("PIC24FJ64GA702", pe_path)
    # Test 
    test_target_device_selection("PIC32MZ2064DAR169", pi_path)
    test_coding_language_selection("PIC32MZ2064DAR169", pi_path)
