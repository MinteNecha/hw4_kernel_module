#!/bin/bash
echo "----------------------------Making and input module-------------------------"
sleep 1
make
sudo insmod hw4.ko
sudo dmesg | tail -2

sleep 2

echo "------------------Creating node to be able to read and write to device------------------------------------"
MAJOR=$(dmesg | grep "Welcome Major number: " | tail -n 1 | awk '{print $NF}')
sudo mknod /dev/hw4 c $MAJOR 0
sudo chmod 666 /dev/hw4

sleep 2

echo "----------------Lets write to device-----------------------------"
echo "Message to device" > /dev/hw4

sleep 2

head -n 1 /dev/hw4

sleep 2

echo "-------------------Time to remove everything----------------------"
sudo rm /dev/hw4
sudo rmmod hw4
make clean
