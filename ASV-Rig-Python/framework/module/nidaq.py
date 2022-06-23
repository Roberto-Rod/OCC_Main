#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig NI DAQ Module Implementation."""

import logging
from threading import Lock
import threading
from time import sleep
import sys

import numpy as np

from nidaqmx import Task
from nidaqmx.constants import AcquisitionType

from framework.device.ni6363 import AnalogOutputTask, AnalogOutputWaveformTask
from framework.device.ni6363 import DigitalInputOnChangeTask, DigitalOutputTask, DigitalOutputWaveformTask
from framework.util.config import Config
from framework.util.data import PlaybackData


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'EncoderWaveformTask',
    'PdaWaveformTask',
    'ScanWaveformTask',
    'AnalogOutputControl',
    'DigitalInputOnChangeControl',
    'DigitalOutputControl',
    'NiDaq'
]


################################################################################
# Encoder Waveform Task
################################################################################

class EncoderWaveformTask(DigitalOutputWaveformTask):
    """Implements a streamed encoder waveform task.

       This class provides streaming of the simulated motor encoder pulses A, B and Z on P0.0, P0.1 and P0.2.
       The ndarray of digital sample data should be a 1D array of uint32 where A is bit 0, B is bit 1 and Z is bit 2.
   """

    # Private data
    _lines = None

    def __init__(self, rate: float, encoder_data: np.ndarray, samp_clk_source: str = "",
                 sample_mode: AcquisitionType = AcquisitionType.FINITE):
        """Creates an EncoderWaveformTask.

           :param rate (float): the sampling rate in samples per channel per second.
           :param enc_data (ndarray): a 1D ndarray of uint32 where A is bit 0, B is bit 1 and Z is bit 2.
           If you use an external source for the Sample Clock, set this input to the maximum expected rate of that clock.
           :param samp_clk_source (str): the source terminal of the sample clock.
           Leave this input unspecified to use the default onboard clock of the device.
           :param sample_mode (AcquisitionType): if the task generates samples continuously or if it generates a finite number of
           samples.
        """
        logger.debug("EncoderWaveformTask__init__: rate = %.1f, encoder_data.shape = '%s', samp_clk_source = '%s', "
                     "sample_mode = %s", rate, encoder_data.shape, samp_clk_source, sample_mode)
        self._lines = Config().get_nidaq_config().encoder_lines
        super().__init__(self._lines, rate, encoder_data, samp_clk_source=samp_clk_source, sample_mode=sample_mode)


################################################################################
# PDA Waveform Task
################################################################################

class PdaWaveformTask(AnalogOutputWaveformTask):
    """Implements a streamed PDA signal waveform task.

       This class provides streaming of the simulated PDA signal on AO 0.
       The ndarray of analog sample data should be a 1D arrays of float where AO 0 is the range -5V to +5V.
    """

    def __init__(self, rate: float, signal_data: np.ndarray, samp_clk_source: str = "",
                 sample_mode: AcquisitionType = AcquisitionType.FINITE):
        """Creates a PdaWaveformTask.

           :param rate (float): the sample rate.
           :param signal_data (numpy.ndarray): the analog voltage data.
           :param samp_clk_source (str): the source terminal of the sample clock.
           Leave this input unspecified to use the default onboard clock of the device.
           :param sample_mode (AcquisitionType): if the task generates samples continuously or if it generates a finite number of
           samples.
        """
        logger.debug("PdaWaveformTask.__init__: rate = %.1f, signal_data.shape = '%s', samp_clk_source = '%s', sample_mode = %s",
                     rate, signal_data.shape, samp_clk_source, sample_mode)
        self._channel = Config().get_nidaq_config().signal_channel
        super().__init__(self._channel, rate, signal_data, samp_clk_source=samp_clk_source, sample_mode=sample_mode)


################################################################################
# Measuyrement Waveform Task
################################################################################

