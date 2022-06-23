#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Tuning Sequence Implementation."""

import logging

from framework.asv_control import AsvControl
from framework.module.nidaq import EncoderWaveformTask
from framework.util.config import Config
from framework.util.data import PlaybackData


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'BasicTuning'
]


class BasicTuning():
    """Class implementing basic startup and tuning sequence."""

    def __init__(self):
        logger.debug('BasicTuning.__init__')

    def execute(self, asv: AsvControl, data: PlaybackData) -> None:
        """Performs the basic PM1 Pachymeter startup and tuning sequence.

           The sequence is as follows:

           Disable automatic LPON1 following of LON.
           Wait for M+/M- signal present.
           Start encoder file playback.
           Repeat 15 times:

           Wait for LON to go high.
           Set analogue signal to 3.45V and set LPON.
           Wait for LON to go low.
           Clear LPON.

           Disable automatic LPON1 following of LON.

        :param data (PlaybackData): the encoder playback data to be replayed during the tuning sequence.
        """
        logger.info("BasicTuning.execute: data = '%s'", data.get_fname())
        # Set VOFF = 2.500V, VSIG = 0.000V, VOUT = 0.000V => VPDA = 2.500V
        asv.set_voff(2.500)
        asv.set_vsig(0.000)
        asv.set_vout(0.000)
        # Initialise LON on/off count
        count = 0
        # Disable automatic LPON1 tracking of LON
        asv.ni_daq.set_auto_lpon1(False)
        # Instantiate an encoder waveform task to stream the encoder data to the DUT
        with EncoderWaveformTask(data.get_rate(), data.get_encoder_data()) as task:
            # Wait for the presence of the M+/M- signal
            logger.info('BasicTuning.execute: wait for M+/M- to become active')
            asv.ni_daq.din.wait_for_enc_m(True)
            # Playback the startup encoder file
            logger.info('BasicTuning.execute: playback the startup encoder file')
            task.start()
            while True:
                logger.info('BasicTuning.execute: wait for LON to become active')
                asv.ni_daq.din.wait_for_lsr_lon(True)
                # TODO set PDA voltage to 3.450V
                # Set VOFF = 2.500V, VSIG = 2.900V, VOUT = 0.000V => VPDA = 3.450V
                #asv.set_vsig(2.900)
                # Reflect LON in LPON1
                asv.ni_daq.dout.set_lsr_lpon1(True)
                logger.info('BasicTuning.execute: wait for LON to become inactive')
                asv.ni_daq.din.wait_for_lsr_lon(False)
                # TODO set VOUT back to 2.500V
                # Set VOFF = 2.500V, VSIG = 0.000V, VOUT = 0.000V => VPDA = 2.500V
                #asv.set_vsig(0.000)
                # Reflect LON in LPON1
                asv.ni_daq.dout.set_lsr_lpon1(False)
                count += 1
                if count == 15:
                    logger.info('BasicTuning.execute: count == 15')
                    break
            # Wait for encoder playback to finish
            task.wait_until_done()
        # Disable automatic LPON1 tracking of LON
        asv.ni_daq.set_auto_lpon1(False)
