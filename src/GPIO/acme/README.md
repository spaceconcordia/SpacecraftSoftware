# Acmepins

A Python library for controlling the GPIO pins on
the following Acme Systems Linux boards:

* [Roadrunner](http://www.acmesystems.it/roadrunner)
* [Acqua A5](http://www.acmesystems.it/acqua)
* [Aria G25](http://www.acmesystems.it/aria)
* [Arietta G25](http://www.acmesystems.it/arietta)
* [FOX Board G20](http://www.acmesystems.it/FOXG20) 

## Installation

```
# git clone git://github.com/AcmeSystems/acmepins.git
# cd acmepins
~/acmepins# python setup.py install
```

## Pin test

```
$ python blink.py PA0

```
		

## Python Code examples

### Blinking led

```
from acmepins import GPIO
from time import sleep

#Roadrunner example
led = GPIO('PA0','OUTPUT') 

#FOX Board G20 example
#led = GPIO('J7.3','OUTPUT') 

#Aria G25 example
#led = GPIO('W9','OUTPUT') 

#Arietta G25 example
#led = GPIO('J4.29','OUTPUT') 

#Acqua A5 example
#led = GPIO('J3.32','OUTPUT') 

while True:
    led.on()
    sleep(1)
    led.off()
    sleep(1)
```

### Button read in polling mode

```
from acmepins import GPIO
from time import sleep

#FOX Board G20 example
Button=GPIO('J7.5','INPUT')

#Aria G25 example
#Button=GPIO('W15','INPUT')

#Arietta G25 example (on board push button)
#Button=GPIO('PC17','INPUT')

#Acqua A5 example
#Button=GPIO('J3.33','INPUT')

i=0
while True:
    sleep(1)
    i+=1
    print i
    if Button.digitalRead()==0:
        print "Pressed"
        while Button.digitalRead()==0:
            pass   
```

### Button read in event mode
```
from acmepins import GPIO
from time import sleep

def event_handler():
    print "Input changed"

#FOX Board G20 example
Button=GPIO('J7.5','INPUT')

#Aria G25 example
#Button=GPIO('W15','INPUT')

#Arietta G25 example (on board push button)
#Button=GPIO('PC17','INPUT')

#Acqua A5 example
#Button=GPIO('J3.33','INPUT')

Button.set_edge("both",event_handler)

i=0
while True:
    print i
    i=i+1
    sleep(0.5)
```

### Blinking the on-board red led
```
from acmepins import ARIETTA_LED
from time import sleep

arietta_led=ARIETTA_LED("none")

for i in range(5):
	arietta_led.on()
	sleep(0.1)
	arietta_led.off()
	sleep(0.1)
	arietta_led.on()
	sleep(0.1)
	arietta_led.off()
	sleep(0.1)

	arietta_led.on()
	sleep(2)
	arietta_led.off()
	sleep(0.5)
    
arietta_led.mode("heartbeat")
    
```

## Links

* http://www.acmesystems.it/gpio

