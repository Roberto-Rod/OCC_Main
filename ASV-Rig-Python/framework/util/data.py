#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Data Utility."""

import logging
import os
from typing import Dict, Tuple
import sys

import numpy as np

#pylint: disable=wildcard-import
from framework.constants import *
from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'PlaybackFileReader',
    'PlaybackDataConverter',
    'PlaybackData'
]


class PlaybackFileReader:
    """This class reads a playback data file for a single encoder calibration or measurement simulation.

       The playback data is read from a CSV file.
       The first three columns contain the binary motor encoder signals A, B and Z.
       The fourth column contains the signal voltage that is to be presented to the PDC via the 5M1 resistor on the LDA (0 to 5V).
       The fifth column is used to separate the test data into bundles to indicate suitable break points during playback.

       Optionally the first lines of the file contains metadata as key=value pairs on lines starting with a '#'.
       There is then a single header line which does not start with a '#'.
       The rest of the file contains data lines.

       # rate=1000000Hz\n
       A (binary), B (binary), Z (binary), signal (V fed to PDC via 5M1R on LDA), separate bundles (binary)\n
       0,0,0,2.50000,0\n
       1,0,0,2.51740,0\n
       1,1,0,2.51714,0\n
       ...\n
       0,0,0,2.51785,1\n
       1,0,0,2.51740,1\n
       1,1,0,2.51714,1\n
       ...\n
       0,0,0,2.51785,0\n
       1,0,0,2.51740,0\n
       1,1,0,2.51714,0

       A caching mechanism is available whereby a numpy NPZ file is written following a successful load of the CSV file.
       Further loads of the same file will only need to process the header metadata and can load the raw data arrays from the NPZ
       file.
       The file size and timestamps are checked to make sure the CSV file has not been updated since the NPZ file was written.
    """

    # Local variables
    _skiprows = None
    _use_cache = None

    def __init__(self, use_cache: bool = True):
        logger.debug("PlaybackFileReader.__init__: usecache = %r", use_cache)
        self._skiprows = 1
        self._use_cache = use_cache

    def read(self, fname: str) -> Tuple[Dict[str, str], Tuple[np.ndarray]]:
        """Read a playback data file.

           :param fname (str): the filename of the CSV playback data file.
        """
        logger.debug("PlaybackFileReader.read: fname = '%s'", fname)
        # Check file extension is CSV
        fext = os.path.splitext(fname)[1].lower()
        if fext != '.csv':
            logger.fatal("PlaybackFileReader.read: Invalid file extension '%s', expected '.csv'", fext)
            sys.exit(1)
        # Verify that the file exists
        if not os.path.isfile(fname):
            logger.fatal("PlaybackFileReader.read: No such file '%s'", fname)
            sys.exit(1)
        # Read and return the metadata and data
        meta = self._read_meta(fname)
        data = self._read_data(fname)
        return (meta, data)

    def _read_meta(self, fname: str) -> Dict[str, str]:
        """Read metadata from the comment header.

           :param fname (str): the filename of the CSV playback data file.
        """
        logger.debug("PlaybackFileReader._read_meta: fname = '%s'", fname)
        result: Dict[str, str] = {}
        self._skiprows = 1
        # Process the comment header
        with open(fname, encoding='latin1') as f_in:
            for line in f_in:
                if line.startswith('#'):
                    self._skiprows += 1
                    name, val = line[1:].partition('=')[::2]
                    if val:
                        name = name.strip().lower()
                        val = val.strip()
                        logger.debug("PlaybackData._read_meta: %s = %s", name, val)
                        result[name]=val
                else:
                    break
        return result

    def _read_data(self, fname: str) -> Tuple[np.ndarray]:
        """Read playback data."""
        logger.debug("PlaybackFileReader._read_data: fname = '%s'", fname)
        result: Tuple[np.ndarray] = ()
        # Check to see if caching is enabled
        if self._use_cache:
            # Establish expected cache file name
            npzfname = os.path.splitext(fname)[0] + '.npz'
            # Check to see if cache is present and correct
            if os.path.isfile(npzfname):
                if os.path.getmtime(npzfname) > os.path.getmtime(fname):
                    # Load the raw data from the cache file using numpy.load
                    logger.debug('PlaybackData._read_data: loading data using numpy.load')
                    npzfile = np.load(npzfname)
                    result = (npzfile['A'], npzfile['B'], npzfile['Z'], npzfile['signal'], npzfile['bundle'])
                    logger.debug("PlaybackData._read_data: read %d samples", len(result[0]))
                    return result
                else:
                    logger.debug("PlaybackFileReader._read_data: Cache file '%s' is stale", npzfname)
            else:
                logger.debug("PlaybackFileReader._read_data: No such cache file '%s'", npzfname)
        # Load the raw data from the CSV file using numpy.loadtxt
        logger.debug('PlaybackData._read_data: loading data using numpy.loadtxt')
        result = np.loadtxt(fname, dtype={'names': ('A', 'B', 'Z', 'signal', 'bundle'),
                                          'formats': (np.uint32, np.uint32, np.uint32, np.float64, np.uint32)},
                            comments='#', delimiter=',', skiprows=self._skiprows, unpack=True)
        logger.debug("PlaybackData._read_data: read %d samples", len(result[0]))
        # Check to see if caching is enabled
        if self._use_cache:
            # Cache array data as NPZ file to avoid parsing next time
            logger.debug("PlaybackData._read_data: Writing cache file '%s'", npzfname)
            np.savez_compressed(npzfname, A=result[0], B=result[1], Z=result[2], signal=result[3], bundle=result[4])
        return result


