#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Automated Software Verification Rig Configuration File Support."""

from array import array
import os.path
import sys
from typing import Dict, NamedTuple
import yaml


__all__ = [
    'LoggingConfig',
    'DigiPotConfig',
    'NiDaqConfig',
    'SerialDebugConfig',
    'TouchConfig',
    'Config'
]


class LoggingConfig(NamedTuple):
    """NamedTuple representing the logging configuration."""
    level: int
    levels: Dict[str, int]
    path: str
    mode: str


class DigiPotConfig(NamedTuple):
    """NamedTuple representing the digipot configuration."""
    ftdi_url: str
    freq: float


class NiDaqConfig(NamedTuple):
    """NaedTuple representing the nidaq configuration."""
    device: str
    signal_channel: str
    encoder_lines: str
    di_lines: str
    do_lines: str
    timing_counter: str
    timing_source: str


class SerialDebugConfig(NamedTuple):
    """NamedTuple representing the serial debug configuration."""
    path: str
    ports: Dict[str, str]
    baudrate: int
    mode: str
    bufsize: int
    timeout: float


class TouchConfig(NamedTuple):
    """NamedTuple representing the serial debug configuration."""
    aa_port: int
    aa_addr: int
    aa_timeout_ms: int
    int_timeout_ms: int
    touch_request: array
    touch_responses: Dict[str, array]


class Config:
    """Configuration File Support.

       This class implements a YAML based configuration file.
    """

    _SEARCH_PATH = ['.\\config.yml', '.\\etc\\config.yml']

    # Local data
    _instance = None
    _yaml = {}

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(Config, cls).__new__(cls)
            try:
                # Search the configuration file search path for a configuration file and attempt to load it
                for path in cls._SEARCH_PATH:
                    if os.path.exists(path):
                        with open(path, 'r', encoding='utf-8',) as stream:
                            cls._yaml = yaml.safe_load(stream)
                        return cls._instance
                print('FATAL: Unable to locate the configuration file', file=sys.stderr)
                sys.exit(1)
            #pylint: disable=broad-except
            except Exception as exc:
                print('FATAL: Exception processing the configuration file: ', exc, file=sys.stderr)
                sys.exit(1)
        return cls._instance

    def get_logging_config(self) -> LoggingConfig:
        """Get the logging environment configuration."""
        try:
            item = self._yaml['environment']['logging']
            return LoggingConfig(item['level'], item['levels'], item['path'], item['mode'])
        except KeyError as exc:
            print('FATAL: Missing or invalid environment logging configuration: ', exc, file=sys.stderr)
            sys.exit(1)

    def get_digipot_config(self) -> DigiPotConfig:
        """Get the digipot module configuration."""
        try:
            item = self._yaml['modules']['digipot']
            return DigiPotConfig(item['ftdi_url'], item['freq'])
        except KeyError as exc:
            print('FATAL: Missing or invalid digipot module configuration: ', exc, file=sys.stderr)
            sys.exit(1)

    def get_nidaq_config(self) -> NiDaqConfig:
        """Get the nidaq module configuration."""
        try:
            item = self._yaml['modules']['nidaq']
            device = item['device']
            return NiDaqConfig(device, device + '/' + item['signal_channel'], device + '/' + item['encoder_lines'],
                               device + '/' + item['di_lines'], device + '/' + item['do_lines'],
                               device + '/' + item['timing_counter'], item['timing_source'])
        except KeyError as exc:
            print('FATAL: Missing or invalid nidaq module configuration: ', exc, file=sys.stderr)
            sys.exit(1)

    def get_serial_debug_config(self) -> SerialDebugConfig:
        """Get the serial debug module configuration."""
        try:
            item = self._yaml['modules']['serial_debug']
            return SerialDebugConfig(item['path'], item['ports'], item['baudrate'], item['mode'], item['bufsize'], item['timeout'])
        except KeyError as exc:
            print('FATAL: Missing or invalid serial debug module configuration: ', exc, file=sys.stderr)
            sys.exit(1)

    def get_test_yaml(self):
        """Gets the raw YAML representation of the test configuration."""
        try:
            return self._yaml['test']
        except KeyError as exc:
            print('FATAL: Missing or invalid test configuration: ', exc, file=sys.stderr)
            sys.exit(1)

    def get_touch_config(self) -> TouchConfig:
        """Gets the touch module configuration."""
        try:
            item = self._yaml['modules']['touch']
            # return TouchConfig(item['aa_port'], item['aa_addr'], item['aa_timeout_ms'], array('B', item['touch_request']),
            #                    array('B', item['touch_response']))
            return TouchConfig(item['aa_port'], item['aa_addr'], item['aa_timeout_ms'], item['int_timeout_ms'], array('B', item['touch_request']),
                               item['touch_responses'])
        except KeyError as exc:
            print('FATAL: Missing or invalid touch module configuration: ', exc, file=sys.stderr)
            sys.exit(1)
