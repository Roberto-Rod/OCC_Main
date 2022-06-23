#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig NI 6363 Device Support."""

import logging

import numpy as np

from nidaqmx import Task
from nidaqmx.constants import AcquisitionType, Signal, TerminalConfiguration
from nidaqmx.stream_readers import AnalogMultiChannelReader, AnalogSingleChannelReader, DigitalSingleChannelReader
from nidaqmx.stream_writers import AnalogSingleChannelWriter, AnalogMultiChannelWriter, DigitalSingleChannelWriter

from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'AnalogInputTask',
    'AnalogInputWaveformTask',
    'AnalogOutputTask',
    'AnalogOutputWaveformTask',
    'DigitalInputTask',
    'DigitalInputOnChangeTask',
    'DigitalInputWaveformTask',
    'DigitalOutputTask',
    'DigitalOutputWaveformTask'
]


################################################################################
# Analog Input Device Classes
################################################################################

class AnalogInputTask(Task):
    """A task to read the specified analog input channel(s) on-demand.

       An initial sample is read immediately on task creation and then further samples on-demand if required until the task is
       stopped or cleared.
    """

    # Public data
    data = None

    # Private data
    _reader = None

    def __init__(self, channel: str, data: np.ndarray, min_val: float = -5., max_val: float = 5.):
        """Creates an AnalogInputTask.

        :param channel (str): the names of the physical channels to use to create virtual channels.
        :param data (ndarray): a  preallocated 1D NumPy array of floating-point values to hold the samples requested.
        :param min_value (float): the minimum value you expect to measure.
        :param max_value (float): the maximum value you expect to measure.
        """
        logger.debug("AnalogInputTask.__init__: channel = '%s', data.shape = '%s', min_val = %.4f, max_val = %.4f",
                     channel, data.shape, min_val, max_val)
        super().__init__()
        self.data = data
        self.ai_channels.add_ai_voltage_chan(channel, terminal_config=TerminalConfiguration.DIFFERENTIAL, min_val=min_val,
                                             max_val=max_val)
        self._reader = AnalogMultiChannelReader(self.in_stream)
        self._reader.read_one_sample(self.data)
        logger.debug("AnalogInputTask.__init__: data = %s", str(self.data))

    def read_one_sample(self) -> None:
        """Read a further on-demand sample from the analog input channel(s)."""
        self._reader.read_one_sample(self.data)
        logger.debug("AnalogInputTask.read_one_sample: data = %s", str(self.data))


class AnalogInputWaveformTask(Task):
    """A task to read the specified analog input channel multiple times.

       Multiple samples are read immediately on task creation in one burst at the specified rate.
    """

    # Public data
    data = None

    # Private data
    _reader = None

    def __init__(self, channel: str, data: np.ndarray, rate: float, samp_clk_source: str = "", min_val: float = -5.,
                 max_val: float = 5.):
        """Creates an AnalogInputWaveformTask.

        :param channel (str): the physical channel.
        :param data (ndarray): a preallocated 1D NumPy array of floating-point values to hold the samples requested.
        :param rate (float): the sampling rate in samples per channel per second.
        If you use an external source for the Sample Clock, set this input to the maximum expected rate of that clock.
        :param samp_clk_source (str): the source terminal of the sample clock.
        Leave this input unspecified to use the default onboard clock of the device.
        :param min_value (float): the minimum value you expect to measure.
        :param max_value (float): the minimum value you expect to measure.
        """
        logger.debug("AnalogInputWaveformTask: channel = '%s', data.shape = '%s', rate = %.1f, samp_clk_source = '%s', "
                     "min_val = %.4f, max_val = %.4f", channel, data.shape, rate, samp_clk_source, min_val, max_val)
        super().__init__()
        self.data = data
        self.ai_channels.add_ai_voltage_chan(channel, terminal_config=TerminalConfiguration.DIFFERENTIAL, min_val = min_val,
                                             max_val = max_val)
        self.timing.cfg_samp_clk_timing(rate, source=samp_clk_source, samps_per_chan=len(data))
        self._reader = AnalogSingleChannelReader(self.in_stream)
        self._reader.read_many_sample(self.data)
        logger.debug("AnalogInputWaveformTask.__init__: data = %s", str(self.data))

    def read_many_sample(self) -> None:
        """Read a further burst of on-demand samples from the analog input channel(s)."""
        self._reader.read_many_sample(self.data)
        logger.debug("AnalogInputWaveformTask.read_many_sample: data = %s", str(self.data))


