#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig MCP4261 Device Support."""

import logging
from time import sleep
from typing import Tuple

from framework.device.ft232h_spi import SpiMaster
from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'MCP4261'
]

class MCP4261:
    """MCP4261 Device Support.

       8-Bit Dual SPI Digital POT with Non-Volatile Memory.
       Connected via an FT232H and PyFtdi/PyUSB packages.
    """

    # SPI command set
    _CMD_WRITE = 0x00
    _CMD_INCR = 0x01
    _CMD_DECR = 0x02
    _CMD_READ = 0x03

    # SPI memory addresses
    _MEM_ADDR_WIPER_0 = 0x00
    _MEM_ADDR_WIPER_1 = 0x01
    _MEM_ADDR_NV_WIPER_0 = 0x02
    _MEM_ADDR_NV_WIPER_1 = 0x03
    _MEM_ADDR_TCON = 0x04
    _MEM_ADDR_STATUS = 0x05

    # Status bits
    STATUS_EEWA = 0x10
    STATUS_WL = 0x0C
    STATUS_SHDN = 0x02
    STATUS_WP = 0x01
    STATUS_MASK = 0x01F

    # Potentiometer steps/positions supported
    STEPS_DEFAULT = 0x80
    STEPS_MAX = 0x100

    # TCON bits
    TCON_EXPECTED = 0x0FF
    TCON_MASK = 0x0FF

    # Local data
    _spi = None

    def __init__(self, url: str, cs_pin: int, freq: float):
        logger.debug("MCP4261.__init__: url = '%s', freq = %.1f", url, freq)
        # Instantiate an SPI master instance on the FT232H
        self._spi = SpiMaster(url, cs_pin, freq)
        # Log initial STATUS and TCON register contents
        status = self.read_status()
        tcon = self.read_tcon()
        logger.debug("MCP4261.__init__: STATUS = 0x%03x, TCON = 0x%03x", status, tcon)
        # If STATUS is not as expected then flag an error
        if ((status & self.STATUS_MASK) & (self.STATUS_EEWA | self.STATUS_WL | self.STATUS_SHDN | self.STATUS_WP)) != 0x00:
            logger.error("MCP4261.__init__: STATUS = 0x%03x", status)
        # If TCON is not as expected then flag an error
        if (tcon & self.TCON_MASK) != self.TCON_EXPECTED:
            logger.error("MCP4261.__init__: TCON = 0x%03x", tcon)

    def read_w(self, wiper: int) -> int:
        """Read volatile wiper position

           :return: wiper position or STEPS_DEFAULT if CMDERR is detected or value is out of range
        """
        logger.debug("MCP4261.read_w: wiper = %d", wiper)
        # Check wiper number is valid
        if 0 <= wiper <= 1:
            (cmderr, steps) = self._cmd_read(self._MEM_ADDR_WIPER_0 + wiper)
            if cmderr or steps > self.STEPS_MAX:
                steps = self.STEPS_DEFAULT
            logger.debug("MCP4261.read_w: wiper = %d, steps = %d", wiper, steps)
            return steps
        logger.error("MCP4261.read_w: invalid wiper = %d", wiper)
        return self.STEPS_DEFAULT

    def write_w(self, wiper: int, steps: int) -> None:
        """Write volatile wiper position

           :param steps: requested wiper position
        """
        logger.debug("MCP4261.write_w: wiper = %d, steps = %d", wiper, steps)
        # Check wiper number is valid
        if 0 <= wiper <= 1:
            steps = min(max(steps, 0), self.STEPS_MAX)
            self._cmd_write(self._MEM_ADDR_WIPER_0 + wiper, steps)
        else:
            logger.error("MCP4261.write_w: invalid wiper = %d", wiper)

    def incr_w(self, wiper: int) -> None:
        """Increment volatile wiper position

        """
        logger.debug("MCP4261.incr_w: wiper = %d", wiper)
        # Check wiper number is valid
        if 0 <= wiper <= 1:
            self._cmd_incr(self._MEM_ADDR_WIPER_0 + wiper)
        else:
            logger.error("MCP4261.incr_w: invalid wiper = %d", wiper)

    def decr_w(self, wiper: int) -> None:
        """Decrement volatile wiper position

        """
        logger.debug("MCP4261.decr_w: wiper = %d", wiper)
        # Check wiper number is valid
        if 0 <= wiper <= 1:
            self._cmd_decr(self._MEM_ADDR_WIPER_0 + wiper)
        else:
            logger.error("MCP4261.decr_w: invalid wiper = %d", wiper)

    def read_nv_w(self, wiper: int) -> int:
        """Read non-volatile wiper position

           :return: wiper position or zero if CMDERR is detected or value is out of range
        """
        logger.debug("MCP4261.read_nv_w: wiper = %d", wiper)
        # Check wiper number is valid
        if 0 <= wiper <= 1:
            (cmderr, steps) = self._cmd_read(self._MEM_ADDR_NV_WIPER_0 + wiper)
            if cmderr or steps > self.STEPS_MAX:
                steps = self.STEPS_DEFAULT
            logger.debug("MCP4261.read_nv_w: wiper = %d, steps = %d", wiper, steps)
            return steps
        logger.error("MCP4261.read_nv_w: invalid wiper = %d", wiper)
        return self.STEPS_DEFAULT

    def write_nv_w(self, wiper: int,  steps: int) -> None:
        """Write non-volatile wiper position

           :param steps: requested non-volatile wiper position
        """
        logger.debug("MCP4261.write_nv_w: wiper = %d, steps = %d", wiper, steps)
        # Check wiper number is valid
        if 0 <= wiper <= 1:
            # Make sure steps is valid
            steps = min(max(steps, 0), self.STEPS_MAX)
            # Read back the current value and write to the non-volatile wiper register if required
            if steps != self.read_nv_w(wiper):
                logger.warning("MCP4261.write_nv_w: wiper = %d, steps = %d", wiper, steps)
                self._cmd_write(self._MEM_ADDR_NV_WIPER_0 + wiper, steps)
                status = self.read_status()
                # Loop until EE write has completed
                while ((status & self.STATUS_MASK) & self.STATUS_EEWA) != 0x00:
                    logger.debug('MCP4261.write_nv_w: busy')
                    sleep(0.010)
                    status = self.read_status()
        else:
            logger.error("MCP4261.write_nv_w: invalid wiper = %d", wiper)

    def read_status(self) -> int:
        """Read the current STATUS register contents."""
        logger.debug('MCP4261.read_status')
        (_cmderr, status) = self._cmd_read(self._MEM_ADDR_STATUS)
        logger.debug("MCP4261.read_status: STATUS = 0x%03x", status)
        return status

    def read_tcon(self) -> int:
        """Read the current TCON register contents."""
        logger.debug('MCP4261.read_tcon')
        (_cmderr, tcon) = self._cmd_read(self._MEM_ADDR_TCON)
        logger.debug("MCP4261.read_tcon: TCON = 0x%03x", tcon)
        return tcon

    def _cmd_write(self, mem_addr: int, data: int ) -> bool:
        logger.debug("MCP4261._cmd_write: mem_addr = 0x%02x, data = 0x%03x", mem_addr, data)
        # Build the 16 bit write command
        data_out = bytes([
            ((mem_addr & 0x0f) << 4) + (self._CMD_WRITE << 2) + ((data & 0x100) >> 8),
            (data & 0x0ff)
        ])
        # Perform the SPI exchange
        data_in = self._spi.exchange(data_out)
        # Separate and return the CMDERR bit valid(high) or invalid(low)
        cmderr = (data_in[0] & 0x02) == 0
        # Log result
        if not cmderr:
            logger.debug("MCP4261._cmd_write: cmderr = %r, data_out = 0x%02x%02x, data_in = 0x%02x%02x",
                         cmderr, data_out[0], data_out[1], data_in[0], data_in[1])
        else:
            logger.error("MCP4261._cmd_write: cmderr = %r, data_out = 0x%02x%02x, data_in = 0x%02x%02x",
                         cmderr, data_out[0], data_out[1], data_in[0], data_in[1])
        return cmderr

    def _cmd_read(self, mem_addr: int) -> Tuple[bool, int]:
        logger.debug("MCP4261._cmd_read: mem_addr = 0x%02x", mem_addr)
        # Build the 16 bit read command
        data_out = bytes([
            ((mem_addr & 0x0f) << 4) + (self._CMD_READ << 2),
            0x00
        ])
        # Perform the SPI exchange
        data_in = self._spi.exchange(data_out)
        # Separate and return the CMDERR bit valid(high) or invalid(low) and the data bits
        cmderr = (data_in[0] & 0x02) == 0
        data = ((data_in[0] & 0x01) << 8) + data_in[1]
        # Log result
        if not cmderr:
            logger.debug("MCP4261._cmd_read: cmderr = %r, data_out = 0x%02x%02x, data_in = 0x%02x%02x",
                         cmderr, data_out[0], data_out[1], data_in[0], data_in[1])
        else:
            logger.error("MCP4261._cmd_read: cmderr = %r, data_out = 0x%02x%02x, data_in = 0x%02x%02x",
                         cmderr, data_out[0], data_out[1], data_in[0], data_in[1])
        return (cmderr, data)

    def _cmd_incr(self, mem_addr: int) -> bool:
        logger.debug("MCP4261._cmd_incr mem_addr = 0x%02x", mem_addr)
        # Build the 8 bit increment command
        data_out = bytes([ ((mem_addr & 0x0f) << 4) + (self._CMD_INCR << 2) ])
        # Perform the SPI exchange
        data_in = self._spi.exchange(data_out)
        # Separate and return the CMDERR validity (active high)
        cmderr = (data_in[0] & 0x02) == 0
        # Log result
        if not cmderr:
            logger.debug("MCP4261._cmd_incr: cmderr = %r, data_out = 0x%02x", cmderr, data_out[0])
        else:
            logger.error("MCP4261._cmd_incr: cmderr = %r, data_out = 0x%02x", cmderr, data_out[0])
        return cmderr

    def _cmd_decr(self, mem_addr: int) -> bool:
        logger.debug("MCP4261._cmd_decr mem_addr = 0x%02x", mem_addr)
        # Build the 8 bit decrement command
        data_out = bytes([ ((mem_addr & 0x0f) << 4) + (self._CMD_DECR << 2) ])
        # Perform the SPI exchange
        data_in = self._spi.exchange(data_out)
        # Separate and return the CMDERR validity (active high)
        cmderr = (data_in[0] & 0x02) == 0
        # Log result
        if not cmderr:
            logger.debug("MCP4261._cmd_decr: cmderr = %r, data_out = 0x%02x", cmderr, data_out[0])
        else:
            logger.error("MCP4261._cmd_decr: cmderr = %r, data_out = 0x%02x", cmderr, data_out[0])
        return cmderr
