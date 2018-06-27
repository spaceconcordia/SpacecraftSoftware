#/root/csdc4/src/Scheduler/deploy.py

from __future__ import print_function
import sys
sys.path.insert(0, '/root/csdc4/src/GPIO/acme')
from acmepins import GPIO

deployment_a = GPIO('J4.8', 'OUTPUT')
deployment_b = GPIO('J4.10', 'OUTPUT')

time.sleep(60)

deployment_a.on()
deployment_b.on()
print("Deploying...")

time.sleep(5)

deployment_a.off()
deployment_b.off()

