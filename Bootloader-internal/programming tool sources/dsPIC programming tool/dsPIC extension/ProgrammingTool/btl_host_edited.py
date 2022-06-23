#!/usr/bin/env python

"""*****************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************"""

import os
import sys
import time
import serial
import optparse

#------------------------------------------------------------------------------
BL_CMD_UNLOCK       = 0xa0
BL_CMD_DATA         = 0xa1
BL_CMD_VERIFY       = 0xa2
BL_CMD_RESET        = 0xa3
BL_CMD_BKSWAP_RESET = 0xa4

BL_RESP_OK          = 0x50
BL_RESP_ERROR       = 0x51
BL_RESP_INVALID     = 0x52
BL_RESP_CRC_OK      = 0x53
BL_RESP_CRC_FAIL    = 0x54

BL_GUARD            = 0x5048434D

# Should be equal to Device Erase size
ERASE_SIZE        = 256

BOOTLOADER_SIZE     = 2048

# Supported Devices [ERASE_SIZE, BOOTLOADER_SIZE]
devices = {
            "SAME7X"    : [8192, 8192],
            "SAME5X"    : [8192, 8192],
            "SAMD5X"    : [8192, 8192],
            "SAMG5X"    : [8192, 8192],
            "SAMC2X"    : [256, 2048],
            "SAMD1X"    : [256, 2048],
            "SAMD2X"    : [256, 2048],
            "SAMDA1"    : [256, 2048],
            "SAML1X"    : [256, 2048],
            "SAML2X"    : [256, 2048],
            "SAMHA1"    : [256, 2048],
            "PIC32MK"   : [4096, 8192],
            "PIC32MZ"   : [16384, 16384],
            "PIC32MX"   : [1024, 4096],
}

#------------------------------------------------------------------------------
def error(text):
    sys.stderr.write('\nError: %s\n' % text)
    return True
    #sys.exit(-1)

#------------------------------------------------------------------------------
def warning(text):
    sys.stderr.write('\nWarning: %s\n' % text)

#------------------------------------------------------------------------------
def verbose(verb, text):
    if verb:
        print("\n" + text)

#------------------------------------------------------------------------------
def crc32_tab_gen():
    res = []

    for i in range(256):
        value = i

        for j in range(8):
            if value & 1:
                value = (value >> 1) ^ 0xedb88320
            else:
                value = value >> 1

        res += [value]

    return res

#------------------------------------------------------------------------------
def crc32(tab, data):
    crc = 0xffffffff

    for d in data:
        crc = tab[(crc ^ d) & 0xff] ^ (crc >> 8)

    return crc

#------------------------------------------------------------------------------
def uint32(v):
    return [(v >> 0) & 0xff, (v >> 8) & 0xff, (v >> 16) & 0xff, (v >> 24) & 0xff]

#------------------------------------------------------------------------------
def get_response(port):
    v = port.read()

    if len(v) == 0:
        return None
    elif len(v) > 1:
        error('invalid response received (size > 1)')

    return (v[0])

#------------------------------------------------------------------------------
def send_request(port, cmd, size, data):
    req = uint32(BL_GUARD) + size + [cmd] + data

    port.write(bytes(bytearray(req)))

    for i in range(20):
        resp = get_response(port)

        if (resp is None):
            warning('no response received, retrying %d' % (i+1))
            
            if(try_to_open_new_port(optionsG.port)):
                verbose(optionsG.verbose, 'PORT OK\n')
            else:
                verbose(optionsG.verbose, 'PORT N OK\n')
        else:
            return resp

    error('no response received, giving up')
    
    

# Print iterations progress
def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '|'):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)

    print ('\r%s |%s| %s%% %s \r' % (prefix, bar, percent, suffix), end =""),

    if iteration == total: 
        print()

#------------------------------------------------------------------------------
global optionsG, successG
successG = False

def define_options():
    global optionsG
    parser = optparse.OptionParser(usage = 'usage: %prog [options]')
    parser.add_option('-v', '--verbose', dest='verbose', help='enable verbose output', default=False, action='store_true')
    parser.add_option('-r', '--baud', dest='baud', help='UART baudrate', default=115200, metavar='BAUD')
    parser.add_option('-t', '--tune', dest='tune', help='auto-tune UART baudrate', default=False, action='store_true')
    parser.add_option('-i', '--interface', dest='port', help='communication interface', metavar='PATH')
    parser.add_option('-f', '--file', dest='file', help='binary file to program', metavar='FILE')
    parser.add_option('-a', '--address', dest='address', help='destination address', metavar='ADDR')
    parser.add_option('-p', '--sectorSize', dest='sectSize', help='Device Sector Size in Bytes', metavar='SectSize')
    parser.add_option('-b', '--boot', dest='boot', help='enable write to the bootloader area', default=False, action='store_true')
    parser.add_option('-s', '--swap', dest='swap', help='swap banks after programming', default=False, action='store_true')
    parser.add_option('-d', '--device', dest='device', help='target device (samc2x/samd1x/samd2x/samd5x/samda1/same7x/same5x/samg5x/saml2x/samha1/pic32mk/pic32mx/pic32mz)', metavar='DEV')

    (options, args) = parser.parse_args()
    optionsG = options

