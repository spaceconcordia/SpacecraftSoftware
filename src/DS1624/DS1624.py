import smbus
import time
import logging
import struct


class TempSensor:
    """

    Class to read out an DS1624 temperature sensor with a given address.

    DS1624 data sheet: http://datasheets.maximintegrated.com/en/ds/DS1624.pdf

    Thomas Heuberger, August 2013

    Usage:

        >>> from TempSensor import TempSensor
        >>> sensor = TempSensor(0x48)
        >>> print "%02.02f" % sensor.get_temperature()
        23.66

    """

    # Some constants
    DS1624_READ_TEMP = 0xAA
    DS1624_START = 0xEE
    DS1624_STOP = 0x22

    def __init__(self, address):
        self.address = address
        self.bus = smbus.SMBus(0)

    def __send_start(self):
        self.bus.write_byte(self.address, self.DS1624_START)

    def __send_stop(self):
        self.bus.write_byte(self.address, self.DS1624_STOP)

    def __read_sensor(self):
        """    
        Reads the raw temperature data from a DS1624 sensor. 

        The raw data output is a 16 bit word. 
        Reading from LEFT to RIGHT, the 1st bit is the MSB and the 13th bit is the LSB, 
        so 13 bits are payload and the last 3 bits are zeros.

        When read, because of the endianness differences between the DS1624 and the RPi
        the byte order is reversed, so the second byte represents the integer part of 
        the temperature and the first byte the fractional part in terms of a 0.03125 multiplier.      
        """
        return self.bus.read_word_data(self.address, self.DS1624_READ_TEMP)

    def __convert_temp(self, raw):
        """
        Converts the raw data to a decimal value.        
        """
        logging.basicConfig(filename='debug.log', level=logging.DEBUG)
        # As the DS1624 is Big-endian and the Pi Little-endian, the byte order is reversed.
        temp_integer = raw & 0x00FF
        temp_fractional = ((raw & 0xFF00) >> 8) >> 3

        a, b = struct.unpack('bb', '{}{}'.format(
            chr(temp_integer), chr(temp_fractional)))
        logging.debug('raw: ' + hex(raw) + ' result: ' +
                      str(a + (0.03125 * b)))
        return a + (0.03125 * b)

    def run_test(self):
        logging.basicConfig(filename='debug.log', level=logging.DEBUG)

        # Examples taken from the data sheet
        values = [0x7D, 0x1019, 0x8000, 0, 0x80FF, 0xF0E6, 0xC9]

        for value in values:
            logging.debug('value: ' + hex(value) + ' result: ' +
                          str(self.__convert_temp(value)))

    def get_temperature(self):
        self.__send_start()
        time.sleep(0.1)
        return self.__convert_temp(self.__read_sensor())

    def read_temperature(self):
        return self.get_temperature()
