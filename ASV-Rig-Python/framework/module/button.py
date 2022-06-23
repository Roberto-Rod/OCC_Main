#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, occuity Limited <roberto.rodrigues@occuity.com>
# All rights reserved.
#


"""Pachymeter Automated Software Verification Rig DUT Button, and power ON/OFF Commands Implementation."""

import logging
import serial

from framework.util.config import Config

config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])
class Button():
    """
        This class implements the UART commands that allow powering the DUT ON and OFF,
        and implements the different button presses.
    """

    # port definition
    PE_port     = 'COM6'
    baudrate    = 115200
    parity      = serial.PARITY_NONE
    stopbits    = serial.STOPBITS_ONE
    bytesyze    = serial.EIGHTBITS
    time_out    = None
    # flowcontrol = serial.

    # Ping command format h(AF 45 1 10 E1 E2 FE)
    ping_command = (b'\xAF\x45\x01\x10\xE1\xE2\xFE')
    # ON command format h(55 00 55 00 AF 45 2 2 4F 4E E1 E2 5E)
    # Tells PE to turn the other PESS ON
    ON_command = (b'\x55\x00\x55\x00\xAF\x45\x02\x02\x4F\x4E\xE1\xE2\x5E')
    # Short button press command format h(55 00 55 00 AF 45 2 2 4F 4E E1 E2 5E)
    button_short_press_command = (b'\x55\x00\x55\x00\xAF\x45\x04\x05\x42\x54\x4E\x00\x0A\xE1\xE2\x08')
    # Button delay OFF command format \h(AF 45 4	5 42 54 4E	7 D1 E1 E2 3A)
    button_delay_off_command = (b'\xAF\x45\x04\x05\x42\x54\x4E\x07\xD1\xE1\xE2\x3A')
    # Button force OFF command format \h(AF 45 4 5 42 54 4E B B9 E1 E2 4E)
    button_force_off_command = (b'\xAF\x45\x04\x05\x42\x54\x4E\x0B\xB9\xE1\xE2\x4E')
    # OFF delayed command format h(AF 45 3 5 4F 46 46 5F 44 E1 E2 79)
    off_delayed_command = (b'\xAF\x45\x03\x05\x4F\x46\x46\x5F\x44\xE1\xE2\x79')

    def __init__(self):
         # open serial port
        self.ser = serial.Serial(self.PE_port, self.baudrate, self.bytesyze, self.parity, self.stopbits, self.time_out)
        logger.debug("Connection established with %s", self.ser.name)         # check which port was really used

    def check_connection_is_open(self):
        """
            Checks if the connection is open
        """
        return self.ser.isOpen()

    # read the device's response
    def read_dut_response(self):
        """
            Reads the respopnse from device
        """

        bytes_to_read = self.ser.inWaiting()
        # print("Bytes in input buffer", bytes_to_read)
        response = self.ser.readlines(bytes_to_read)
        # print(response)
        # Flush
        self.ser.flushInput()
        return response

    def send_ping_command(self):
        """
            Send the Ping command
        """
        self.ser.write(self.ping_command)
        # time.sleep(0.25)

    def send_on_command(self):
        """
            Send the ON command
        """
        self.ser.write(self.ON_command)
        # time.sleep(0.5)

    def send_short_button_command(self):
        """
            Send a short button press command
        """
        self.ser.write(self.button_short_press_command)
        # time.sleep(0.5)

    def send_button_delay_off_command(self):
        """
            Send the button delay OFF command
        """
        self.ser.write(self.button_delay_off_command)
        # time.sleep(0.5)

    def send_off_delayed_command(self):
        """
            Send the OFF delayed command
        """
        self.ser.write(self.off_delayed_command)
        # time.sleep(0.5)

    def send_force_off_command(self):
        """
            Send the force OFF command
        """
        self.ser.write(self.button_force_off_command)
        # time.sleep(0.5)

    def close_connection(self):
        """
            Close the UART connection
        """
        self.ser.close()
        print("Connection closed with ", self.PE_port)
