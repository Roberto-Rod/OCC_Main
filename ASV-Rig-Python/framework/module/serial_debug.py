#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2021-2022, LeoTel Software Systems Limited <james.bridson@leotel-software.co.uk>
# All rights reserved.
#

"""Pachymeter Automated Software Verification Rig Serial Debug Module Implementation."""

import logging
from queue import Queue
import random
import sys
from threading import Lock, Thread
import time

import serial
from serial.tools import list_ports

from framework.util.config import Config


config = Config().get_logging_config()
logger = logging.getLogger(__name__)
if __name__ in config.levels:
    logger.setLevel(config.levels[__name__])


__all__ = [
    'SerialDebugLogger',
    'SerialDebug'
]


class SerialDebugLogger:
    """This class implements a serial debug logger.

       Ultimately we might want the framework to be able to interact with the
       debug in some way e.g. waiting for a certain input but for now simply
       logging the debug output is sufficient.
    """

    def __init__(self, device: str, baudrate: int, fname: str, mode: str, bufsize: int, timeout: float, queue: Queue):
        """Initialise an instance of SerialDebugLogger.

           :param device: The device name of the local serial port.
           This is typically COMX on Windows and /dev/ttyXX on Linux.
           :param baudrate: The baudrate of the serial port.
           :param fname: The file name of the log file to be written.
           :param mode: The file mode to use, usually 'w' to truncate or 'a' to append.
           :param bufsize: The size of the read buffer on the serial port.
           :param timeout: The read timeout of the serial port.
           :param queue: A queue for communication with the thread.
        """
        logger.debug("SerialDebugLogger.__init__: device = '%s', baudrate = %d, fname = '%s', mode = '%s', bufsize = %d, "
                     "timeout = %.1f", device, baudrate, fname, mode, bufsize, timeout)
        self._fname = fname
        self._mode = mode
        self._queue = queue
        self._uart = serial.Serial()
        self._uart.port = device
        self._uart.baudrate = baudrate
        self._uart.timeout = timeout
        self._buffer = bytearray(bufsize)

    def open(self):
        """Open the serial port."""
        logger.debug('SerialDebugLogger.open')
        self._uart.rts = False
        self._uart.open()

    def close(self):
        """Close the serial port."""
        logger.debug('SerialDebugLogger.close()')
        self._uart.close()

    def main(self):
        """Reads data from the serial port and writes it to the log file.

           Most of the time this is blocked on I/O.
        """
        logger.debug('SerialDebugLogger.main()')
        self.open()
        with open(self._fname, self._mode, encoding='iso-8859-1') as f_out:
            time.sleep(self._uart.timeout * random.random())
        while True:
            bytes_read = self._uart.readinto(self._buffer)
            if bytes_read > 0:
                logger.debug("SerialDebugLogger.main: bytes_read = %d", bytes_read)
                with open(self._fname, 'a', encoding='iso-8859-1') as f_out:
                    f_out.write(self._buffer[:bytes_read].decode(encoding='iso-8859-1'))
            #else:
            #    logger.debug('SerialDebugLogger.main: idle')
            if not self._queue.empty():
                logger.debug('SerialDebugLogger.main: close requested')
                self.close()
                return


class SerialDebug:
    """This class instantiates the individual SerialDebugLogger instances and
       associated threads and provides method to start and stop the threads.
    """

    # Local data
    _config = None
    _mutex = None
    _queue = None
    _loggers = None
    _threads = None

    def __init__(self):
        logger.info('SerialDebug.__init__')
        self._is_alive = False
        self._config = Config().get_serial_debug_config()
        self._mutex = Lock()
        self._queue = Queue()
        self._loggers = []
        self._threads = []
        self._devices = []
        self._fnames = []
        devices = [port.device for port in list_ports.comports()]
        for port in self._config.ports:
            _device = self._config.ports[port]
            _fname = self._config.path + f"\\dbg_{port}.txt"
            if _device in devices:
                self._loggers.append(SerialDebugLogger(_device, self._config.baudrate, _fname, self._config.mode,
                                                        self._config.bufsize, self._config.timeout, self._queue))
                self._devices.append(_device)
                self._fnames.append(_fname)
            else:
                logger.fatal("SerialDebug.__init__: Debug '%s', COM port '%s' cannot be found.", port, _device)
                sys.exit(1)

    def __enter__(self):
        logger.debug('SerialDebug.__enter__')
        self._mutex.acquire()
        self._start()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.debug('SerialDebug.__exit__')
        self._stop()
        self._mutex.release()

    def _start(self) -> None:
        """Start all the debug logger threads."""
        logger.debug('SerialDebug._start')
        if self._is_alive is False:
            for serial_logger in self._loggers:
                self._threads.append(Thread(target=serial_logger.main))
            for thread in self._threads:
                thread.start()
            self._is_alive = True
        else:
            logger.error('SerialDebug.start: already running')

    def _stop(self) -> None:
        """Stop all the debug logger threads by posting to the queue."""
        logger.debug('SerialDebug._stop')
        if self._is_alive:
            self._queue.put(False)
            for thread in self._threads:
                thread.join()
            self._threads.clear()
            self._queue.empty()
            self._is_alive = False
        else:
            logger.error('SerialDebug.stop: not running')

    def reset(self) -> None:
        """Reset the SerialDebug object to its default state."""
        logger.debug('SerialDebug.reset()')
