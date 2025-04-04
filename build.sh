# #!/bin/sh

# sudo apt update -y

# while IFS= read -r line; do
# 	if echo "$line" | grep "false"; then
# 		sudo apt install 
# done < hasDependencies

# sudo apt install xauth -y || exit 1
# sudo apt install xorg -y || exit 1
# sudo apt install openbox -y || exit 1

# if [ ! -d "Arduino-IRremote"]; then
# 	git clone git@github.com:Arduino-IRremote/Arduino-IRremote.git || exit 1
# fi

#!/bin/sh

sudo apt update -y
sudo apt install libx11-dev -y || exit 1
sudo apt install xauth -y || exit 1
sudo apt install xorg -y || exit 1
sudo apt install openbox -y || exit 1

if [ ! -d "Arduino-IRremote" ]; then
	git clone git@github.com:Arduino-IRremote/Arduino-IRremote.git || exit 1
else
	echo "IRremote library already installed, skipping..."
fi

# If -bin option provided, make program executable from anywhere
if [ "$1" == "-bin" ]; then
	export PATH=$PATH:~/RaspiRemote/
fi

make -j4 || exit 1