################################################################################
# Analog Output Device Classes
################################################################################

class AnalogOutputTask(Task):
    """A task to write the specified analog output channel(s) on-demand.

       An initial sample is written immediately on task creation and then further samples on-demand if required until the task is
       stopped or cleared.
    """

    # Private data
    _writer = None

    # Public data
    data = None

    def __init__(self, channel: str, data: np.ndarray, min_val: float = -5., max_val: float = 5.):
        """Creates an AnalogOutputTask.

        :param channel (str): the names of the physical channels to use to create virtual channels.
        :param data (Any): a 1D NumPy array of a floating-point samples to write to the task.
        :param min_value (float): the minimum value you expect to generate.
        :param max_value (float): the minimum value you expect to generate.
        """
        logger.debug("AnalogOutputTask.__init__: channel = '%s', data.shape = '%s', min_val = %.4f, max_val = %.4f",
                     channel, data.shape, min_val, max_val)
        super().__init__()
        self.data = data
        self.ao_channels.add_ao_voltage_chan(channel, min_val = min_val, max_val = max_val)
        self._writer = AnalogMultiChannelWriter(self.out_stream)
        self._writer.write_one_sample(self.data)
        logger.debug("AnalogOutputTask.__init__: data = %s", str(self.data))

    def write_one_sample(self) -> None:
        """Writes a further on-demand sample to the analog output channel(s)."""
        self._writer.write_one_sample(self.data)
        logger.debug("AnalogOutputTask.write_one_sample: data = %s", str(self.data))


class AnalogOutputWaveformTask(Task):
    """A task to write the specified analog output channel multiple times.

       Multiple samples are written immediately on task creation in one burst at the specified rate.
    """

    # Public data
    data = None

    # Private data
    _writer = None

    def __init__(self, channel: str, rate: float, data: np.ndarray, samp_clk_source: str = "", min_val: float = -5.,
                 max_val: float = 5., sample_mode: AcquisitionType = AcquisitionType.FINITE):
        """Creates an AnalogOutputWaveformTask.

           :param channel (str): the physical channel.
           :param rate (float): the sampling rate in samples per channel per second.
           If you use an external source for the Sample Clock, set this input to the maximum expected rate of that clock.
           :param data (ndarray): a 1D NumPy array of floating-point samples.
           :param samp_clk_source (str): the source terminal of the sample clock.
           Leave this input unspecified to use the default onboard clock of the device.
           :param min_value (float): the minimum value you expect to generate.
           :param max_value (float): the minimum value you expect to generate.
           :param sample_mode (AcquisitionType): if the task generates samples continuously or if it generates a finite number of
           samples.
        """
        logger.debug("AnalogOutputWaveformTask: channel = '%s', data.shape = '%s', rate = %.1f, samp_clk_source = '%s', "
                     "min_val = %.4f, max_val = %.4f, sample_mode = %s", channel, data.shape, rate, samp_clk_source, min_val,
                     max_val, sample_mode)
        super().__init__()
        self.data = data
        self.ao_channels.add_ao_voltage_chan(channel, min_val=min_val, max_val=max_val)
        self.timing.cfg_samp_clk_timing(rate, source=samp_clk_source, sample_mode=sample_mode, samps_per_chan=len(data))
        self._writer = AnalogSingleChannelWriter(self.out_stream)
        self._writer.write_many_sample(data)


