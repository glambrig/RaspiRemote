#!/bin/sh

sudo apt update -y
sudo apt install libx11-dev -y || exit 1
sudo apt install xauth -y || exit 1
sudo apt install xorg -y || exit 1
sudo apt install openbox -y || exit 1
sudo apt install lirc liblircclient-dev -y || exit 1

if [ "$1" = "-nopi" ] || [ "$2" = "-nopi" ] || [ "$3" = "-nopi" ]; then
	if [ ! -d "inc/WiringPi" ] && [ "$(gpio -v)" = 127 ]; then
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

	if [ "$1" = "-copy" ] || [ "$2" = "-copy" ] || [ "$3" = "-copy" ]; then
		sudo cp lircd.conf /etc/lirc/lircd.conf
		sudo cp lircrc /etc/lirc/lircrc
		sudo cp lirc_options.conf /etc/lirc/lirc_options.conf
	fi

else
	if [ ! -d "inc/WiringPi" ] && [ "$(gpio -v)" = 127 ]; then
	git clone git@github.com:WiringPi/WiringPi.git
	cd WiringPi
	./build debian
	mv debian-template/wiringpi_3.14_arm64.deb .
	sudo chmod 644 wiringpi_3.14_arm64.deb
	sudo apt install ./wiringpi_3.14_arm64.deb
	cd ..
	mv WiringPi inc
	else
		echo "WiringPi already installed, skipping..."
	fi

	if [ "$1" != "-nocopy" ] && [ "$2" != "-nocopy" ] && [ "$3" != "-nocopy" ]; then
		sudo cp lircd.conf /etc/lirc/lircd.conf
		sudo cp lircrc /etc/lirc/lircrc
		sudo cp lirc_options.conf /etc/lirc/lirc_options.conf
		rm lircd.conf lircrc lirc_options.conf
	fi
fi

# If -bin option provided, make program executable from anywhere
# cwd=$(pwd)
# if [ "$1" = "-bin" ] || [ "$2" = "-bin" ] || [ "$3" = "-bin" ]; then
# 	export PATH=$PATH:$cwd
# fi

make -j4 || exit 1