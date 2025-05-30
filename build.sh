#!/bin/sh

if [ "$1" != "-noapt" ] || [ "$2" != "-noapt" ] || [ "$3" != "-noapt" ]; then
	sudo apt update -y || exit 1
	sudo apt install lirc liblirc-dev -y || exit 1
	clear
fi

if [ ! -d "inc/LibUinputWrapper" ]; then
	echo "LibUinputWrapper not found, installing..."
	git clone git@github.com:glambrig/LibUinputWrapper.git
	mv LibUinputWrapper inc
	make -C inc/LibUinputWrapper
fi

if [ "$1" = "-nopi" ] || [ "$2" = "-nopi" ] || [ "$3" = "-nopi" ]; then
	if [ ! -d "inc/WiringPi" ] && ! gpio -v >/dev/null 2>&1; then
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
else
	if [ ! -d "inc/WiringPi" ] && ! command -v gpio &> /dev/null ; then
		echo "WiringPi not found, installing..."
		git clone git@github.com:WiringPi/WiringPi.git || exit 1
		cd WiringPi
		./build debian || exit 1
		mv debian-template/wiringpi_3.14_arm64.deb .
		sudo chmod 644 wiringpi_3.14_arm64.deb
		sudo apt install ./wiringpi_3.14_arm64.deb
		cd ..
		mv WiringPi inc
	else
		echo "WiringPi already installed, skipping..."
	fi
fi

echo "WiringPi installed successfully."

if [ "$1" != "-nocopy" ] && [ "$2" != "-nocopy" ] && [ "$3" != "-nocopy" ]; then
	sudo cp conf/lircd.conf /etc/lirc/lircd.conf
	sudo cp conf/lircrc /etc/lirc/lircrc
	sudo cp conf/lirc_options.conf /etc/lirc/lirc_options.conf
	# rm lircd.conf lircrc lirc_options.conf
fi

echo "Changing permissions for /dev/uinput ..."

sudo modprobe uinput
sudo chmod 777 /dev/uinput

# If -bin option provided, make program executable from anywhere
# cwd=$(pwd)
# if [ "$1" = "-bin" ] || [ "$2" = "-bin" ] || [ "$3" = "-bin" ]; then
# 	export PATH=$PATH:$cwd
# fi

make -j4 || exit 1