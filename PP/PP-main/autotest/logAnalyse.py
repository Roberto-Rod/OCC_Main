
from __future__ import print_function

#from bs4 import BeautifulSoup
#import urllib

import getopt


import sys
import codecs
import re


horizontal =""
reporterror=""

msg = "sss"

def printHelp() :
    print ("Paramaters are ")
    print (" -f inputfile   ")
    print (" -l       lengthways")
    print (" -x       extra additional fields ")
    print (" -e       report errors (Unloaded Volgate field) ")
    print (" -u       Uart generated file")
    print (" -p       Print pseudo pump if pump down time detected")
    print (" -v       Print version ")

try:
    opts, args = getopt.getopt(sys.argv[1:], 'f:leuvpx')
except getopt.error, msg:
    #sys.stdout = sys.stderr
    print (msg)
    #print (__doc__%globals() )
    printHelp()
    sys.exit(2)


inputfile = ""
debugdump = 0
extra = 0
checksequence = ""
uartversion = ""
displayversion = ""
pseudopumpdown= ""


for o, a in opts:
    if o == '-f':
        inputfile = a
    if o == '-x':
        extra = 1
    if o == '-l':
        horizontal = "aaa"
    if o == '-e':
        reporterror = "aaa"
    if o == '-s':
        checksequence = "aaa"
    if o == '-u':
        uartversion = "aaa"
    if o == '-v':
        displayversion = "aaa"
    if o == '-p':
        pseudopumpdown = "aaa"



if  displayversion != "":
    print ("Version debug demo only Version 0 ");
    exit(1)


lines = open( inputfile, "r" ).readlines()

# field sizes
fieldsizes = [2,2,4,2,2,1,1,2]

eeprom = []

fieldoffset = 0
bytecount = 0
extractedfield = 0
eepromoffset = 0
input_file_offset = 0

shiftcount = 0
seqcount = 0

def readBinaryFile() :

    bytecount = 0
    fieldoffset = 0
    input_file_offset = 0
    shiftcount = 0
    eepromoffset = 0


    for line in lines:

        words = line.split()

        if bytecount == 0 :
            bytecount = fieldsizes[ fieldoffset ]
            extractedfield = 0

        input_offset = words[2]
        input_offset = input_offset.replace ( ' ','')
        #print ( input_offset );
        if int(input_offset,10) != input_file_offset :
            print ("Fail: Input records fail to match expected sequence at record: ", end='' ); print ( input_file_offset );
            exit(1)

        input_file_offset += 1

        bin = words[4]
        bin = bin.replace ( ' ','')


        extractedfield += (int(bin,2) << ( shiftcount *8))
        shiftcount += 1

        bytecount -= 1
        if bytecount == 0 :
            shiftcount = 0
            eeprom.append( extractedfield  )
            #print "fieldoffset",fieldoffset, "value", extractedfield
            eepromoffset += 1
            fieldoffset += 1
            if fieldoffset >= len(fieldsizes) :
                fieldoffset = 0
                #print "last field ", extractedfield

    if input_file_offset != 256001:
        print ("Fail: input file is wrong size, it should be 256000 but is : ");
        print ( input_file_offset );
        exit(1)


