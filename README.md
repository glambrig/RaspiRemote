I like watching movies and youtube on my laptop, since I have an adblocker. The screen is kind of small though, so I usually watch the stuff from my laptop on my TV via HDMI. The problem with this approach is that whenever I want to pause or search something, I have to get up off the couch (the HDMI cable is too short). This problem could arguably be solved by just getting a longer cable, but that would be too easy. So I thought: what if I could use a remote control, which could move the mouse, click, and type? That's what this project is.

This program provides a GUI which makes selecting services easy. Simply use the remote to choose the service you want, click, and it'll take you there. Once on the page (let's say you're on youtube), use the up/down/left/right arrows to navigate the videos, and the center button to click. If you click the search bar, you'll need to use the number keys, as described below.

To make this work, you'll need:
- A raspberry pi
- IR remote + receiver (included in Elegoo's Arduino UNO R3 starter kit)

Since a little remote control is pretty limited, I had to make some choices.
The first is that in order to type something, you'd have to use the 1-9 keys on the remote just like on those old flip phones, where 1 would be A/B/C depending on how many times you press the key.
The second (and most annoying) is that the descriptions of the keys on the remote control don't match with what I've bound those keys to do. At least, this is the case for the one that I'm using (the one that comes with the arduino starter kit), maybe yours is nicer.

### How to prepare the hardware
1. Plug the IR receiver directly into the raspberry pi using the I2C port
2. Connect the raspberry pi to your TV via HDMI (optional, though you'll need a screen in any case)

### How to build the project:
- Clone the project (`git clone ...`)
- Run `build.sh` (if you want to be able to run this program from anywhere, use `./build.sh -bin`)
- Launch the program with `./raspiremote`

***IMPORTANT***:
If you're using the Elegoo remote included in the arduino kit, run this (`sudo cp lircd.conf /etc/lirc/lircd.conf`) to copy the LIRC configuration file that I made. Otherwise, you'll have to use LIRC's `irrecord` tool to make a configuration file for your remote.
If you want to use your own remote and raspiremote doesn't do anything when you press buttons, MAKE SURE that you REMOVE the 0xFFFFFF (or 0x000000) from your lircd.conf file as one of the answers on this page says (https://raspberrypi.stackexchange.com/questions/37579/lirc-no-output-from-irw).
This had me stumped for days, so you're wlecome.

### How to change the websites the GUI redirects to
This is a bit trickier than one might think. Since we're using the left/right/up/down keys to navigate, the correct distance for the cursor to jump depends on how far apart the videos (or things to be clicked) are on the website you visit, how many there are per row, and some other things. I've included a configuration file (`config.json`) which you may edit to reflect the appropriate distances for the website that you want to add.

For example:
Let's say that you want to visit example.com, which has a homepage with 6 videos per row, ....
