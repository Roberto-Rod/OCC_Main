#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig FT232H I2C Device Support."""

import logging
import sys

from pyftdi.i2c import I2cController

from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'I2cMaster'
]


class I2cMaster:
    """FT232H I2C Master Device Support.

    Single Channel Hi-Speed USB to Multipurpose UART/FIFO IC configured as I2C master.
    D0/SCL
    D1/SDA (Out)
    D2/SDA (in)
    """

    # Local data
    _handle = None
    _gpio = None
    _i2c = None

    def __init__(self, url: str, addr: int):
        logger.debug("I2cMaster.__init__: url = '%s', addr = %d", url, addr)
        # Instantiate an I2C controller
        self._handle = I2cController()
        self._handle.set_retry_count(1)
        # Configure the FT232H interface as an I2C master
        self._handle.configure(url)
        # Create a port to an I2C slave
        self._i2c = self._handle.get_port(addr)
        # Confirm configuration or raise a fatal error
        if not self._handle.configured:
            logger.fatal("Failed to configure I2C controller")
            sys.exit(1)

    def exchange(self, out: bytes, readlen: int = 0) -> bytes:
        """Perform an exchange with the I2C slave."""
        logger.debug("I2cMaster.exchange: out = %s", out.hex(' '))
        #self._i2c.write(out)
        # Perform the I2C exchange
        data_in = self._i2c.exchange(out, readlen)
        logger.debug("I2cMaster.exchange: in  = %s", data_in.hex(' '))
        return data_in
