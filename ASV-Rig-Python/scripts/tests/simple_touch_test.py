
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

        # create instance of button
        pe_button = Button()

        # Select Ardvaark I2C
        logger.info('_perform_startup_and_scan: Select Ardvaark I2C...')
        asv.touch_panel.select_aa_i2c()


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
        logger.info("_perform_startup_and_scan: waiting to send power up command to the DUT...")

        # Wait
        time.sleep(5)

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

        # Check is USB is connected
        usb_on = asv.ni_daq.dout.is_usb_en()
        logger.info("_perform_startup_and_scan: checking is USB is enabled... - USB is '%s'", usb_on)

        # Wait for screen to sleep
        time.sleep(11)

        loop1 = 3
        loop2 = 3
        loop_count = 1

        while loop_count <= loop1:

            # Wake screen
            # print("USB " + str(asv.ni_daq.dout.is_usb_en()) + " - Sending wake up touch whilst DUT is in low power " + str(loop_count) + " to screen...")
            logger.info("USB '%s' - Sending wake up touch '%d' when DUT is in low power...", asv.ni_daq.dout.is_usb_en(), loop_count)
            asv.touch_panel.touch("wakeup_touch")
            # Send touch lifted message
            asv.touch_panel.transmit_touch_lifted("wakeup_touch_lift_start", "wakeup_touch_lift_end")

            # Wait for screen to sleep
            loop_count += 1

            if loop_count <= loop1:
                time.sleep(22)

        # reset count
        loop_count = 1
        time.sleep(5)

        while loop_count <= loop2:

            # Wake screen
            # print("USB " + str(asv.ni_daq.dout.is_usb_en()) + " - Sending wake up touch when DUT is active " + str(loop_count))
            logger.info("USB '%s' - Sending wake up touch '%d' when DUT is active...", asv.ni_daq.dout.is_usb_en(), loop_count)
            asv.touch_panel.touch("wakeup_touch")
            # Send touch lifted message
            asv.touch_panel.transmit_touch_lifted("wakeup_touch_lift_start", "wakeup_touch_lift_end")

            # Wait
            loop_count += 1
            time.sleep(5)


        # Wake screen
        print("Sending wake up touch " + str(loop_count) + " to screen...")
        asv.touch_panel.touch("wakeup_touch")
        # Send touch lifted message
        asv.touch_panel.transmit_touch_lifted("wakeup_touch_lift_start", "wakeup_touch_lift_end")

        # Check screen lights up
        time.sleep(5)

        # Simulate a scan start LCD touch
        logger.info("Sending start scan touch to screen...")
        asv.touch_panel.touch("scan_button_touch")
        # Send touch lifted message
        asv.touch_panel.transmit_touch_lifted("scan_button_touch_lift_start", "scan_button_touch_lift_end")

        # Run the basic scanning sequence
        logger.info('_perform_startup_and_scan: executing the scanning sequence')
        BasicScanning().execute(asv, scan_data)

        # Select DUT I2C
        logger.info('_perform_startup_and_scan: Select DUT I2C...')
        asv.touch_panel.select_tp_i2c()

        # Disable USB
        time.sleep(10)
        logger.info('_perform_startup_and_scan: finished scan, disabling USB passthrough...')
        asv.ni_daq.dout.set_usb_en(False)

        # Select DUT I2C
        asv.touch_panel.select_tp_i2c()

        # Turn DUT OFF
        pe_button.send_button_delay_off_command()


if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('tuning_file', type=str, help='Encoder tuning CSV playback data filename')
    parser.add_argument('scanning_file', type=str, help='Encoder and signal scanning CSV playback data filename')
    args = parser.parse_args()
    logger.info("__main__: tuning_file = '%s', scanning_file = '%s'", args.tuning_file, args.scanning_file)
    _perform_startup_and_scan(PlaybackData(args.tuning_file), PlaybackData(args.scanning_file))


    # Finished
    logger.info("__main__: Finished...")