################################################################################
# Digital Input Device Classes
################################################################################

class DigitalInputTask(Task):
    """A task to read the specified digital input lines on-demand.

       An initial sample is read immediately on task creation and then further samples on-demand if required until the task is
       stopped or cleared.
     """

    # Public data
    data = None

    # Private data
    _reader = None

    def __init__(self, lines: str, data: np.ndarray):
        """Creates a DigitalInputTask.

           :param lines (str): the names of the digital lines or ports to use to create virtual channels.
           :param data (ndarray): a preallocated 1D NumPy array of booleans to hold the samples requested.
        """
        logger.debug("DigitalInputTask.__init__: lines = '%s', data.shape = '%s'", lines, data.shape)
        super().__init__()
        self.data = data
        self.di_channels.add_di_chan(lines)
        self._reader = DigitalSingleChannelReader(self.in_stream)
        self._reader.read_one_sample_multi_line(self.data)
        logger.debug("DigitalInputTask.__init__: data = %s", str(self.data))

    def read_one_sample(self) -> None:
        """Reads a further on-demand sample from the digital input lines or ports."""
        self._reader.read_one_sample_multi_line(self.data)
        logger.debug("DigitalInputTask.read_one_sample: data = %s", str(self.data))


class DigitalInputOnChangeTask(Task):
    """A task to read the specified digital input lines on-change.

        An initial sample is read immediately on task creation using a Task and then further samples on-change until the task is
        stopped or cleared.

        On-change detection requires buffered access so on the NI 6363 this class can only be used with port 0.
     """

    # Public data
    data = None

    # Private data
    _reader = None

    def __init__(self, lines: str, data: np.ndarray) -> None:
        """Creates a DigitalInputOnChangeTask.

           :param lines (str): the names of the digital lines or ports to use to create virtual channels.
           :param data (ndarray): a preallocated 1D NumPy array of booleans to hold the samples requested.
        """
        logger.debug("DigitalInputOnChangeTask.__init__: lines = '%s', data.shape = '%s'", lines, data.shape)
        super().__init__()
        with Task() as task:
            task.di_channels.add_di_chan(lines)
            reader = DigitalSingleChannelReader(task.in_stream)
            reader.read_one_sample_multi_line(data)
        logger.debug("DigitalInputOnChangeTask.__init__: data = %s", str(data))
        self.data = data
        filtered_channel = self.di_channels.add_di_chan(lines)
        filtered_channel.di_dig_fltr_enable = True
        filtered_channel.di_dig_fltr_min_pulse_width = 10.240000e-6
        self.timing.cfg_change_detection_timing(rising_edge_chan=lines, falling_edge_chan=lines,
                                                sample_mode=AcquisitionType.CONTINUOUS)
        self.register_signal_event(Signal.CHANGE_DETECTION_EVENT, self._on_change)
        self._reader = DigitalSingleChannelReader(self.in_stream)
        self.start()

    def _on_change(self, task_handle, signal_type, callback_data):
        """Callback for on change detection."""
        #pylint: disable=unused-argument
        self._reader.read_one_sample_multi_line(self.data)
        logger.debug("DigitalInputOnChangeTask._on_change: data = %s", str(self.data))
        return 0


