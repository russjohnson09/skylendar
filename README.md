#Dependencies
sudo apt-get update

sudo apt-get install git cmake build-essential


##Qt5
sudo apt-get update
sudo apt-get install qtbase5-dev libqt5svg5-dev
sudo apt-get install qtdeclarative5-dev

sudo apt-get install qttools5-dev
sudo apt-get install qttools5-dev-tools


ls /usr/lib/x86_64-linux-gnu/cmake/Qt5

##Qt5Svg


###Not Required?
sudo apt-get install qtdeclarative5-dev


# skylendar


mkdir /skylendar/builds/ubuntu -p
cd /skylendar/builds/ubuntu

sudo mkdir /build_skylendar/ubuntu -p
sudo chown -R vagrant:vagrant /build_skylendar

cd /build_skylendar/ubuntu
sudo cmake /skylendar/skylendar-4.1nn

sudo chown -R vagrant:vagrant /build_skylendar

running mkfontdir /usr/share/fonts/truetype  2>&1


##running mkfontdir /usr/share/fonts/truetype  2>&1


#make


#make install




https://github.com/BYVoid/OpenCC/issues/141

makedir /var/tmp/obj
cd /var/tmp/obj

and run the next command:

sudo -DCMAKE_BUILD_Type=Release cmake /skylendar/skylendar-4.1nn




sudo make /


sudo make install


sudo skydmin


vagrant@skylendar:/build_skylendar/ubuntu$ sudo skydmin
QSqlDatabase: QPSQL driver not loaded
QSqlDatabase: available drivers: QSQLITE


#postgres
sudo apt install postgresql postgresql-contrib


 PostgreSQL driver for Qt5.


sudo apt-get install libqt5sql5-psql

https://www.digitalocean.com/community/tutorials/how-to-install-and-use-postgresql-on-ubuntu-18-04

sudo -u postgres createuser --interactive
sudo -u postgres createdb vagrant


psql


##procedural
https://www.postgresql.org/docs/8.2/xplang-install.html
lpgsql language.

sudo -i -u postgres
psql




sudo ldconfig



http://howtolamp.com/articles/adding-shared-libraries-to-system-library-path/


sudo su
echo "/usr/local/lib64" > /etc/ld.so.conf.d/local.conf
ldconfig
