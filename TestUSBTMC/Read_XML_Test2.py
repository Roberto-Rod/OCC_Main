

import re
from posixpath import split
import xml.etree.ElementTree as ET
from builtins import map

def test_coding_language_selection(target_device):

    if(target_device == "dsPIC33CK128MP203"):
        # LSC project
        tree = ET.parse("C:/Releases/PM1/LSC-v1.04/PM1-LSC-1.04/PM1-LSC-1.04/LSC_Firmware.X/nbproject/configurations.xml")
    elif (target_device == "PIC32MZ1024EFH100"):
        # PDA project
        tree = ET.parse("C:/Releases/PM1/PDA-v1.13\PDA-v1.13/PDA-v1.13/firmware/PDAB_Firmware.X/nbproject/configurations.xml")
    elif (target_device == "PIC24FJ64GA702"):
        # PE project
        tree = ET.parse("C:/Releases/PM1/PE-v1.03/PE-v1.03/PM1-PE-v1.03/PE-Module/Environment-Firmware.X/nbproject/configurations.xml")
    elif (target_device == "PIC32MZ2064DAR169"):
        # PI project
        tree = ET.parse("C:/Releases/PM1/PI-v1.14/PI-Module/PIB_Firmware/firmware/PIB_Firmware.X/nbproject/configurations.xml")
    else:
        print("Unknown device selection.")
        return

    root = tree.getroot()

    print("Verifying SRS-001 Coding language for " + target_device + "...")
    for itemPath in root.iter('itemPath'):
        #print(itemPath.text)
        file_list = itemPath.text.split('.')
        #print(file_list)

        # #if (file_list[1] != "NULL")
        file_ext_list = str(file_list[-1])
        #print(file_ext_list)

        # if file_ext_list != "h" and file_ext_list != "c" and file_ext_list != "S" and file_ext_list != "s" and file_ext_list != "mc3" and file_ext_list != "yml" and file_ext_list != "xml" and file_ext_list != "prj" and file_ext_list != "ld" and file_ext_list != "Makefile":
        #     print("FAILED, project includes prohibited files: " + file_list[0] + "." + file_ext_list)
        # # else:
        #     print("PASS")
        
        try:
            assert file_ext_list == "h" or file_ext_list == "c" or file_ext_list == "S" or file_ext_list == "s" or file_ext_list == "mc3" or file_ext_list == "yml" or file_ext_list == "xml" or file_ext_list == "prj" or file_ext_list == "ld" or file_ext_list == "Makefile", 'FAILED. Project includes prohibited source files: ' + file_ext_list
            #print("PASS")
        except AssertionError as error:
            print(error)


def test_target_device_selection(target_device):

    if(target_device == "dsPIC33CK128MP203"):
        # LSC project
        tree = ET.parse("C:/Releases/PM1/LSC-v1.04/PM1-LSC-1.04/PM1-LSC-1.04/LSC_Firmware.X/nbproject/configurations.xml")
    elif (target_device == "PIC32MZ1024EFH100"):
        # PDA project
        tree = ET.parse("C:/Releases/PM1/PDA-v1.13\PDA-v1.13/PDA-v1.13/firmware/PDAB_Firmware.X/nbproject/configurations.xml")
    elif (target_device == "PIC24FJ64GA702"):
        # PE project
        tree = ET.parse("C:/Releases/PM1/PE-v1.03/PE-v1.03/PM1-PE-v1.03/PE-Module/Environment-Firmware.X/nbproject/configurations.xml")
    elif (target_device == "PIC32MZ2064DAR169"):
        # PI project
        tree = ET.parse("C:/Releases/PM1/PI-v1.14/PI-Module/PIB_Firmware/firmware/PIB_Firmware.X/nbproject/configurations.xml")
    else:
        print("Unknown device selection.")
        return 

    root = tree.getroot()

    for targetDevice in root.iter('targetDevice'):
        print("Verifying SRS-002 Processor requirements for " + target_device + "...")

        # Verify it is the correct micrcontroller for this project configuration
        # if(targetDevice.text != target_device):
        #     print("FAILED. Wrong device selection:", targetDevice.text)
        
        try:
            assert targetDevice.text == target_device, 'FAILED. Wrong device selection, expected: ' + target_device
            print("PASS")
        except AssertionError as error:
            print(error)

if __name__ == '__main__':

    # Test 
    test_target_device_selection("dsPIC33CK128MP203")
    test_coding_language_selection("dsPIC33CK128MP203")
    # Test 
    test_target_device_selection("PIC32MZ1024EFH100")
    test_coding_language_selection("PIC32MZ1024EFH100")
    # Test 
    test_target_device_selection("PIC24FJ64GA702")
    test_coding_language_selection("PIC24FJ64GA702")
    # Test 
    test_target_device_selection("PIC32MZ2064DAR169")
    test_coding_language_selection("PIC32MZ2064DAR169")
