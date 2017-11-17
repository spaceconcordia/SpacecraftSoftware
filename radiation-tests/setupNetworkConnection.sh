#!/bin/sh

# Probably will need to run as root (rather than just sudo).
# This is for the last command.
# Usage: ./setupNetworkConnection ARIETTA_DEVICE ETHERNET_DEVICE
# Both these values can be found by checking with ifconfig

ip link set $1 up

sleep 2s

ip addr add 10.0.0.2/24 dev $1

sleep 2s

iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o $2 -j MASQUERADE

sleep 2s

echo 1 > /proc/sys/net/ipv4/ip_forward
