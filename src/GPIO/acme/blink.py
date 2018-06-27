from acmepins import GPIO
from time import sleep
import sys

print "This is the name of the script: ", sys.argv[0]
print "Number of arguments: ", len(sys.argv)
print "The arguments are: " , str(sys.argv)

#Roadrunner example
led = GPIO(sys.argv[1],'OUTPUT') 

#led = GPIO('J4.24','OUTPUT')

while True:
    led.on()
    sleep(1)
    led.off()
    sleep(1)
