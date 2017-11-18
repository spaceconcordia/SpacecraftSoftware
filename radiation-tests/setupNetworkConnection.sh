#!/bin/sh

# Probably will need to run as root (rather than just sudo).
# This is for the last command.
# Usage: ./setupNetworkConnection ARIETTA_DEVICE ETHERNET_DEVICE
# Both these values can be found by checking with ifconfig

usb_device="enp0s29u1u2"
network_device="wlp4s0"

if [ $# -eq 2 ]
	then 
		usb_device = $1
		network_device = $2
elif [ $# -eq 1 ]
	then
		echo "Not enough arguments supplied."
		echo "Usage: setupNetworkConnection [usb_device netwok_device]"
		exit 1
else
		echo "No arguments supplied."
		echo "Using $usb_device $network_device"
fi

ip link set $usb_device up

sleep 2s

ip addr add 10.0.0.2/24 dev $usb_device

sleep 2s

iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o $network_device -j MASQUERADE

sleep 2s

echo 1 > /proc/sys/net/ipv4/ip_forward