def main():
    global optionsG
    options = optionsG

    if options.port is None:
        error('communication port is required (try -h option)')
        return

    
    if options.file is None:
        error('file name is required (use -f option)')
        return

    if options.device is None:
        error('target device is required (use -d option)')
        return

    if options.address is None:
        error('destination address is required (use -a option)')
        return

    device = options.device.upper()

    if (device in devices):
        if (device == "PIC32MX"):
            if options.sectSize is None:
                error('device sector size is required (use -p option)')
                return

            ERASE_SIZE    = int(options.sectSize)
        else:
            ERASE_SIZE    = devices[device][0]

        BOOTLOADER_SIZE     = devices[device][1]
    else:
        error('invalid device')
        return

    if (options.swap == True):
        if ((device != "SAME5X") and (device != "SAMD5X") and (device != "PIC32MZ") and (device != "PIC32MK")):
            error('Bank Swapping not supported on this device')
            return

    try:
        address = int(options.address, 0)
    except ValueError as inst:
        error('invalid address value: %s' % options.address)
        return

    if (("SAM" in device)):
        if address < BOOTLOADER_SIZE and options.boot == False:
            error('address is within the bootlaoder area, use --boot options to unlock writes')
            return
    else:
        if options.boot == True:
            error('--boot option is not supported on this device')
            return
    
    port = None
    try:
        port = serial.Serial(options.port, options.baud, timeout=1)
    except serial.serialutil.SerialException as inst:
        error(inst)
        return

    if options.tune:
        verbose(options.verbose, 'Auto-tuning UART baudrate')
        port.send_break(duration=0.01)
        port.write(chr(0x55))

    try:
        data = data = [(x) for x in open(options.file, 'rb').read()]
    except Exception as inst:
        error(inst)
        return

    while len(data) % ERASE_SIZE > 0:
        data += [0xff]

    crc32_tab = crc32_tab_gen()
    crc = crc32(crc32_tab, data)

    size = len(data)

    verbose(options.verbose, 'Unlocking\n')
    if(port == None):
        error('...port == None')
        return
    resp = send_request(port, BL_CMD_UNLOCK, uint32(8), uint32(address) + uint32(size))

    if resp != BL_RESP_OK:
        error('invalid response code (0x%02x). Check that your file size and address are correct.' % resp)
        return

    # Create data blocks of ERASE_SIZE each
    blocks = [data[i:i + ERASE_SIZE] for i in range(0, len(data), ERASE_SIZE)]

    addr = address

    for idx, blk in enumerate(blocks):
        printProgressBar(idx+1, len(blocks), prefix = 'Programming:', suffix = 'Complete', length = 50)


        resp = send_request(port, BL_CMD_DATA, uint32(ERASE_SIZE + 4), uint32(addr) + blk)
        addr += ERASE_SIZE

        if resp != BL_RESP_OK:
            error('invalid response code (0x%02x)' % resp)
            return

    # Send Verification command
    verbose(options.verbose, 'Verification')

    resp = send_request(port, BL_CMD_VERIFY, uint32(4), uint32(crc))

    if resp == BL_RESP_CRC_OK:
        verbose(options.verbose, '... success')
        os.remove("py_in_run.temp")
        successG = True
    else:
        error('... fail (status = 0x%02x)' % resp)

    # Send Reboot Command
    if (options.swap == True):
        verbose(options.verbose, 'Swapping Bank And Rebooting')
        resp = send_request(port, BL_CMD_BKSWAP_RESET, uint32(16), uint32(0) * 4)
    else:
        verbose(options.verbose, 'Rebooting')
        resp = send_request(port, BL_CMD_RESET, uint32(16), uint32(0) * 4)

    if resp == BL_RESP_OK:
        verbose(options.verbose, 'Reboot Done')
    else:
        error('... Reset fail (status = 0x%02x)' % resp)

    port.close()

#------------------------------------------------------------------------------

def try_to_open_new_port(portname):
    ret = False
    test = serial.Serial(baudrate=9600, timeout=0, writeTimeout=0)
    test.port = portname
    try:
        test.open()
        if test.isOpen():
            test.read()
            test.close()
            ret = True
    except serial.serialutil.SerialException:
        pass
    return ret

define_options()

giveup_timeout = 10
while(successG == False):
    file2 = open(r"py_in_run.temp","w+")
    main()
    giveup_timeout -= 1
    if(giveup_timeout == 0):
        break

print("Too much of everything... :-(")




