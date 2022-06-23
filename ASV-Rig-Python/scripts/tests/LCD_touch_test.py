
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Basic Startup and Scan Script Implementation."""

import time
import argparse
from logging import getLogger

from framework.asv_control import AsvControl
from framework.util.data import PlaybackData
from framework.sequence.scanning import BasicScanning
from framework.sequence.tuning import BasicTuning

from framework.device.aardvark_py import *
from framework.module.button import Button


logger = getLogger()

def _perform_startup_and_scan(tune_data: PlaybackData, scan_data: PlaybackData):
    """Power on the Pachymeter, support the initial boot up and tuning sequence and then perform a basic scanning sequence.
       The sequence is as follows:
       Set VOFF = 2.50V and VSIG = 0.00V.
       Power the DUT up (performed via UART commands to PE PESS).
       Run the basic tuning sequence (from sequences).
       Run the basic scanning sequence (from sequences).
       :param tune_data (PlaybackData): the encoder playback data to be replayed during the tuning sequence.
       :param scan_data (PlaybackData): the encoder playback data to be replayed during the scanning sequence.
    """
    with AsvControl() as asv:
        logger.info("_perform_startup_and_scan: tune_data = '%s', scan_data = '%s'", tune_data.get_fname(), scan_data.get_fname())

        # create instanbce of button
        pe_button = Button()

        # Select DUT I2C
        asv.touch_panel.select_tp_i2c()

        # Check is USB is connected
        logger.info('_perform_startup_and_scan: checking is USB is enabled...')
        usb_on = asv.ni_daq.dout.is_usb_en()

        if usb_on:
            logger.info('_perform_startup_and_scan: USB is enabled. Disabling before powering up the DUT...')
            # Disable USB pass through
            asv.ni_daq.dout.set_usb_en(False)
        else:
            logger.info('_perform_startup_and_scan: USB is disabled')

        # Wait to send command to power up the DUT
        logger.info('_perform_startup_and_scan: waiting to send power up command to the DUT...')

        # Wait
        time.sleep(2)

        # Simulate a button press to power up the DUT
        # ping the device
        pe_button.send_ping_command()

        # Send ON command
        logger.info('_perform_startup_and_scan: powering up the DUT')
        pe_button.send_on_command()

        # Run the basic tuning sequence
        logger.info('_perform_startup_and_scan: executing the tuning sequence')
        BasicTuning().execute(asv, tune_data)

        # Enable USB
        logger.info('_perform_startup_and_scan: enabling USB so that scan data is collected. Ensure the data collection tool is connected...')
        asv.ni_daq.dout.set_usb_en(True)
        time.sleep(10)

        # # Wait for screen to sleep
        # time.sleep(150)


        # # Turn DUT OFF
        # pe_button.send_button_delay_off_command()


if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('tuning_file', type=str, help='Encoder tuning CSV playback data filename')
    parser.add_argument('scanning_file', type=str, help='Encoder and signal scanning CSV playback data filename')
    args = parser.parse_args()
    logger.info("__main__: tuning_file = '%s', scanning_file = '%s'", args.tuning_file, args.scanning_file)
    _perform_startup_and_scan(PlaybackData(args.tuning_file), PlaybackData(args.scanning_file))


    # Finished
    logger.info("__main__: Finished...")
