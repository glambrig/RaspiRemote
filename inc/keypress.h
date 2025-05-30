#pragma once

#include <iostream>
#include <ctime>
#include <lirc/lirc_client.h>
#include "../inc/LibUinputWrapper/libUinputWrapper.h"

#define MOUSE_X_MOVE_OFFSET 15
#define MOUSE_Y_MOVE_OFFSET 10

class gui;

class Keypress
{
private:
	gui		*guiPtr;
	int		uinput_fd;
public:
	void	listenForKeyPress(struct lirc_config **lirc_config);
	void	decodeKeyPress(char *receivedCodeStr);
	int		discernCorrectKey(u_int16_t key);
	void	checkForNumberKey(std::string &receivedCodeStr);
	bool	checkForArrowKey(std::string &receivedCode);

	void	setGuiPtr(class gui *gui)
	{
		guiPtr = gui;
	}
	void	setUinputFd(int &uinp_fd)
	{
		uinput_fd = uinp_fd;
	}
};