class ScanWaveformTask(Task):
    """Implements a synchronised PDA signal and encoder waveform task.

       This class provides synchronised streaming of the simulated PDA signal on AO 0 and the simulated motor encoder pulses A, B
       and Z on P0.0, P0.1 and P0.2.
       The ndarrays of sample data should be 1D arrays of the same length with the AO 0 data being float in the range -5V to +5V
       and the digital data being uint32 where A is bit 0, B is bit 1 and Z is bit 2.
   """

    # Private data
    _counter = None
    _source = None

    def __init__(self, rate: float, signal_data: np.ndarray, encoder_data: np.ndarray,
                 sample_mode: AcquisitionType = AcquisitionType.FINITE):
        """Creates an ScanWaveformTask.

           :param rate (float): the sample rate.
           :param signal_data (numpy.ndarray): the analog voltage data.
           :param encoder_data (numpy.ndarray): the digital encoder data.
           :param sample_mode (AcquisitionType): if the task generates samples continuously or if it generates a finite number of
           samples.
        """
        logger.debug("ScanWaveformTask.__init__: rate = %.1f, pda_data.shape = '%s', enc_data.shape = '%s', sample_mode = %s",
                     rate, signal_data.shape, encoder_data.shape, sample_mode)
        self._counter = Config().get_nidaq_config().timing_counter
        self._source = Config().get_nidaq_config().timing_source
        super().__init__()
        if signal_data.shape != encoder_data.shape:
            logger.fatal('ScanWaveformTask.__init__: AO and DO arrays should be the same shape')
            sys.exit(1)
        ctr = self.co_channels.add_co_pulse_chan_freq(self._counter, freq = rate)
        ctr.co_pulse_term = ''
        self.timing.cfg_implicit_timing(sample_mode=sample_mode, samps_per_chan = len(signal_data))
        self._pda_task = PdaWaveformTask(rate, signal_data, samp_clk_source = self._source, sample_mode=sample_mode)
        self._enc_task = EncoderWaveformTask(rate, encoder_data, samp_clk_source = self._source, sample_mode=sample_mode)

    def __enter__(self):
        logger.debug('ScanWaveformTask.__enter__')
        super().__enter__()
        self._pda_task.__enter__()
        self._enc_task.__enter__()
        return self

    def __exit__(self, exception_type, exception_value, exception_traceback):
        logger.debug('ScanWaveformTask.__exit__')
        self._pda_task.__exit__(exception_type, exception_value, exception_traceback)
        self._enc_task.__exit__(exception_type, exception_value, exception_traceback)
        super().__exit__(exception_type, exception_value, exception_traceback)

    def start(self) -> None:
        logger.debug('ScanWaveformTask.start')
        self._pda_task.start()
        self._enc_task.start()
        super().start()

    def stop(self) -> None:
        logger.debug('ScanWaveformTask.stop')
        super().stop()
        self._pda_task.stop()
        self._enc_task.stop()


################################################################################
# Analog Output Control Class
################################################################################

class AnalogOutputControl:
    """Implements a control for the on-demand analog output.

       The NI DAQ analog channel used is:\n
       AO 0 - -5V/+5V

       NI_AOUT_0 is initialised to 0.000V on initialisation i.e. mid-range.
       This will translate to an NI_AOUT_0_3V3 of 1.667V.
    """

    # Private data
    _channel = None
    _mutex = None

    def __init__(self):
        """Creates an AnalogOutputControl."""
        logger.debug('AnalogOutputControl.__init__')
        self._channel = Config().get_nidaq_config().signal_channel
        self._mutex = Lock()
        self.data = np.array([0.], dtype=float)
        with AnalogOutputTask(self._channel, self.data) as ao_task:
            ao_task.wait_until_done()

    def __enter__(self):
        logger.debug('AnalogOutputControl.__enter__')
        self._mutex.acquire()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.debug('AnalogOutputControl.__exit__')
        self._mutex.release()

    def get_vout(self) -> float:
        """Gets the analog output voltage."""
        logger.debug("AnalogOutputControl.get_vout: vout = %.3f", self.data[0])
        return self.data[0]

    def set_vout(self, vout: float) -> None:
        """Sets the analog output voltage."""
        logger.debug("AnalogOutputControl.set_vout: vout = %.3f", vout)
        self.data[0] = vout
        with AnalogOutputTask(self._channel, self.data) as ao_task:
            ao_task.wait_until_done()

    def reset(self):
        """Reset the AnalogOutputControl object to its default state."""
        logger.debug('AnalogOutputControl.reset()')
        self.data[0] = 0.
        with AnalogOutputTask(self._channel, self.data) as ao_task:
            ao_task.wait_until_done()


################################################################################
# Digital Input On Change Controller Class
################################################################################

