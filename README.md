I like watching movies and youtube on my laptop, since I have an adblocker. The screen is kind of small though, so I usually watch the stuff from my laptop on my TV via HDMI. The problem with this approach is that whenever I want to pause or search something, I have to get up off the couch (the HDMI cable is too short). This problem could arguably be solved by just getting a longer cable, but that would be too easy. So I thought: what if I could use a remote control, which could move the mouse, click, and type? That's what this project is.

This program provides a GUI which makes selecting services easy. Simply use the remote to choose the service you want, click, and it'll take you there. Once on the page (let's say you're on youtube), use the up/down/left/right arrows to navigate the videos, and the center button to click. If you click the search bar, you'll need to use the number keys, as described below.

To make this work, you'll need:
- A raspberry pi
- IR remote + receiver (included in the Arduino UNO R3 starter kit)
- TV (optional)
- HDMI cable (optional)

Since a little remote control is pretty limited, I had to make some choices.
The first is that in order to type something, you'd have to use the 1-9 keys on the remote just like on those old flip phones, where 1 would be A/B/C depending on how many times you press the key.
The second (and most annoying) is that the descriptions of the keys on the remote control don't match with what I've bound those keys to do. At least, this is the case for the one that I'm using (the one that comes with the arduino starter kit), maybe yours is nicer.

### How to prepare the hardware

You'll need three female-to-female dupont cables, or twice as many male-to-female cables and a bread board. If you're confused about which pin is which, please refer to https://pinout.xyz/pinout/wiringpi .

1. Connect the IR receiver's output to GPIO pin 17 of the Pi
2. Connect the 3.3V and GND of the IR receiver to those same pins on the Pi
3. Connect the raspberry pi to your TV via HDMI

### How to build the project:
- Clone the project (`git clone ...`)
- Run `build.sh` (if you want to be able to run this program from anywhere, use `./build.sh -bin`)
- Launch the program with `./raspiremote`

### How to change the websites the GUI redirects to
This is a bit trickier than one might think. Since we're using the left/right/up/down keys to navigate, the correct distance for the cursor to jump depends on how far apart the videos (or things to be clicked) are on the website you visit, how many there are per row, and some other things. I've included a configuration file (`config.json`) which you may edit to reflect the appropriate distances for the website that you want to add.

For example:
Let's say that you want to visit example.com, which has a homepage with 6 videos per row, ....