class DigitalInputWaveformTask(Task):
    """A task to read a digital waveform input from the specified lines.

       This class supports reading of multiple samples to one or more port lines.

       Waveform input requires buffered access so on the NI 6363 this class can only be used with port 0.
    """

    # Public data
    data = None

    # Private data
    _reader = None

    def __init__(self, lines: str, data: np.ndarray, rate: float, samp_clk_source: str = "",
                 sample_mode: AcquisitionType = AcquisitionType.FINITE):
        """Creates a DigitalInputWaveformTask.

           :param lines (str): the names of the digital lines or ports to use to create virtual channels.
           :param data (Any): a preallocated 1D NumPy array of 32-bit unsigned integer values to hold the samples requested.
           :param rate (float): the sampling rate in samples per channel per second.
           If you use an external source for the Sample Clock, set this input to the maximum expected rate of that clock.
           :param samp_clk_source (str): the source terminal of the sample clock.
           Leave this input unspecified to use the default onboard clock of the device.
           :param sample_mode (AcquisitionType): if the task generates samples continuously or if it generates a finite number of
           samples.
        """
        logger.debug("DigitalInputWaveformTask: lines = '%s', data.shape = '%s', rate = %.1f, samp_clk_source = '%s', "
                     "sample_mode = %s", lines, data.shape, rate, samp_clk_source, sample_mode)
        super().__init__()
        self.data = data
        self.di_channels.add_di_chan(lines)
        self.timing.cfg_samp_clk_timing(rate=rate, source=samp_clk_source, sample_mode=sample_mode, samps_per_chan = len(data))
        self._reader = DigitalSingleChannelReader(self.in_stream)
        self._reader.read_many_sample_port_uint32(data)


################################################################################
# Digital Output Device Classes
################################################################################

class DigitalOutputTask(Task):
    """A task to write the specified digital output lines on-demand.

       An initial sample is writen immediately on task creation and then further samples on-demand if required until the task is
       stopped or cleared.
     """

    # Public data
    data = None

    # Private data
    _writer = None

    def __init__(self, lines: str, data: np.ndarray) -> None:
        """Creates a DigitalOutputTask.

        :param lines (str): the names of the digital lines or ports to use to create virtual channels.
        :param data (ndarray): a preallocated 1D NumPy array of boolean samples to write to the task.
        """
        logger.debug("DigitalOutputTask.__init__: lines = '%s', data.shape = '%s'", lines, data.shape)
        super().__init__()
        self.data = data
        self.do_channels.add_do_chan(lines)
        self._writer = DigitalSingleChannelWriter(self.out_stream)
        self._writer.write_one_sample_multi_line(self.data)
        logger.debug("DigitalOutputTask.__init__: data = %s", str(self.data))

    def write_one_sample(self) -> None:
        """Writes a further on-demand sample to the digital input lines or ports."""
        self._writer.write_one_sample_multi_line(self.data)
        logger.debug("DigitalOutputTask.write_one_sample: data = %s", str(self.data))


class DigitalOutputWaveformTask(Task):
    """A task to write a digital waveform output to the specified lines.

       This class supports writing of multiple samples to one or more port lines.

       Waveform output requires buffered access so on the NI 6363 this class can only be used with port 0.
    """

    # Local data
    data = None
    _writer = None

    def __init__(self, lines: str, rate:float, data: np.ndarray, samp_clk_source: str = "",
                 sample_mode: AcquisitionType = AcquisitionType.FINITE):
        """Creates a DigitalOutputWaveformTask.

           :param lines (str): the names of the digital lines or ports to use to create virtual channels.
           :param rate (float): the sampling rate in samples per channel per second.
           If you use an external source for the Sample Clock, set this input to the maximum expected rate of that clock.
           :param data (Any): a 1D NumPy array of 32-bit unsigned integer samples to write to the task.
           :param samp_clk_source (str): the source terminal of the sample clock.
           Leave this input unspecified to use the default onboard clock of the device.
           :param sample_mode (AcquisitionType): if the task generates samples continuously or if it generates a finite number of
           samples.
        """
        logger.debug("DigitalOutputWaveformTask: lines = '%s', rate = %.1f, data.shape = '%s', samp_clk_source = '%s', "
                     "sample_mode = %s", lines, rate, data.shape, samp_clk_source, sample_mode)
        super().__init__()
        self.data = data
        self.do_channels.add_do_chan(lines)
        self.timing.cfg_samp_clk_timing(rate=rate, source=samp_clk_source, sample_mode=sample_mode, samps_per_chan = len(data))
        self._writer = DigitalSingleChannelWriter(self.out_stream, auto_start = False)
        self._writer.write_many_sample_port_uint32(data)
