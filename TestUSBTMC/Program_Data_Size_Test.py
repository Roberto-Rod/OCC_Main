from datetime import datetime
from pickle import FALSE, TRUE

def test_code_space_usage():

    with open(test_report_file, 'a') as f:
        
        # LSC project
        print("Verifying SRS-003 Program memory size for dsPIC33CK128MP203...")
        f.write("\nVerifying SRS-003 Program memory size for dsPIC33CK128MP203...")
        with open('C:/Releases/PM1/LSC-v1.04/PM1-LSC-1.04/PM1-LSC-1.04/LSC_Firmware.X/dist/default/production/LSC_Firmware.X.production.map') as file:
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

        # PDA project
        print("Verifying SRS-003 Program memory size for PIC32MZ1024EFH100...")
        f.write("\nVerifying SRS-003 Program memory size for PIC32MZ1024EFH100...")
        with open('C:/Releases/PM1/PDA-v1.13/PDA-v1.13/PDA-v1.13/firmware/PDAB_Firmware.X/dist/PIC32MZ2048EFH100/production/PDAB_Firmware.X.production.map') as file:
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
        
        # PE project
        print("Verifying SRS-003 Program memory size for PIC24FJ64GA702...")
        f.write("\nVerifying SRS-003 Program memory size for PIC24FJ64GA702...")
        with open('C:/Releases/PM1/PE-v1.03/PE-v1.03/PM1-PE-v1.03/PE-Module/Environment-Firmware.X/dist/default/production/Environment-Firmware.X.production.map') as file:
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

        # PI project
        print("Verifying SRS-003 Program memory size for PIC32MZ2064DAR169...")
        f.write("\nVerifying SRS-003 Program memory size for PIC32MZ2064DAR169...")
        with open('C:/Releases/PM1/PI-v1.14/PI-Module/PIB_Firmware/firmware/PIB_Firmware.X/dist/Main_Board_Rev_C/production/PIB_Firmware.X.production.map') as file:
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

def test_data_space_usage():

    with open(test_report_file, 'a') as f:

        # LSC project
        # print("Verifying SRS-004 Data memory size for " + target_device + "...")
        print("Verifying SRS-004 Data memory size for dsPIC33CK128MP203...")
        f.write("\nVerifying SRS-004 Data memory size for dsPIC33CK128MP203...")
        with open('C:/Releases/PM1/LSC-v1.04/PM1-LSC-1.04/PM1-LSC-1.04/LSC_Firmware.X/dist/default/production/LSC_Firmware.X.production.map') as file:
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
        print("Verifying SRS-004 Data memory size for PIC32MZ1024EFH100...")
        f.write("\nVerifying SRS-004 Data memory size for PIC32MZ1024EFH100...")
        with open('C:/Releases/PM1/PDA-v1.13/PDA-v1.13/PDA-v1.13/firmware/PDAB_Firmware.X/dist/PIC32MZ2048EFH100/production/PDAB_Firmware.X.production.map') as file:
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
        print("Verifying SRS-004 Data memory size for PIC24FJ64GA702...")
        f.write("\nVerifying SRS-004 Data memory size for PIC24FJ64GA702...")
        with open('C:/Releases/PM1/PE-v1.03/PE-v1.03/PM1-PE-v1.03/PE-Module/Environment-Firmware.X/dist/default/production/Environment-Firmware.X.production.map') as file:
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
        print("Verifying SRS-004 Data memory size for PIC32MZ2064DAR169...")
        f.write("\nVerifying SRS-004 Data memory size for PIC32MZ2064DAR169...")
        with open('C:/Releases/PM1/PI-v1.14/PI-Module/PIB_Firmware/firmware/PIB_Firmware.X/dist/Main_Board_Rev_C/production/PIB_Firmware.X.production.map') as file:
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
        
def get_test_report_header_details():

    # Take note of date and time
    test_start_time = datetime.now().strftime("%m/%d/%Y, %H:%M:%S")
    line1 = "Date: " + test_start_time 
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
        header = [line1, line2, line3, line4, line5, line6, line7]
        f.writelines(header)
    f.close()

# Define the code and data space limits for all microcontrollers
dsPIC33CK128MP203_code_limit    = 0x19999
PIC32MZ1024EFH100_code_limit    = 0xCCCCC
PIC24FJ64GA702_code_limit       = 0x19999
PIC32MZ2064DAR169_code_limit    = 0x199999
dsPIC33CK128MP203_data_limit    = 0x3999
PIC32MZ1024EFH100_data_limit    = 0x73333
PIC24FJ64GA702_data_limit       = 0x3999
PIC32MZ2064DAR169_data_limit    = 0x90000

date = datetime.now().strftime("_%Y_%m_%d_%H_%M_%S")
test_report_file = "SysTst_Manual-00001_" + date + ".txt"

if __name__ == '__main__':

    # Create the test report file
    get_test_report_header_details()

    # Check code and data space
    
    if test_code_space_usage() == TRUE and test_data_space_usage() == TRUE:
        print("\nSysTst_Manual-00001 Test Complete: PASS")
        with open(test_report_file, 'a') as f:
            f.write("\nSysTst_Manual-00001 Test Complete: PASS")
        f.close()
    else:
        print("\nSysTst_Manual-00001 Test Complete: FAIL")
        with open(test_report_file, 'a') as f:
            f.write("\nSysTst_Manual-00001 Test Complete: FAIL")
        f.close()

