#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Automated Software Verification Rig Framework Package."""

from datetime import datetime
import logging
import os
import sys

from framework.util.config import Config

# pylint: disable=broad-except

try:
    config = Config().get_logging_config()
    logger = logging.getLogger()
    logger.setLevel(config.level)
    formatter = logging.Formatter('[%(asctime)s] p%(process)s {%(pathname)s:%(lineno)d} %(levelname)s - %(message)s')
    fname = config.path + '\\logging-' + datetime.now().strftime('%Y%m%d%H%M%S-pid') + str(os.getpid()) + '.txt'
    f_h = logging.FileHandler(filename=fname, mode=config.mode, encoding='utf-8')
    f_h.setLevel(logging.DEBUG)
    f_h.setFormatter(formatter)
    logger.addHandler(f_h)
    c_h = logging.StreamHandler()
    c_h.setLevel(logging.INFO)
    c_h.setFormatter(formatter)
    logger.addHandler(c_h)
except Exception as exc:
    print('FATAL: Failed to configure framework logging: ', exc.with_traceback, file=sys.stderr)
    sys.exit(1)
