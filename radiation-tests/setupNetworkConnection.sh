#!/bin/sh

# Probably will need to run as root (rather than just sudo).
# This is for the last command.
# Usage: ./setupNetworkConnection ARIETTA_DEVICE ETHERNET_DEVICE
# Both these values can be found by checking with ifconfig

# Change these values to reflect your devices.
# usb_device: find this by pluggin in the arietta, and running the command "ifconfig".
# You will find either a device very similar to the one named here, or one named 'usb0'
usb_device="enp0s29u1u2"
# This is the device that you are using to connect to the internet. The format will
# probably be similar to the device below if wifi. 
network_device="wlp4s0"
# This is the desired IP address for the host device (ie your computer), not the arietta
host_address="10.0.0.2"
arietta_address="10.0.0.1"

# This section of code just checks for your parameters and sets them accordingly
if [ $# -eq 4 ]
	then 
		usb_device = $1
		network_device = $2
		ip_address = $3
		arietta_address = $4
elif [ $# -eq 0 ]
	then
		echo "Using usb device $usb_device, network device $network_device, host address $host_address, arietta address $arietta_address"
elif [ $# -lt 4 ]
	then
		if [ $1 = 'help' ]
			then
				echo "Run this script after pluggin in your Arietta."
				echo "Usage: setupNetworkConnection [usb_device netwok_device]"
				echo "usb_device: this is the usb network connection. You can find this by checking the command"
				echo "    ifconfig. The device should be similar to enp0s29u1u2 or usb0"
				echo "network_device: this is the device that you are connecting to the internet with. It can"
				echo "    also be found checking ifconfig, it will have an IP address associated."
				exit 1
		else
			echo "Not enough arguments supplied."
			echo "Usage: setupNetworkConnection [usb_device netwok_device ip_address arietta_address]"
			exit 1
		fi
elif [ $# -gt 4 ]
	then
		echo "Too many arguments supplied."
		echo "Usage: setupNetworkConnection [usb_device netwok_device ip_address arietta_address]"
		exit 1
fi

# Brings up the usb device. 
ip link set $usb_device up

sleep 2s

# Adds an ip address to the usb device
ip addr add $host_address/24 dev $usb_device

sleep 2s

# Set iptabls to allow port forwarding from the arietta to the host network device
# Masquerade as if it is using the same network
iptables -t nat -A POSTROUTING -s $arietta_address/32 -o $network_device -j MASQUERADE

sleep 2s

# Allow ip forwarding
echo 1 > /proc/sys/net/ipv4/ip_forward
