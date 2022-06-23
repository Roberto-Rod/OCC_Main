#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Basic Startup and Scan Script Implementation."""

import argparse
from logging import getLogger

from framework.asv_control import AsvControl
from framework.util.data import PlaybackData
from framework.sequence.scanning import BasicScanning
from framework.sequence.tuning import BasicTuning

logger = getLogger()

def _perform_startup_and_scan(tune_data: PlaybackData, scan_data: PlaybackData):
    """Power on the Pachymeter, support the initial boot up and tuning sequence and then perform a basic scanning sequence.

       The sequence is as follows:

       Set VOFF = 2.50V and VSIG = 0.00V.
       Power the DUT up (performed manually for now).
       Run the basic tuning sequence (from sequences).
       Run the basic scanning sequence (from sequences).

       :param tune_data (PlaybackData): the encoder playback data to be replayed during the tuning sequence.
       :param scan_data (PlaybackData): the encoder playback data to be replayed during the scanning sequence.
    """
    with AsvControl() as asv:
        logger.info("_perform_startup_and_scan: tune_data = '%s', scan_data = '%s'", tune_data.get_fname(), scan_data.get_fname())
        # Ask the operator to power up the DUT
        logger.info('_perform_startup_and_scan: power up the DUT')
        # Run the basic tuning sequence
        logger.info('_perform_startup_and_scan: executing the tuning sequence')
        BasicTuning().execute(asv, tune_data)
        # Run the basic scanning sequence
        logger.info('_perform_startup_and_scan: executing the scanning sequence')
        BasicScanning().execute(asv, scan_data)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('tuning_file', type=str, help='Encoder tuning CSV playback data filename')
    parser.add_argument('scanning_file', type=str, help='Encoder and signal scanning CSV playback data filename')
    args = parser.parse_args()
    logger.info("__main__: tuning_file = '%s', scanning_file = '%s'", args.tuning_file, args.scanning_file)
    _perform_startup_and_scan(PlaybackData(args.tuning_file), PlaybackData(args.scanning_file))
