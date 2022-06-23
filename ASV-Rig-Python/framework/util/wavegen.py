#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Waveform Utility."""

import logging

import numpy as np

from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'data_sine'
]


def data_sine(freq: float, rate: float, duration: float, amplitude: float) -> np.ndarray:
    """Generate an ndarray of samples representing a sine wave.

       :param freq (float): frequency of the sine wave (Hz)
       :param rate (float): sample rate (Hz)
       :param duration (float): duration of the sample (s)
       :param amplitude (float): amplitude of the sine wave (V)
       :return: returns an ndarray of float samples
    """
    logger.debug("wave_sine: freq = %.1f, rate = %.1f duration = %.3f, amplitude = %.3f", freq, rate, duration, amplitude)
    points = np.arange(int(rate * duration))
    data_out = np.sin(2.0 * np.pi * points / (rate / freq)) * amplitude
    return data_out
