#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig FT232H SPI Device Support."""

import logging
import sys

from pyftdi.spi import SpiController

from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'SpiMaster'
]


class SpiMaster:
    """FT232H SPI Master Device Support.

    Single Channel Hi-Speed USB to Multipurpose UART/FIFO IC configured as SPI master.
    D0/SCK
    D1/MOSI
    D2/MISO
    """

    # Local data
    _cs_mask = None
    _cs_pin = None
    _handle = None
    _gpio = None
    _spi = None

    def __init__(self, url: str, cs_pin: int, freq: float):
        logger.debug("SpiMaster.__init__: url = '%s', freq = %.1f", url, freq)
        self._cs_pin = cs_pin
        self._cs_mask = 1 << cs_pin
        # PyFtdi directly supports CS on DBUS D3 - D7, CBUS C0 - C7 require GPIO
        if cs_pin <= 4:
            # Instantiate an SPI controller
            self._handle = SpiController(cs_count = cs_pin + 1)
            # Configure the FT232H interface as an SPI master
            self._handle.configure(url)
            # Create a port to an SPI slave with PyFtdi managed CS
            self._spi = self._handle.get_port(cs_pin, freq, 0)
        else:
            # Instantiate an SPI controller
            self._handle = SpiController()
            # Configure the FT232H interface as an SPI master
            self._handle.configure(url)
            # Create a port to an SPI slave with PyFtdi managed CS
            self._spi = self._handle.get_port(0, freq, 0)
            # Slave select is on CBUS, so we need to configure GPIO pin as write initially high
            self._gpio = self._handle.get_gpio()
            self._gpio.set_direction(self._cs_mask, self._cs_mask)
            self._gpio.write(self._cs_mask)
        # Confirm configuration or raise a fatal error
        if not self._handle.configured:
            logger.fatal("Failed to configure SPI controller")
            sys.exit(1)

    def exchange(self, out: bytes) -> bytes:
        """Perform an exchange with the SPI slave."""
        logger.debug("SpiMaster.exchange: out = %s", out.hex(' '))
        if self._cs_pin > 4:
            # Assert the slave select
            self._gpio.write(0)
        # Perform the SPI exchange
        data_in = self._spi.exchange(out, 0, duplex = True)
        if self._cs_pin > 4:
            # Deassert the slave select
            self._gpio.write(self._cs_mask)
        logger.debug("SpiMaster.exchange: in  = %s", data_in.hex(' '))
        return data_in
