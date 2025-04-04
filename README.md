## Remote control functionality with raspberry pi.

I like watching movies and youtube on my laptop, since I have an adblocker. The screen is kind of small though, so I ususally watch the stuff from my laptop on my TV via HDMI. The problem with this approach is that whenever I want to pause or search something, I have to get up off the couch (the HDMI cable is too short). This problem could arguably be solved by just getting a longer cable, but that would be too easy. So I thought: what if I could use a remote control, which could move the mouse, click, and type? That's what this project is.

To make this work, you'll need:
- A raspberry pi
- IR remote + receiver

Here's the wiring diagram.
[diagram goes here]

Since a little remote control is pretty limited, I had to make some choices.
The first is to use a GUI which will make selecting services easy. This is basically just a simple HTML page, where the different pages you want to visit (youtube, cartoons, etc.) will be displayed.
The second is that in order to type something, you'd have to use the 1-9 keys on the remote just like on those old flip phones, where 1 would be A/B/C depending on how many times you press the key.

### Steps to build the project
- Clone the project
- Use `make`
- ....
