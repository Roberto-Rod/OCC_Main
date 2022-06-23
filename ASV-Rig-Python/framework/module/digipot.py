#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig DigiPot Module Implementation."""

import logging
from threading import Lock
import sys

from framework.device.mcp4261 import MCP4261
from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'DigiPot'
]


class DigiPot():
    """DigiPot Control.

       This class implements the singleton pattern i.e. there is only one actual underlying instance of DigiPot. Access to the
       instance should be via the with statement to prevent concurrent access in the main control flow.

       The DigiPot will always initialise the underlying device so that the VOFF wiper is set to the maximum position i.e. VOFF
       will be set to 2.500V and the VSIG wiper is set to the minimum position i.e. VSIG = 0.000V irrespective of the NI DAC VOUT
       value.

       This means that the default output VOUT to the laser board is 2.500V.
    """

    # Private constants
    _CS_PIN = 8
    _VOFF_WIPER = 1
    _VSIG_WIPER = 0

    # Private data
    _instance = None
    _mcp4261 = None
    _mutex = None

    def __new__(cls):
        if cls._instance is None:
            logger.info('DigiPot.__new__: creating the singleton instance')
            cls._instance = super(DigiPot, cls).__new__(cls)
            cls._config = Config().get_digipot_config()
            cls._mcp4261 = MCP4261(cls._config.ftdi_url, cls._CS_PIN, cls._config.freq)
            status = cls._mcp4261.read_status()
            tcon = cls._mcp4261.read_tcon()
            # If STATUS is not as expected then raise a fatal error
            if ((status & cls._mcp4261.STATUS_MASK) &
                (cls._mcp4261.STATUS_EEWA | cls._mcp4261.STATUS_WL | cls._mcp4261.STATUS_SHDN | cls._mcp4261.STATUS_WP)) != 0x00:
                logger.fatal("DigiPot.__new__: DigiPot was not initialised successfully.")
                sys.exit(1)
            # If TCON is not as expected then raise a fatal error
            if (tcon & cls._mcp4261.TCON_MASK) != cls._mcp4261.TCON_EXPECTED:
                logger.fatal("DigiPot.__new__: DigiPot was not initialised successfully.")
                sys.exit(1)
            cls._mcp4261.write_w(cls._VSIG_WIPER, 0)
            cls._mcp4261.write_nv_w(cls._VSIG_WIPER, 0)
            cls._mcp4261.write_w(cls._VOFF_WIPER, cls._mcp4261.STEPS_MAX)
            cls._mcp4261.write_nv_w(cls._VOFF_WIPER, cls._mcp4261.STEPS_MAX)
            cls._mutex = Lock()
        return cls._instance

    def __enter__(self):
        logger.debug('DigiPot.__enter__')
        self._mutex.acquire()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.debug('DigiPot.__exit__')
        self._mutex.release()

    def read_vsig_w(self) -> int:
        """Read volatile VSIG wiper position

           :return: wiper position or STEPS_DEFAULT if CMDERR is detected or value is out of range
        """
        logger.debug('DigiPot.read_vsig_w')
        steps = self._mcp4261.read_w(self._VSIG_WIPER)
        return steps

    def write_vsig_w(self, steps: int) -> None:
        """Write volatile VSIG wiper position

           :param steps: wiper position
        """
        logger.debug("DigiPot.write_vsig_w: vsig_w = %d", steps)
        self._mcp4261.write_w(self._VSIG_WIPER, steps)

    def increment_vsig_w(self) -> None:
        """Increment volatile VSIG wiper position."""
        logger.debug('DigiPot.increment vsig_w')
        self._mcp4261.incr_w(self._VSIG_WIPER)

    def decrement_vsig_w(self) -> None:
        """Decrement volatile VSIG wiper position."""
        logger.debug('DigiPot.decrement vsig_w')
        self._mcp4261.decr_w(self._VSIG_WIPER)

    def read_voff_w(self) -> int:
        """Read volatile VOFF wiper position

           :return: wiper position or STEPS_DEFAULT if CMDERR is detected or value is out of range
        """
        logger.debug('DigiPot.read_voff_w')
        steps = self._mcp4261.read_w(self._VOFF_WIPER)
        return steps

    def write_voff_w(self, steps: int) -> None:
        """Write volatile VOFF wiper position

           :param steps: wiper position
        """
        logger.debug("DigiPot.write_voff_w: voff_w = %d", steps)
        self._mcp4261.write_w(self._VOFF_WIPER, steps)

    def increment_voff_w(self) -> None:
        """Increment volatile VOFF wiper position."""
        logger.debug('DigiPot.increment_voff_w')
        self._mcp4261.incr_w(self._VOFF_WIPER)

    def decrement_voff_w(self) -> None:
        """Decrement volatile VOFF wiper position."""
        logger.debug('DigiPot.decrement vsig_w')
        self._mcp4261.decr_w(self._VOFF_WIPER)

    def reset(self):
        """Reset the DigiPot object to its default state."""
        logger.debug('DigiPot.reset()')
        self._mcp4261.write_w(self._VSIG_WIPER, 0)
        self._mcp4261.write_nv_w(self._VSIG_WIPER, 0)
        self._mcp4261.write_w(self._VOFF_WIPER, self._mcp4261.STEPS_MAX)
        self._mcp4261.write_nv_w(self._VOFF_WIPER, self._mcp4261.STEPS_MAX)
