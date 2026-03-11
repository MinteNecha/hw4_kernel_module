#!/bin/bash

make
sudo insmod hw4.ko
sudo dmesg | tail -2

sleep 1

MAJOR=$(dmesg | grep "Welcome Major number: " | tail -n 1 | awk '{print $NF}')
sudo mknod /dev/hw4 c $MAJOR 0
sudo chmod 666 /dev/hw4

sleep 1

echo "Writting to device and reading from device" > /dev/hw4

sleep 1

head -n 1 /dev/hw4

sleep 1

sudo rm /dev/hw4
sudo rmmod hw4
make clean
