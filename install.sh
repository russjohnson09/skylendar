#!/usr/bin/env bash

sudo mkdir /skylander


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