class DigitalInputOnChangeControl(DigitalInputOnChangeTask):
    """Implements a control for the n-change digital inputs.

       The NI DAQ digital inputs used are:\n
       P0.4 - Laser LON command (active high).\n
       P0.5 - Encoder M+/M- detection (active high).\n
       P0.6 - Spare.\n
       P0.7 - Spare.

       On-change detection requires buffered access so on the NI 6363 this control can only be used with port 0.
       This controller is implemented as a persistent task.
    """

    # Private constants
    _LSR_LON = 0
    _ENC_M = 1
    _P0_6 = 2
    _P0_7 = 3

    # Private data
    _lines = None
    _lsr_lon_rising_cv = None
    _lsr_lon_falling_cv = None
    _enc_m_rising_cv = None
    _enc_m_falling_cv = None
    _callback_method = None

    def __init__(self):
        """Creates a DigitalInputOnChangeControl."""
        logger.debug('DigitalInputOnChangeControl.__init__')
        self._lines = Config().get_nidaq_config().di_lines
        super().__init__(self._lines, np.zeros(4, dtype=bool))
        self._lsr_lon_rising_cv = threading.Condition()
        self._lsr_lon_falling_cv = threading.Condition()
        self._enc_m_rising_cv = threading.Condition()
        self._enc_m_falling_cv = threading.Condition()

    def _is_lsr_lon_active(self) -> bool:
        """Checks whether LSR_LON is active (high).

           :return: True if LSR_ON is active, False otherwise.
        """
        return self.data[self._LSR_LON]

    def _is_lsr_lon_inactive(self) -> bool:
        """Checks whether LSR_LON is inactive (low).

           :return: True if LSR_ON is inactive, False otherwise.
        """
        return not self.data[self._LSR_LON]

    def is_lsr_lon(self) -> bool:
        """Checks whether LSR_LON is active (high) or inactive (low).

           :return: True if LSR_LON is active (high), False if LSR_LON is inactive (low).
        """
        active = self._is_lsr_lon_active()
        logger.debug("DigitalInputControl.is_lsr_lon: active = %r", active)
        return active

    def wait_for_lsr_lon(self, active: bool) -> None:
        """Wait for LSR_LON to be active (high) or inactive (low)."""
        logger.debug("DigitalInputOnChangeControl.wait_for_lsr_lon: active = %r", active)
        if active:
            with self._lsr_lon_rising_cv:
                self._lsr_lon_rising_cv.wait_for(self._is_lsr_lon_active)
        else:
            with self._lsr_lon_falling_cv:
                self._lsr_lon_falling_cv.wait_for(self._is_lsr_lon_inactive)

    def register_callback(self, callback_method) -> None:
        """Method to allow scripts to monitor digital inputs via callbacks.

           :param callback_method (function): a callback method to be invoked via the on_change callback.
        """
        logger.debug("DigitalInputOnChangeControl.register_callback: callback_method = %s", callback_method)
        self._callback_method = callback_method

    def _is_enc_m_active(self) -> bool:
        """Checks whether ENC_M is active (high)."""
        return self.data[self._ENC_M]

    def _is_enc_m_inactive(self) -> bool:
        """Checks whether ENC_M is inactive (low)."""
        return not self.data[self._ENC_M]

    def is_enc_m(self) -> bool:
        """Checks whether ENC_M is active (high) or inactive (low).

           :return: True if ENC_M is active (high), False if ENC_M is inactive (low).
        """
        active = self._is_enc_m_active()
        logger.debug("DigitalInputOnChangeControl.is_enc_m: active = %r", active)
        return active

    def wait_for_enc_m(self, active: bool) -> None:
        """Wait for ENC_M to be active (high) or inactive (low)."""
        logger.debug("DigitalInputOnChangeControl.wait_for_enc_m: active = %r", active)
        if active:
            with self._enc_m_rising_cv:
                self._enc_m_rising_cv.wait_for(self._is_enc_m_active)
        else:
            with self._enc_m_falling_cv:
                self._enc_m_falling_cv.wait_for(self._is_enc_m_inactive)

    def _on_change(self, task_handle, signal_type, callback_data):
        """Callback for on change detection."""
        super()._on_change(task_handle, signal_type, callback_data)
        logger.debug("DigitalInputOnChangeControl._on_change: LSR_LON active = %r, ENC_M active = %r", self._is_lsr_lon_active(),
                     self._is_enc_m_active())
        # Unblock any threads waiting for changes
        with self._lsr_lon_rising_cv:
            if self._is_lsr_lon_active():
                self._lsr_lon_rising_cv.notify_all()
        with self._lsr_lon_falling_cv:
            if self._is_lsr_lon_inactive():
                self._lsr_lon_falling_cv.notify_all()
        with self._enc_m_rising_cv:
            if self._is_enc_m_active():
                self._enc_m_rising_cv.notify_all()
        with self._enc_m_falling_cv:
            if self._is_enc_m_inactive():
                self._enc_m_falling_cv.notify_all()
        # Invoke any high level callback (if registered)
        if self._callback_method:
            self._callback_method()
        return 0

    def reset(self):
        """Reset the DigitalInputOnChangeControl object to its default state."""
        logger.debug('DigitalInputOnChangeControl.reset()')


