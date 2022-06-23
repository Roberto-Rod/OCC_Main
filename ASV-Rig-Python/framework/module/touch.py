#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Touch Module Implementation."""

import binascii
import logging
from threading import Lock
import sys
import time
from datetime import datetime, timedelta
from typing import Literal


#pylint: disable=wildcard-import
#pylint: disable=unused-wildcard-import
from framework.device.aardvark_py import *
from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'TouchPanel'
]


class TouchPanel:
    """Support Touch Panel Control.

       Touch Panel Control/Automation/Simulation is provided via the Total Phase Aardvark I2C/GPIO
       host adapter.
    """

    GPIO5_AA_INT = AA_GPIO_MISO
    GPIO7_AA_TP_I2C_EN = AA_GPIO_SCK
    GPIO8_SPARE = AA_GPIO_MOSI
    GPIO9_nTP_RESET = AA_GPIO_SS

    BUFFER_SIZE = 65535
    INTERVAL_TIMEOUT = 5
    MAXIMUM_TOUCH_RETRIES = 2

    _gpio_value = 0
    _handle = None
    _instance = None
    _mutex = None
    _port = None
    _touch_loc = None
    _touch_lift = None
    _touch_lift_start = None
    _i2c_interrupt_timeout = None
    _touch_request_period = None

    def __new__(cls):
        logger.debug('TouchPanel.__new__')
        if cls._instance is None:
            logger.info('TouchPanel.__new__: creating the singleton instance')
            cls._instance = super(TouchPanel, cls).__new__(cls)
            cls._config = Config().get_touch_config()
            cls._mutex = Lock()
            cls._open()
        return cls._instance

    def __enter__(self):
        logger.debug('TouchPanel.__enter__')
        self._mutex.acquire()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.debug('TouchPanel.__exit__')
        self._mutex.release()
        return self

    def is_tp_reset(self) -> bool:
        """Checks whether TP_RESET# is active (low).

           :return: returns True if TP_RESET# is active (low), False if TP_RESET# is inactive (high)
        """
        if not aa_gpio_get(self._handle) & self.GPIO9_nTP_RESET:
            logger.debug('TouchPanel.is_tp_reset: TP_RESET# is active (low)')
            return True
        logger.debug('TouchPanel.is_tp_reset: TP_RESET# is inactive (high)')
        return False

    def set_aa_int(self, active: bool) -> None:
        """Sets AA_INT active (high) or inactive (low).

           :param active: True or False.
        """
        if active:
            logger.debug('TouchPanel.set_aa_int: setting AA_INT active (high)')
            self._gpio_value |= self.GPIO5_AA_INT
        else:
            logger.debug('TouchPanel.set_aa_int: setting AA_INT inactive (low)')
            self._gpio_value &= ~self.GPIO5_AA_INT
        ret_code = aa_gpio_set(self._handle, self._gpio_value)
        if ret_code != AA_OK:
            status = aa_status_string(ret_code)
            logger.error("%s (%d)", status, ret_code)

    def select_aa_i2c(self) -> None:
        """Sets AA_TP_I2C_EN inactive (low).

           When AA_TP_I2C_EN is inactive DUT I2C is routed to the Aardvark.
        """
        logger.debug('TouchPanel.select_aa_i2c: setting AA_TP_I2C_EN inactive (low)')
        self._gpio_value &= ~self.GPIO7_AA_TP_I2C_EN
        ret_code = aa_gpio_set(self._handle, self._gpio_value)
        if ret_code != AA_OK:
            status = aa_status_string(ret_code)
            logger.error("%s (%d)", status, ret_code)

    def select_tp_i2c(self) -> None:
        """Sets AA_TP_I2C_EN active (high).

           When AA_TP_I2C_EN is active DUT I2C is routed to the Touch Panel.
        """
        logger.debug('TouchPanel.select_tp_i2c: setting AA_TP_I2C_EN active (high)')
        self._gpio_value |= self.GPIO7_AA_TP_I2C_EN
        ret_code = aa_gpio_set(self._handle, self._gpio_value)
        if ret_code != AA_OK:
            status = aa_status_string(ret_code)
            logger.error("%s (%d)", status, ret_code)

    def touch_request_is_valid(self, touch_type: str) -> bool:
        """ Check if the touch requested is valid and exists in config.yml
            Parameters : a string specifying the type of touch
            Return : True if the touch exists in config.yml file, False otherwise
        """

        logger.debug("TouchPanel.touch: requested touch type : '%s'", touch_type)
         # Check is a valid key
        if touch_type in self._config.touch_responses:
            # print("Touch type found in config.yml")
            logger.debug("TouchPanel.touch: '%s' - (%s) touch type found in config.yml: ",
                        touch_type, binascii.hexlify(self._touch_loc).decode('utf-8'))
            return True
        else:
            logger.debug("TouchPanel.touch: touch response cannot be found : %s (%d)",
                        touch_type, array('B', self._config.touch_responses[self._touch_loc]))
            return False

    def transmit_response(self, action_type: int) -> Literal:
        """
            Transmits touch request
        """

        if action_type == 1:
            self._i2c_interrupt_timeout = self._config.aa_timeout_ms
            self._touch_request_period = 0.006       # units of seconds
        elif action_type == 0:
            self._i2c_interrupt_timeout = self._config.int_timeout_ms
            self._touch_request_period = 0.010       # units of seconds
        else:
            logger.error("TouchPanel.transmit_response: invalid timeout value")
            sys.exit(1)


        self.set_aa_int(True)
        touch_request_start_time = datetime.now()
        ret_code = aa_async_poll(self._handle, self._i2c_interrupt_timeout)
        # print("TouchPanel.transmit_response: error code returned from line 159 call to aa_async_poll ", ret_code)

        if ret_code == AA_ASYNC_I2C_READ:
            (num_bytes, addr, data_in) = aa_i2c_slave_read(self._handle, self.BUFFER_SIZE)
            if num_bytes >= 0:
                if data_in == self._config.touch_request:
                    logger.debug("TouchPanel.transmit_response: request received addr = 0x%02x", addr)
                    ret_code = aa_async_poll(self._handle, self._i2c_interrupt_timeout)
                    # print("TouchPanel.transmit_response: error code returned from line 167 call to aa_async_poll ", ret_code)
                    if ret_code == AA_ASYNC_I2C_WRITE:
                        num_bytes = aa_i2c_slave_write_stats(self._handle)
                        if num_bytes >= 0:
                            if num_bytes == len(self._touch_loc):
                                logger.debug('TouchPanel.transmit_response: response transmitted')
                                # Touch has been transmitted
                                # print("TouchPanel.touch: error code after touch transmitted ", ret_code)
                                # Check if the transmission occurred in less than the minimum pulse width
                                while datetime.now() < (touch_request_start_time + timedelta(seconds=self._touch_request_period)):
                                    time.sleep(0.001)
                                self.set_aa_int(False)
                                return ret_code
                            else:
                                logger.error("TouchPanel.transmit_response: response length mismatch (%d, %d)",
                                            num_bytes, len(self._touch_loc))
                        else:
                            status = aa_status_string(num_bytes)
                            logger.error("TouchPanel.transmit_response: %s (%d)", status, num_bytes)
                    return ret_code
                else:
                    logger.error("TouchPanel.transmit_response: unexpected request '%s'",
                                binascii.hexlify(data_in).decode('utf-8'))
                    # return ret_code
            else:
                status = aa_status_string(num_bytes)
                logger.error("TouchPanel.transmit_response: %s (%d)", status, num_bytes)
                # return ret_code
        self.set_aa_int(False)
        return ret_code

    def transmit_touch_lifted(self, touch_type_lift: str, touch_type_lift_start: str) -> None:
        """
            Transmit touch lifted message
        """

        touch_lift_start_time = datetime.now()
        start_touch_lifted_period = 0.020       # units of seconds

        self._touch_lift = array('B', self._config.touch_responses[touch_type_lift])
        logger.debug("TouchPanel.transmit_touch_lifted: request = '%s', response = '%s'",
                         binascii.hexlify(bytearray(self._config.touch_request)).decode('utf-8'),
                         binascii.hexlify(self._touch_lift).decode('utf-8'))

        while datetime.now() < (touch_lift_start_time + timedelta(seconds=start_touch_lifted_period)):
            time.sleep(0.001)

        # Check is a valid key
        if self.touch_request_is_valid(touch_type_lift):
            ret_code = aa_i2c_slave_set_response(self._handle, self._touch_lift)
            if ret_code == len(self._touch_lift):
                ret_code = aa_i2c_slave_enable(self._handle, self._config.aa_addr, 0, 0)
                if ret_code == AA_OK:

                    # try to transmit touch lift response with the same timeout as a touch press
                    ret_code = self.transmit_response(1)
                    # print("transmit_touch_lifted: Error code", ret_code)

                    if ret_code == AA_ASYNC_I2C_WRITE:
                        # print("Touch lift transmitted OK")
                        ret_code = aa_i2c_slave_disable(self._handle)

                    if ret_code != AA_OK:
                        status = aa_status_string(ret_code)
                        logger.error("TouchPanel.transmit_touch_lifted: %s (%d)", status, ret_code)
                else:
                    status = aa_status_string(ret_code)
                    logger.error("TouchPanel.transmit_touch_lifted: %s (%d)", status, ret_code)
            elif ret_code >= 0:
                logger.error("TouchPanel.transmit_touch_lifted: response truncated (%d)", ret_code)
            else:
                status = aa_status_string(ret_code)
                logger.error("TouchPanel.transmit_touch_lifted: %s (%d)", status, ret_code)
        else:
            logger.error("TouchPanel.transmit_touch_lifted: touch response cannot be found : %s (%d)", touch_type_lift, self._touch_lift)
            sys.exit(1)

        # begin the final 3 pulses to end the touch lift process
        touch_lift_finish_start_time = datetime.now()
        end_touch_lifted_period = 0.040

        self._touch_lift_start = array('B', self._config.touch_responses[touch_type_lift_start])
        logger.debug("TouchPanel.transmit_touch_lifted: request = '%s', response = '%s'",
                         binascii.hexlify(bytearray(self._config.touch_request)).decode('utf-8'),
                         binascii.hexlify(self._touch_lift_start).decode('utf-8'))

        while datetime.now() < (touch_lift_finish_start_time + timedelta(seconds=end_touch_lifted_period)):
            time.sleep(0.001)

        # Check is a valid key
        if self.touch_request_is_valid(touch_type_lift_start):
            ret_code = aa_i2c_slave_set_response(self._handle, self._touch_lift_start)
            if ret_code == len(self._touch_lift_start):
                ret_code = aa_i2c_slave_enable(self._handle, self._config.aa_addr, 0, 0)
                if ret_code == AA_OK:

                    # try to transmit touch lift end response 3 times
                    pulses = 1
                    while pulses <= 3:
                        ret_code = self.transmit_response(0)
                        pulses += 1
                        # print("Error code", ret_code)

                    if ret_code == AA_ASYNC_I2C_WRITE:
                        # print("Touch lift end transmitted OK")
                        ret_code = aa_i2c_slave_disable(self._handle)

                    if ret_code != AA_OK:
                        status = aa_status_string(ret_code)
                        logger.error("TouchPanel.transmit_touch_lifted: %s (%d)", status, ret_code)
                else:
                    status = aa_status_string(ret_code)
                    logger.error("TouchPanel.transmit_touch_lifted: %s (%d)", status, ret_code)
            elif ret_code >= 0:
                logger.error("TouchPanel.transmit_touch_lifted: response truncated (%d)", ret_code)
            else:
                status = aa_status_string(ret_code)
                logger.error("TouchPanel.transmit_touch_lifted: %s (%d)", status, ret_code)
        else:
            logger.error("TouchPanel.transmit_touch_lifted: touch response cannot be found : %s (%d)", touch_type_lift, self._touch_lift)
            sys.exit(1)

    def touch(self, touch_type: str) -> None:
        """Perform a simulated touch sequence."""

        self._touch_loc = array('B', self._config.touch_responses[touch_type])

        # Check is a valid key
        if self.touch_request_is_valid(touch_type):

            logger.debug("TouchPanel.touch: request = '%s', response = '%s'",
                         binascii.hexlify(bytearray(self._config.touch_request)).decode('utf-8'),
                         binascii.hexlify(self._touch_loc).decode('utf-8'))
            ret_code = aa_i2c_slave_set_response(self._handle, self._touch_loc)
            if ret_code == len(self._touch_loc):
                ret_code = aa_i2c_slave_enable(self._handle, self._config.aa_addr, 0, 0)
                if ret_code == AA_OK:

                    # try to transmit touch
                    ret_code = self.transmit_response(1)
                    # print("Error code", ret_code)

                    if ret_code == AA_ASYNC_I2C_WRITE:
                        # print("Touch transmitted OK")
                        ret_code = aa_i2c_slave_disable(self._handle)
                    else:
                        # If the touch was not acknowledged
                        # If no data was sent, try again
                        touch_retry_count = 1

                        while (ret_code == AA_ASYNC_NO_DATA or ret_code == 3) and touch_retry_count <= self.MAXIMUM_TOUCH_RETRIES:

                            time.sleep(0.001)
                            touch_retry_count += 1
                            # try to transmit touch
                            ret_code = self.transmit_response(1)
                            # print("Error code", ret_code)

                    ret_code = aa_i2c_slave_disable(self._handle)

                    if ret_code != AA_OK:
                        status = aa_status_string(ret_code)
                        logger.error("TouchPanel.touch: %s (%d)", status, ret_code)
                else:
                    status = aa_status_string(ret_code)
                    logger.error("TouchPanel.touch: %s (%d)", status, ret_code)
            elif ret_code >= 0:
                logger.error("TouchPanel.touch: response truncated (%d)", ret_code)
            else:
                status = aa_status_string(ret_code)
                logger.error("TouchPanel.touch: %s (%d)", status, ret_code)

        else:
            logger.error("TouchPanel.touch: touch response cannot be found : %s (%d)", touch_type, self._touch_loc)
            sys.exit(1)



    def reset(self):
        """Reset the TouchPanel object to its default state."""
        logger.debug('TouchPanel.reset()')
        aa_close(self._handle)
        self._handle = None
        self._open()

    @classmethod
    def _open(cls) -> None:
        # Open the aardvark
        (cls._handle, aaext) = aa_open_ext(cls._config.aa_port)
        if cls._handle > 0:
            logger.info("TouchPanel._open: opened Aardvark on port %d, (0x%02x)", cls._config.aa_port, aaext.features)
            # Ensure the aardvark is in I2C/GPIO mode
            aa_configure(cls._handle, AA_CONFIG_GPIO_I2C)
            # Disable the bus pull-up resistors (2.2K resistors)
            # aa_i2c_pullup(cls._handle, AA_I2C_PULLUP_NONE)    # commented out by RR, replaced with line below
            aa_i2c_pullup(cls._handle, AA_I2C_PULLUP_BOTH)
            # Configure GPIO5 as an output (AA_INT) initially low
            # Configure GPIO7 as an output (AA_TP_I2C_EN) initially high
            # Configure GPIO8 as an input (SPARE)
            # Configure GPIO9 as an input (TP_RESET#)
            aa_gpio_pullup(cls._handle, cls.GPIO8_SPARE | cls.GPIO9_nTP_RESET)
            cls._gpio_value = cls.GPIO7_AA_TP_I2C_EN
            aa_gpio_set(cls._handle, cls._gpio_value)
            aa_gpio_direction(cls._handle, cls.GPIO5_AA_INT | cls.GPIO7_AA_TP_I2C_EN)
        else:
            logger.fatal("TouchPanel._open: unable to open Aardvark on port %d (%d)", cls._config.aa_port, cls._handle)
            sys.exit(1)
