#!/bin/bash
# This is the startup script for MavProxy to forward serial radio to
# dell lattitude rugged and dell lattitude extreme
#
# assumed configuration
#
# serial radio: /dev/ttyUSB0
# Ziyang's laptop: 192.168.0.100
# lattiude rugged: 192.168.0.101:14550
# lattitude extreme: 192:168.0.102:14550
#
# The above is configured in TPLINK battery operated router
# If other networking device is used, please set ip as appropriate
#
# User needs to be dialout user group in Linux. Else, connecting to /dev/ttyUSB0# will fail
#
# Other software prerequisite
# mavproxy is installed using pip and registered to system path

#create new folder according to timestamp
now=$(date +%Y-%m-%d:%H:%M:%S)
mkdir "$now"

#change current directory
cd $now

#start mavproxy
mavproxy.py --master=/dev/ttyUSB0 --baudrate=57600 --out=udp:127.0.0.1:14550 --out=udpout:192.168.0.101:14550 --out=udpout:192.168.0.102:14550
