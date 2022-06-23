#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Basic Startup Script Implementation."""

import argparse
from logging import getLogger

from framework.asv_control import AsvControl
from framework.util.data import PlaybackData
from framework.sequence.tuning import BasicTuning

logger = getLogger()

def _perform_startup(data: PlaybackData):
    """Power on the Pachymeter and support the initial boot up and tuning sequence.

       The sequence is as follows:

       Set VOFF = 2.50V and VSIG = 0.00V.
       Power the DUT up (performed manually for now).
       Run the basic tuning sequence (from sequences).

       :param data (PlaybackData): the encoder playback data to be replayed during the tuning sequence.
    """
    with AsvControl() as asv:
        logger.info("_perform_startup: data = '%s'", data.get_fname())
        # Ask the operator to power up the DUT
        logger.info('_perform_startup: power up the DUT')
        # Run the basic tuning sequence
        logger.info('_perform_startup: executing the tuning sequence')
        BasicTuning().execute(asv, data)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('tuning_file', type=str, help='Encoder tuning CSV playback data filename')
    args = parser.parse_args()
    logger.info("__main__: tuning_file = '%s'", args.tuning_file)
    _perform_startup(PlaybackData(args.tuning_file))
