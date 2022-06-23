#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Automated Software Verification Rig Framework.Util Package."""

import logging

from framework.util.config import Config

config = Config().get_logging_config()
logger = logging.getLogger(__package__)
if __package__ in config.levels:
    logger.setLevel(config.levels[__package__])
else:
    logger.setLevel(config.level)