################################################################################
# Digital Output Control Class
################################################################################

class DigitalOutputControl(DigitalOutputTask):
    """Implements a control for the on-demand digital outputs.

       The NI DAQ digital outputs used are:\n
       P1.0 - Laser LPON confirmation (active high).\n
       P1.1 - USB pass-through enable (active high).\n
       P1.2 - DUT power enable (active high).\n
       P1.3 - Spare.

       This controller is implemented as a persistent task.
    """

    # Private constants
    _LSR_LPON1 = 0
    _USB_EN = 1
    _DUT_EN = 2
    _P1_3 = 3

    def __init__(self):
        """Creates a DigitalOutputControl."""
        logger.debug('DigitalOutputControl.__init__')
        self._lines = Config().get_nidaq_config().do_lines
        super().__init__(self._lines, np.array([False, False, False, False]))

    def _is_lsr_lpon1_active(self) -> bool:
        """Checks whether LSR_LPON1 is active (high).

           :return: True if LSR_LPON1 is active, False otherwise.
        """
        return self.data[self._LSR_LPON1]

    def is_lsr_lpon1(self) -> bool:
        """Checks whether LSR_LPON1 output is active (high).

           :return: returns True if LSR_LPON1 is active (high), False if LSR_LPON1 is inactive (low).
        """
        active = self._is_lsr_lpon1_active()
        logger.debug("DigitalOutputControl.is_lsr_lpon1: active = %r", active)
        return active

    def set_lsr_lpon1(self, active: bool) -> None:
        """Set LSR_LPON1 active (high) or inactive (low)."""
        logger.debug("DigitalOutputControl.set_lsr_lpon1: active = %r", active)
        self.data[self._LSR_LPON1] = active
        self.write_one_sample()

    def _is_usb_en_active(self) -> bool:
        """Checks whether USB_EN is active (high).

           :return: True if USB_EN is active, False otherwise.
        """
        return self.data[self._USB_EN]

    def is_usb_en(self) -> bool:
        """Checks whether USB_EN output is active (high).

           :return: returns True if USB_EN is active (high), False if USB_EN is inactive (low).
        """
        active = self._is_usb_en_active()
        logger.debug("DigitalOutputControl.is_usb_en: active = %r", active)
        return active

    def set_usb_en(self, active: bool) -> None:
        """Set USB_EN output active (high) or inactive (low)."""
        logger.debug("DigitalOutputControl.set_usb_en: ACTIVE = %r", active)
        self.data[self._USB_EN] = active
        self.write_one_sample()

    def _is_dut_en_active(self) -> bool:
        """Checks whether DUT_EN is active (high).

           :return: True if DUT_EN is active, False otherwise.
        """
        return self.data[self._DUT_EN]

    def is_dut_en(self) -> bool:
        """Checks whether DUT_EN output is active (high).

           :return: returns True if DUT_EN is active (high), False if DUT_EN is inactive (low).
        """
        active = self._is_dut_en_active()
        logger.debug("DigitalOutputControl.is_dut_en: active = %r", active)
        return active

    def set_dut_en(self, active: bool) -> None:
        """Set DUT_EN output active (high) or inactive (low)."""
        logger.debug("DigitalOutputControl.set_dut_en: active = %r", active)
        self.data[self._DUT_EN] = active
        self.write_one_sample()

    def reset(self):
        """Reset the DigitalOutputControl object to its default state."""
        logger.debug('DigitalOutputControl.reset()')
        self.data[self._LSR_LPON1] = False
        self.data[self._USB_EN] = False
        self.data[self._DUT_EN] = False
        self.data[self._P1_3] = False
        self.write_one_sample()


################################################################################
# NI DAQ Control Class
################################################################################

