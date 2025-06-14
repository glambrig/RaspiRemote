#pragma once

#include <iostream>
#include <ctime>
#include <lirc/lirc_client.h>
#include "../inc/LibUinputWrapper/libUinputWrapper.h"

#define MOUSE_X_MOVE_OFFSET 30
#define MOUSE_Y_MOVE_OFFSET 20

class Keypress
{
private:
	int		uinput_fd;
	bool	arrowKeyMovesMouse = true;
public:
	void	listenForKeyPress(struct lirc_config **lirc_config);
	void	decodeKeyPress(char *receivedCodeStr);
	int		discernCorrectKey(u_int16_t key);
	void	checkForNumberKeyAndPress(std::string &receivedCodeStr);
	bool	checkForArrowKeyAndPress(std::string &receivedCode);

	void	setUinputFd(int &uinp_fd)
	{
		uinput_fd = uinp_fd;
	}
};