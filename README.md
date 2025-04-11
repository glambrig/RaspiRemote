I like watching movies and youtube on my laptop, since I have an adblocker. The screen is kind of small though, so I usually watch the stuff from my laptop on my TV via HDMI. The problem with this approach is that whenever I want to pause or search something, I have to get up off the couch (the HDMI cable is too short). This problem could arguably be solved by just getting a longer cable, but that would be too easy. So I thought: what if I could use a remote control, which could move the mouse, click, and type? That's what this project is.

This program provides a GUI which makes selecting services easy. Simply use the remote to choose the service you want, click, and it'll take you there. Once on the page (let's say you're on youtube), use the up/down/left/right arrows to navigate the videos, and the center button to click. If you click the search bar, you'll need to use the number keys, as described below.

To make this work, you'll need:
- A raspberry pi
- IR remote + receiver (included in Elegoo's Arduino UNO R3 starter kit)

Since a little remote control is pretty limited, I had to make some choices.
The first is that in order to type something, you'd have to use the 1-9 keys on the remote just like on those old flip phones, where 1 would be A/B/C depending on how many times you press the key.
The second (and most annoying) is that the descriptions of the keys on the remote control don't match with what I've bound those keys to do. At least, this is the case for the one that I'm using (the one that comes with the arduino starter kit), maybe yours is nicer.

### How to prepare the hardware

You'll need three female-to-female dupont cables, or twice as many male-to-female cables and a bread board. If you're confused about which pin is which, please refer to https://pinout.xyz/pinout/wiringpi .

1. Connect the IR receiver's output to GPIO pin 17 of the Pi
2. Connect the 3.3V and GND of the IR receiver to those same pins on the Pi
3. Connect the raspberry pi to your TV via HDMI

### Before building the project...
If you're NOT using the Elegoo remote included in the arduino kit, you'll have to use LIRC's `irrecord` tool to make a configuration file for your remote, and you'll have to make a lircrc file from it (read the docs or ask chatgpt).
If you want to use your own remote and raspiremote doesn't do anything when you press buttons, MAKE SURE that you REMOVE the 0xFFFFFF (or 0x000000) from your lircd.conf file as one of the answers on this page says (https://raspberrypi.stackexchange.com/questions/37579/lirc-no-output-from-irw).
This had me stumped for days, so you're welcome.

### How to build the project:
- Clone the project (`git clone ...`)
- Run `build.sh`
- Run the build script with the appropriate options:

`-nocopy`: if you're not using an Elegoo remote, this options ensures that my configuration files won't be copies to /etc/lirc. This means that you have to do all the work as mentioned above.

`-bin`: adds raspiremote directory to $PATH, so you can run this program from anywhere

`-nopi`: if you're not running `raspiremote` on a raspberry pi (if you don't include this option, wiringpi won't work)

- Launch the program with `./raspiremote`

### How to change the websites the GUI redirects to
To do
