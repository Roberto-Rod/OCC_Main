#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Basic Scanning Script Implementation."""

import argparse
from logging import getLogger

from framework.asv_control import AsvControl
from framework.util.data import PlaybackData
from framework.sequence.scanning import BasicScanning

logger = getLogger()

def _perform_scan(data: PlaybackData):
    """Run a basic scanning sequence.

       The sequence is as follows:

       Run basic scanning sequence.

       This script assumes that the DUT is already running and tuning has completed.

       :param data (PlaybackData): the scan playback data to be replayed during the scanning sequence.
    """
    with AsvControl() as asv:
        logger.info("_perform_scanning: data = '%s'", data.get_fname())
        # Run the basic scanning sequence
        logger.info('_perform_scanning: executing the scanning sequence')
        BasicScanning().execute(asv, data)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('scanning_file', type=str, help='Encoder and signal scanning CSV playback data filename')
    args = parser.parse_args()
    logger.info("__main__: scanning_file = '%s'", args.scanning_file)
    _perform_scan(PlaybackData(args.scanning_file))