#
# Read an EEPROM file which has been uploaded from the Eton device via the UART port 
#
def readUartBinaryFile() :

    bytecount = 0
    fieldoffset = 0
    input_file_offset = 0
    shiftcount = 0
    eepromoffset = 0
    global eeprom

    extractedfield = 0

    state = 0;

    for line in lines:

        words = line.split()

        off = words[0].find( "Test" )

        end = words[0].find( "End" )
	if end != -1:
		break;

	#print ( "val ", words[0] ) 

        if state == 1 :
            if ( off != -1  ) or ( words[0].isdigit() == False ) or ( words[0] == "") :

                #print (" off ", off );
                bytecount = 0
                fieldoffset = 0
                input_file_offset = 0
                shiftcount = 0
                eepromoffset = 0
                state = 0
                eeprom = []

        if state == 0 :

            if off != -1 :
                state = 1
            #print (" off ", off );

        else:
            val = words[0]

            # carful about the type 
	    val1 = int(val)

            # If ff's then 1000 is added to the count, take it away here
	    if ( val1 > 1000 ) :
		loopcount = val1  - 1000
		bin = "255"
	    else:
		loopcount = 1
		bin = val

            for  x in range(loopcount) :

                if bytecount == 0 :
                    bytecount = fieldsizes[ fieldoffset ]
                    extractedfield = 0
    
                input_file_offset += 1
    
                extractedfield += (int(bin,10) << ( shiftcount *8))
                shiftcount += 1
    
                bytecount -= 1
                if bytecount == 0 :
                    shiftcount = 0
                    eeprom.append( extractedfield  )
                    # print ("fieldoffset ",fieldoffset, "value ", extractedfield);
                    eepromoffset += 1
                    fieldoffset += 1
                    if fieldoffset >= len(fieldsizes) :
                        fieldoffset = 0
                        #print "last field ", extractedfield
    
                if input_file_offset > 256000:
                     print ("Fail: input file is wrong size, it should be 256000 but is : ");
                #    print ( input_file_offset );
                     return
  

    if input_file_offset != 256000:
        print ("Fail: input file is wrong size, it should be 256000 but is : ");
        print ( input_file_offset );
        return

#uartversion = "222"
if uartversion != "" :
    readUartBinaryFile()
else:
    readBinaryFile()



minutes = 1
offset = 0

state_names = [ 'SLEEP', 'PUMP_DOWN', 'THERAPY_DELIVERY','SHUT_DOWN','LEAK','NonRecoverableError','POST_Run','Fail_outofrange' ]


# Counts the first 30 bits in a int
# For use in duty cycle analyse
def countBits( value ):
    bit_count = 0
    for i in range(30):
        if (value & 1 ) != 0 :
            bit_count +=1
        value >>= 1

    return bit_count


def twos_comp(val, bits):
    """compute the 2's complement of int value val"""
    if (val & (1 << (bits - 1))) != 0: # if sign bit is set e.g., 8bit: 128-255
        val = val - (1 << bits)        # compute negative value
    return val     



print ("Time (min),Differencial Pressure (mbar),External Pressure (mbar),Pump Duty Cycle (%),Loaded battery Voltage (V),Temperature (deg),Temp ADC count,State,IPD Duration (s),Unloaded battery Voltage (V)" )

offset = 0

tick = 999
# detect if record is emtpy ( back ground eeprom ) and set values to 0
while offset < len(eeprom) :
    if eeprom[offset] == 0xFFFF :
        for i in range ( len(fieldsizes)) :
            eeprom[offset + i ] = 0
    offset += len(fieldsizes)

