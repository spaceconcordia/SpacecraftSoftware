import os
import sys
import time

filename = '/root/csdc4/src/GPIO/acme/acmepins.py'

directory, module_name = os.path.split(filename)
module_name = os.path.splitext(module_name)[0]
path = list(sys.path)
sys.path.insert(0, directory)  # '/root/csdc4/src/GPIO/acme'

try:
    from acmepins import GPIO
    led = GPIO('J4.24', 'OUTPUT')
    led.on()
    time.sleep(2)
    led.off()
finally:
    sys.path[:] = path  # restore