class PlaybackDataConverter:
    """This class transforms raw CSV playback data read from a playback data file to a convenient internal format for playback.

       The raw data is made up of a set of analog samples for playback of the PDA signal into the LDA PCB via AO 0, a set of
       synchronised motor encoder pulses A, B and Z on P0.0, P0.1 and P0.2 and a bundle index to denominate suitable points to
       terminate playback.
       The ndarrays of sample data are held in memory as 1D arrays (of the same length).
       The encoder signals are combined into a single uint32 for streaming to the digital waveform generator.
       The signal voltage is analysed to determine the required settings for the offset and signal digipots and stored in memory as
       the value to be written to AO 0 (-5V to +5V).
       This transformation is done so as to maximise the DAC range used and thus minimise any quantisation noise.
    """

    # Private constants
    _B1_FIXED_VSIG_W = True
    _DEFAULT_RATE = 1000000.0

    def __init__(self):
        logger.debug('PlaybackDataConverter.__init__')

    def convert(self, data: Tuple[Dict[str, str], Tuple[np.ndarray]]) -> Tuple:
        """Convert raw playback data read from a playback data file to a convenient internal format for playback."""
        logger.debug('PlaybackDataConverter.convert')
        # Extract the sample rate from the meta data, if specified, otherwise assume the default
        vals = data[0]
        if 'rate' in vals:
            val = vals['rate'].lower()
            if val.endswith('mhz'):
                rate = 1000000.0 * float(val[:-3])
            elif val.endswith('khz'):
                rate = 1000.0 * float(val[:-3])
            elif val.endswith('hz'):
                rate = float(val[:-2])
            else:
                rate = float(val)
        else:
            rate = self._DEFAULT_RATE
        # The raw data may be read from the specified file or from a cached 'npy' version of it
        raw = data[1]
        # Convert the digital data to the correct 1D uint32 format ready for waveform playback
        digital_data = raw[0] + (raw[1] << 1) +  (raw[2] << 2)
        # Determine the limits of the analog data and thus the required digipot positions
        pda_v_max: float = raw[3].max()
        pda_v_min: float = raw[3].min()
        # Make sure we are within the limits of the interface PCBA design
        if pda_v_max > ASV_PDA_VMAX or pda_v_min < 0.000 or pda_v_max < pda_v_min:
            logger.fatal("PlaybackDataConverter.convert: pda_v_max = %.3f, pda_v_min = %.3f", pda_v_max, pda_v_min)
            sys.exit(1)
        logger.debug("PlaybackDataConverter.convert: pda_v_max = %.3f, pda_v_min = %.3f", pda_v_max, pda_v_min)
        # Determine the desired VOFF and associated wiper position
        voff = min(pda_v_min, ASV_DIGIPOT_VOFF_MAX)
        voff_w = round((voff / ASV_DIGIPOT_VOFF_MAX) * float(ASV_DIGIPOT_STEPS_MAX))
        # Determine the peak VSIG and associated wiper position
        if self._B1_FIXED_VSIG_W:
            # On the B1 boards there is an issue with back feeding the VSIG digipot via R30.
            # To get round this we always set vsig_w to maximum i.e. connected directly to the NI ADC tap point.
            # Note: this reduces the range of the NI DAC but not seriously.
            vsig = ASV_DIGIPOT_VSIG_MAX
            vsig_w = ASV_DIGIPOT_STEPS_MAX
        else:
            vsig = pda_v_max - voff
            vsig_w = round((vsig / ASV_DIGIPOT_VSIG_MAX) * float(ASV_DIGIPOT_STEPS_MAX))
        # Sanity check
        if voff_w > ASV_DIGIPOT_STEPS_MAX or vsig_w > ASV_DIGIPOT_STEPS_MAX:
            logger.fatal("PlaybackDataConverter.convert: voff = %.3f, voff_w = %d, vsig = %.3f, vsig_w = %d", voff, voff_w, vsig,
                         vsig_w)
            sys.exit(1)
        logger.debug("PlaybackDataConverter.convert: voff = %.3f, voff_w = %d, vsig = %.3f, vsig_w = %d", voff, voff_w, vsig,
                     vsig_w)
        # Convert the analog data to the correct 1D float64 format ready for waveform playback
        if vsig != 0.:
            analog_data = (raw[3] - voff) / vsig * (ASV_NI_DAQ_AO_0_VMAX - ASV_NI_DAQ_AO_0_VMIN) + ASV_NI_DAQ_AO_0_VMIN
        else:
            analog_data = (raw[3] - voff) + ASV_NI_DAQ_AO_0_VMIN
        # Determine the limits of the shifted analog data
        ao0_v_max: float = analog_data.max()
        ao0_v_min: float = analog_data.min()
        logger.debug("PlaybackDataConverter.convert: ao0_v_max = %.3f, ao0_v_min = %.3f", ao0_v_max, ao0_v_min)
        # Successfully converted
        logger.debug("PlaybackDataConverter.convert: samples = %d rate = %.1f Hz", len(raw[0]), rate)
        return (rate, voff_w, vsig_w, digital_data, analog_data)


