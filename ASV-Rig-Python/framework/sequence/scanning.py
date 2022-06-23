#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Scanning Sequence Implementation."""

import logging

from framework.asv_control import AsvControl
from framework.module.nidaq import ScanWaveformTask
from framework.util.config import Config
from framework.util.data import PlaybackData


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'BasicScanning'
]


class BasicScanning():
    """Class implementing basic scanning sequence."""

    def __init__(self):
        logger.debug('BasicScanning.__init__')

    def execute(self, asv: AsvControl, data: PlaybackData) -> None:
        """Performs the PM1 Pachymeter basic scanning sequence.

           The sequence is as follows:

           Enable automatic LPON1 following of LON.
           Wait for LON to become active.
           Set LPON1 active (automatically).
           Set VOFF and VSIG according to the scan PDA data levels.
           Start scan data playback (includes both encoder and PDA data).
           Wait for LON to become inactive.
           Set LPON1 inactive (automatically).
           Wait for scan data playback to complete.
           Reset the DigiPot (Set VOFF = 2.50V and VSIG = 0.00V).
           Disable automatic LPON1 following of LON.

        :param data (PlaybackData): the combined encoder and signal data to be played back during the tuning sequence.
        """
        logger.info("BasicScanning.execute: data = '%s'", data.get_fname())
        # Set VOFF = 2.500V, VSIG = 0.000V, VOUT = -5.000V => VPDA = 2.500V
        asv.set_voff(2.500)
        asv.set_vsig(0.000)
        asv.set_vout(-5.000)
        # Enable automatic LPON1 tracking of LON
        asv.ni_daq.set_auto_lpon1(True)
        with ScanWaveformTask(data.get_rate(), data.get_signal_data(),  data.get_encoder_data()) as task:
            # Wait for the presence of the LON signal, LPON1 will track automatically
            logger.info('BasicScanning.execute: wait for LON to become active')
            asv.ni_daq.din.wait_for_lsr_lon(True)
            # Payback the signal data first setting the DigiPot based on the signal file contents
            logger.info('BasicScanning.execute: playback the signal data')
            asv.digipot.write_voff_w(data.get_voff_w())
            asv.digipot.write_vsig_w(data.get_vsig_w())
            task.start()
            # Wait for LSR_LON to
            logger.info('BasicScanning.execute: wait for LON to become inactive')
            asv.ni_daq.din.wait_for_lsr_lon(False)
            logger.info('BasicScanning.execute: waiting for scan waveform task to complete')
            task.wait_until_done()
        # Set VOFF = 2.500V, VSIG = 0.000V, VOUT = 0.000V => VPDA = 2.500V
        asv.set_voff(2.500)
        asv.set_vsig(0.000)
        asv.set_vout(0.000)
        # Disable automatic LPON1 tracking of LON
        asv.ni_daq.set_auto_lpon1(False)
