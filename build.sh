#!/bin/sh

sudo apt update -y
sudo apt install libx11-dev -y || exit 1
sudo apt install xauth -y || exit 1
sudo apt install xorg -y || exit 1
sudo apt install openbox -y || exit 1
sudo apt install lirc -y || exit 1

if [ ! -d "inc/WiringPi" ]; then
	git clone git@github.com:WiringPi/WiringPi.git
	cd WiringPi
	./build debian
	mv debian-template/wiringpi_3.14_amd64.deb .
	sudo chmod 644 wiringpi_3.14_amd64.deb
	sudo apt install ./wiringpi_3.14_amd64.deb
	cd ..
	mv WiringPi inc
else
	echo "WiringPi already installed, skipping..."
fi

# If -bin option provided, make program executable from anywhere
cwd=$(pwd)
if [ "$1" = "-bin" ]; then
	export PATH=$PATH:$cwd
fi

make -j4 || exit 1