class PlaybackData:
    """This class holds the playback data for a single encoder tuning or measurement simulation.

       The raw data is made up of a set of analog samples for playback of the PDA signal into the LDA PCB via AO 0, a set of
       synchronised motor encoder pulses A, B and Z on P0.0, P0.1 and P0.2 and a bundle index to denominate suitable points to
       terminate playback.
       The ndarrays of sample data are held in memory as 1D arrays (of the same length) with the digital data samples being uint32
       where A is bit 0, B is bit 1 and Z is bit 2 and with the analog data being float64 in the range -5V to +5V.
    """

    # Private variables
    _rate = None
    _voff_w = None
    _vsig_w = None
    _encoder_data = None
    _signal_data = None

    def __init__(self, fname: str):
        logger.debug("PlaybackData.__init__: fname = '%s'", fname)
        self._fname = fname
        reader = PlaybackFileReader(fname)
        data = reader.read(fname)
        converter = PlaybackDataConverter()
        (self._rate, self._voff_w, self._vsig_w, self._encoder_data, self._signal_data) = converter.convert(data)

    def get_fname(self) -> float:
        """Gets the playback data filename."""
        logger.debug("PlaybackData.get_fname: fname = '%s'", self._fname)
        return self._rate

    def get_rate(self) -> float:
        """Gets the sample rate."""
        logger.debug("PlaybackData.get_rate: rate = %.1f", self._rate)
        return self._rate

    def get_voff_w(self) -> int:
        """Gets the voff digipot wiper position."""
        logger.debug("PlaybackData.get_voff_w: voff_w = %d", self._voff_w)
        return self._voff_w

    def get_vsig_w(self) -> int:
        """Gets the vsig digipot wiper position."""
        logger.debug("PlaybackData.get_vsig_w: vsig_w = %d", self._vsig_w)
        return self._vsig_w

    def get_encoder_data(self) -> np.ndarray:
        """Gets the encoder waveform data."""
        logger.debug("PlaybackData.get_encoder_data: shape = %s", str(self._encoder_data.shape))
        return self._encoder_data

    def get_signal_data(self) -> np.ndarray:
        """Gets the signal waveform data."""
        logger.debug("PlaybackData.get_signal_data: shape = %s", str(self._signal_data.shape))
        return self._signal_data
