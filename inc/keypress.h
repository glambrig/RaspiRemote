#pragma once

#include <iostream>
#include <ctime>
#include <lirc/lirc_client.h>
#include "../inc/libft/libft.h"
#include "../inc/uinputWrapperLib/uinputWrapperLib.h"

class gui;

class Keypress
{
private:
	gui		*guiPtr;
	int		uinput_fd;
public:
	void	listenForKeyPress(struct lirc_config **lirc_config);
	void	decodeKeyPress(char *receivedCodeStr);
	void	checkForNumberKey(char *receivedCode);
	bool	checkForArrowKey(char *receivedCode);

	void	setGuiPtr(class gui *gui)
	{
		guiPtr = gui;
	}
	void	setUinputFd(int &uinp_fd)
	{
		uinput_fd = uinp_fd;
	}
};