class NiDaq():
    """NI DAQ Control."""

    # Private data
    _instance = None
    _mutex = None
    _auto_lpon1 = None

    # Public data
    aout = None
    din = None
    dout = None

    def __new__(cls):
        logger.debug('NiDaq.__new__')
        if cls._instance is None:
            logger.info('NiDaq.__new__: creating the singleton instance')
            cls._instance = super(NiDaq, cls).__new__(cls)
            cls._mutex = Lock()
            cls._auto_lpon1 = False
            cls.aout = AnalogOutputControl()
            cls.din = DigitalInputOnChangeControl()
            cls.dout = DigitalOutputControl()
        return cls._instance

    def __enter__(self):
        logger.debug('NiDaq.__enter__')
        self._mutex.acquire()
        self.aout.__enter__()
        self.din.__enter__()
        self.dout.__enter__()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.debug('NiDaq.__exit__')
        self.aout.__exit__(exc_type, exc_val, exc_tb)
        self.din.__exit__(exc_type, exc_val, exc_tb)
        self.dout.__exit__(exc_type, exc_val, exc_tb)
        self._mutex.release()

    def is_auto_lpon1(self) -> bool:
        """Checks whether automatic LPON1 tracking of LON is active.

           :return: True if automatic LPON1 tracking is active, False otherwise.
        """
        active = self._auto_lpon1
        logger.debug("NiDaq.is_auto_lpon1: active = %r", active)
        return active

    def set_auto_lpon1(self, active: bool) -> None:
        """Enables or disables automatic (software) tracking of LPON1 by LON."""
        logger.debug("NiDaq.set_auto_lpon1: active = %r", active)
        self._auto_lpon1 = active
        if self._auto_lpon1:
            self.din.register_callback(self._din_on_change_callback)
        else:
            self.din.register_callback(None)

    def _din_on_change_callback(self):
        """The DigitalInputOnChange on change callback method."""
        logger.debug('NiDaq.din_on_change_callback')
        if self._auto_lpon1:
            self.dout.set_lsr_lpon1(self.din.is_lsr_lon())

    def reset(self):
        """Reset the NiDaq object to its default state."""
        logger.debug('NiDaq.reset()')
        self.aout.reset()
        self.din.reset()
        self.dout.reset()


################################################################################
# Encoder Waveform Test Methods
################################################################################

def _test_encoder_waveform_task(fname: str) -> None:
    """Test method for the EncoderWaveformTask class."""
    logger.info('loading ...')
    data = PlaybackData(fname)
    logger.info('ready ...')
    with EncoderWaveformTask(data.get_rate(), data.get_encoder_data()) as task:
        task.start()
        task.wait_until_done()
    logger.info('done')


################################################################################
# PDA Waveform Test Methods
################################################################################

def _test_pda_waveform_task(fname: str) -> None:
    """Test method for the PdaWaveformTask class."""
    logger.info('loading ...')
    data = PlaybackData(fname)
    logger.info('ready ...')
    with PdaWaveformTask(data.get_rate(), data.get_signal_data()) as task:
        task.start()
        task.wait_until_done()
    logger.info('done')


################################################################################
# Scan Waveform Test Methods
################################################################################

def _test_scan_waveform_task(fname: str) -> None:
    """Test method for the ScanWaveformTask class."""
    logger.info('loading ...')
    data = PlaybackData(fname)
    logger.info('ready ...')
    with ScanWaveformTask(data.get_rate(), data.get_signal_data(), data.get_encoder_data()) as task:
        task.start()
        task.wait_until_done()
    logger.info('done')


################################################################################
# Analog Output Controller Test Methods
################################################################################

def _test_analog_output_controller():
    """Test method for the AnalogOutputControl."""
    with AnalogOutputControl() as ao_control:
        print(ao_control.data)
        sleep(1.)
        for val in range(-5, 6, 1):
            ao_control.set_vout(float(val))
            print(ao_control.data)
            sleep(1.)
        ao_control.set_vout(0.)
        print(ao_control.data)


################################################################################
# Digital Input Controller Test Methods
################################################################################

def _test_digital_input_controller():
    """Test method for the DigitalInputControl."""
    with DigitalInputOnChangeControl() as di_control:
        di_control.is_lsr_lon()
        di_control.is_enc_m()


################################################################################
# Digital Output Controller Test Methods
################################################################################

def _test_digital_output_controller():
    """Test method for the DigitalOutputControl."""
    with DigitalOutputControl() as do_control:
        do_control.is_lsr_lpon1()
        do_control.is_usb_en()
        do_control.is_dut_en()
        do_control.set_dut_en(True)
        do_control.set_usb_en(True)
        do_control.set_lsr_lpon1(True)
        do_control.is_lsr_lpon1()
        do_control.is_usb_en()
        do_control.is_dut_en()
        do_control.set_dut_en(False)
        do_control.set_usb_en(False)
        do_control.set_lsr_lpon1(False)


# python -m framework.module.nidaq .\framework\module\nidaq.py
if __name__ == "__main__":
    #_test_encoder_waveform_task('./data/tuning4.csv')
    #_test_pda_waveform_task('./data/scanning_with_eye_signal2.csv')
    #_test_scan_waveform_task('./data/scanning_with_eye_signal2.csv')
    #_test_analog_output_controller()
    #_test_digital_input_controller()
    #_test_digital_output_controller()
    pass
