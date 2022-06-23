#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Constants."""

import logging

from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'ASV_DIGIPOT_STEPS_MAX',
    'ASV_DIGIPOT_VOFF_MAX',
    'ASV_DIGIPOT_VSIG_MAX',
    'ASV_NI_DAQ_AO_0_VMAX',
    'ASV_NI_DAQ_AO_0_VMIN',
    'ASV_PDA_VMAX'
]


#: Maximum DigiPot steps
ASV_DIGIPOT_STEPS_MAX = 256
#: Maximum DigiPot offset output voltage (V)
ASV_DIGIPOT_VOFF_MAX = 2.500
#: Maximum DigiPot signal output voltage (V)
ASV_DIGIPOT_VSIG_MAX = 3.333
#: NI DAQ maximum analog output voltage (V)
ASV_NI_DAQ_AO_0_VMAX = 5.000
#: NI DAQ minimum analog output voltage (V)
ASV_NI_DAQ_AO_0_VMIN = -5.000
#: Maximum output voltage at the PDA resistor (V)
ASV_PDA_VMAX = 5.000
