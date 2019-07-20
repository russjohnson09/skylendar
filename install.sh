#!/usr/bin/env bash

cd ~
git clone https://github.com/russjohnson09/skylendar.git

cd skylendar

sudo apt-get update

sudo apt-get install qtbase5-dev libqt5svg5-dev \
qttools5-dev \
qtdeclarative5-dev \
qttools5-dev \
qttools5-dev-tools \
qtdeclarative5-dev \
postgresql postgresql-contrib \
libqt5sql5-psql

cd skylendar/skylendar-4.1nn

sudo -DCMAKE_BUILD_Type=Release cmake

sudo make
sudo make install


#echo "/usr/local/lib64" > /etc/ld.so.conf.d/local.conf
echo "/usr/local/lib64" | sudo tee -a /etc/ld.so.conf.d/skylendar.conf
sudo ldconfig


echo "*******************************"
echo "*******************************"
echo "*******************************"
echo "*******************************"
echo "*******************************"

echo "Run install"
echo "Set root to true and press okay"

sleep 1
echo "3"
sleep 1

echo "2"
sleep 1

echo "1"
sleep 1


sudo skyadmin


echo "sudo skylander"
echo "Run this command whenever running this again after install is a success."

sleep 1
echo "3"
sleep 1

echo "2"
sleep 1

echo "1"
sleep 1


sudo skylendar
