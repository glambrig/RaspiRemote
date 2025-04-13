#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/input.h>
#include <linux/uinput.h>
#include <lirc/lirc_client.h>
#include "../inc/libft/libft.h"

#define MOUSE_EVENT 0
#define KEY_EVENT 1

class gui;

typedef class Keypress
{
private:
		gui	*guiPtr;
public:
	void	setupUinputDevice();
	void	listenForKeyPress(struct lirc_config **lirc_config);
	void	decodeKeyPress(char *receivedCodeStr);
	void	sendEventWrapper(unsigned int code, int value, int eventType);
	void	cleanupUinputDevice();

	void	setGuiPtr(gui *gui)
	{
		guiPtr = gui;
	}
}	Keypress;