offset = 0
while offset < len(eeprom) :
    print ( minutes, end=',')
    if ( horizontal != "" ):
        print ( "");
    minutes += 1

    if ( horizontal != "" ):
        print ( "Differential Pressure (mbar),", end='' );
    print (eeprom[offset], end=',' ) ; offset +=1

    if ( horizontal != "" ):
        print ( "");
        print ( "External Pressure (mbar),", end='' );
    print (eeprom[offset], end=',' ) ; offset +=1

    # bit indicate if pump was on in that second
    bits = countBits(eeprom[offset])
    loadpercent = ( float(bits) / 30 ) * 100
    # if it is on in a second then its only on for 100ms within that second
    #loadpercent = loadpercent / 10
    if ( horizontal != "" ):
        print ( "");
        print ( "Pump Duty Cycle (%),", end='' );
        print ( countBits(eeprom[offset]), end=',');
    #print (eeprom[offset], end=',' ) ;
    print ( "%.4f"%loadpercent, end=',' );
    #print ( "%4.4x"%eeprom[offset], end=',' );  # print in binary look at the binary pattern
    offset +=1

    # Battery Voltage - input in milli volts
    battery_voltage = float(eeprom[offset])  # must be in milli volts
    battery_voltage = battery_voltage / 1000
    if ( battery_voltage > 3.2000 ):
        print ("");
        print ( "Loaded Battery voltage out of range ")
        print ( "%.3f"%battery_voltage, end=',' );
        exit (1)
    if ( horizontal != "" ):
        print ( "");
        print ( "Loaded battery Voltage (V),", end='' );
    #print (eeprom[offset], end=',' ) ;
    print ( "%.3f"%battery_voltage, end=',' );
    offset +=1


    # Temperature  - form the internal sensor
    temperature = eeprom[offset]
    rawtemp = twos_comp(temperature,16)
    # raw temp as negative or positive offset from 42.5
    display_centigrade = 42.5 + (float(rawtemp)/480)
    if rawtemp == 0 :
    	display_centigrade = 0;
    if ( horizontal != "" ):
        print ( "");
        print ( "Temp raw reading,", end='' );
	print (temperature, end=',' ) ;
        print ( "");
        print ( "Temperature (deg) ADC count,", end='' );

    if extra != 0 :
        if tick == 999:
            tick = temperature
        else:
            if tick != temperature:
                print ( "tick delta ", end='')
                print ( temperature - tick, end='' );
                print ( "")
                tick = temperature
        tick += 1;
        if tick > 255 : tick = 0


    print ( "%.1f"%display_centigrade, end=',' );
    offset +=1
    current_state = int( eeprom[offset])
    #print ( "current_state", end="")
    if extra != 0 :
        top = current_state & 0xC0
        current_state &= 0x3F
        if ( horizontal != "" ):
            print ( "")
        print ( "LEDS ", end='')
        if top & 0x80 : print ( "GREEN", end=',' )
        if top & 0x40 : print ( "ORANGE", end=',' )
        if (( top & 0xC0 ) == 0xC0 ) : print ( "ERROR BOTH LEDS" )
        print ( top, end=',')
    countDownTmp = float(eeprom[offset+1]) / 10
    if ( horizontal != "" ):
        if ( countDownTmp != 0.0 ) and ( pseudopumpdown != "" ) :
            print ( "");
            print ("State(Pseudo),PUMP_DOWN_IPD" );
    if ( horizontal != "" ):
        print ( "");
        print ( "State,", end='' );
    print (current_state, end=',' );
    print (state_names[current_state], end=',' );
    #print (eeprom[offset], end=',' ) ;
    offset +=1

    if ( horizontal != "" ):
        print ( "");
        print ( "IPD Duration (s),", end='' );
    countDown = float(eeprom[offset]) / 10
    print ( "%.1f"%countDown, end=',' );  offset +=1


    # print (eeprom[offset], end=',' )
    if (reporterror == "" ):
        if ( horizontal != "" ):
            print ( "");
            print ( "Unloaded battery Voltage (V),", end='' );
        #print (eeprom[offset] );
        # v = 0.0
        v = float(eeprom[offset]) / 1000
        print ( "%.3f"%v );
        offset +=1
    else:
        x = eeprom[offset]
        if ( checksequence != "" ):
            if ( x != seqcount ):
                print ( "");
                print ("Sequence Error ", end='');
        else:
            print ( "");
	    print ("Error value.... ");
            if ( x != 0 ) :
                if (( x & 0x0100 ) != 0 ):
                    print ( "Log Buffer problem: ", end='' );
                if (( x & 0x0200 ) != 0 ):
                    print ( "Auto Track Fail: ", end='' );
                if (( x & 0x0400 ) != 0 ):
                    print ( "Voltage Range: ", end='' );
                if (( x & 0x0800 ) != 0 ):
                    print ( "Cause Leak: ", end='' );
                if (( x & 0xf000 ) != 0 ):
                    print ( "General Error : ", end='' );
                print ( "State Error 0x", end='' );
	# remove the error count 
	x = x & 0xFF00	
        print ( "%4.4x"%x );
        seqcount += 100
        offset +=1


exit(1)
