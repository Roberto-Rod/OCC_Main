#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Control."""


import logging
from threading import Lock
import sys

from framework.constants import ASV_DIGIPOT_STEPS_MAX, ASV_DIGIPOT_VOFF_MAX, ASV_DIGIPOT_VSIG_MAX
from framework.module.digipot import DigiPot
from framework.module.nidaq import NiDaq
from framework.module.serial_debug import SerialDebug
from framework.module.touch import TouchPanel
from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'AsvControl'
]


class AsvControl:
    """Automated Software Verification Rig Control.

    This class implements the singleton pattern i.e. there is only one actual underlying instance of AsvControl.
    Access to the instance should be via the with statement to prevent concurrent access in the main control flow.
    This class is intended to be the top level class used by python scripts that implement automated software verification
    activities.
    """

    # Private data
    _instance = None
    _mutex = None

    # Public data
    digipot = None
    ni_daq = None
    serial_debug = None
    touch_panel = None

    def __new__(cls):
        logger.debug('AsvControl.__new__')
        if cls._instance is None:
            logger.info('AsvControl.__new__: creating the singleton instance')
            cls._instance = super(AsvControl, cls).__new__(cls)
            cls._mutex = Lock()
            cls.digipot = DigiPot()
            cls.ni_daq = NiDaq()
            cls.serial_debug = SerialDebug()
            cls.touch_panel = TouchPanel()
        return cls._instance

    def __enter__(self):
        logger.debug('AsvControl.__enter__')
        self._mutex.acquire()
        self.digipot.__enter__()
        self.ni_daq.__enter__()
        self.serial_debug.__enter__()
        self.touch_panel.__enter__()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.debug('AsvControl.__exit__')
        self.touch_panel.__exit__(exc_type, exc_val, exc_tb)
        self.serial_debug.__exit__(exc_type, exc_val, exc_tb)
        self.ni_daq.__exit__(exc_type, exc_val, exc_tb)
        self.digipot.__exit__(exc_type, exc_val, exc_tb)
        self._mutex.release()

    def reset(self) -> None:
        """Reset the AsvControl object to its default state."""
        logger.info('AsvControl.reset()')
        self.digipot.reset()
        self.ni_daq.reset()
        self.serial_debug.reset()
        self.touch_panel.reset()

    def set_voff(self, voff: float) -> None:
        """Set the offset voltage to voff.

           Sets the offset op-amp buffer output voltage to voff.
           The minimum voltage for voff is 0.000V and corresponds to a digipot setting of zero steps.
           The maximum voltage for voff is ASV_DIGIPOT_VOFF_MAX and corresponds to a digipot setting of ASV_DIGIPOT_STEPS_MAX.

           :param voff (float): the desired constant offset voltage.
        """
        logger.debug("AsvControl.set_voff: voff = %.3f", voff)
        if voff < 0. or voff > ASV_DIGIPOT_VOFF_MAX:
            logger.fatal("AsvControl.set_voff: invalid voff = %.3f", voff)
            sys.exit(1)
        self.digipot.write_voff_w(round((voff / ASV_DIGIPOT_VOFF_MAX) * float(ASV_DIGIPOT_STEPS_MAX)))

    def set_vsig(self, vsig: float) -> None:
        """Set the peak signal voltage to vsig.

           Sets the peak signal op-amp buffer output voltage to vsig.
           The minimum voltage for vsig is 0.000V and corresponds to a digipot setting of zero steps.
           The maximum voltage for vsig is ASV_DIGIPOT_VSIG_MAX and corresponds to a digipot setting of ASV_DIGIPOT_STEPS_MAX.

           :param vsig (float): the desired peak signal voltage.
        """
        logger.debug("AsvControl.set_vsig: vsig = %.3f", vsig)
        if vsig < 0. or vsig > ASV_DIGIPOT_VSIG_MAX:
            logger.fatal("AsvControl.set_vsig: invalid vsig = %.3f", vsig)
            sys.exit(1)
        self.digipot.write_vsig_w(round((vsig / ASV_DIGIPOT_VSIG_MAX) * float(ASV_DIGIPOT_STEPS_MAX)))

    def set_vout(self, vout: float) -> None:
        """Set the NI DAC output voltage to vout.

           Sets the NI DAC output voltage to vout.
           The minimum voltage for vout is -5.000V.
           The maximum voltage for vout is 5.000V.

           :param vout (float): the desired peak signal voltage.
        """
        logger.debug("AsvControl.set_vout: vout = %.3f", vout)
        if vout < -5. or vout > 5.:
            logger.fatal("AsvControl.set_vout: invalid vout = %.3f", vout)
            sys.exit(1)
        self.ni_daq.aout.set_vout(vout)
