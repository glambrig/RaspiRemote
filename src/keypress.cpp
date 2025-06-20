#include "../inc/keypress.h"
#include "../inc/main.h"

void	Keypress::listenForKeyPress(struct lirc_config **lirc_config)
{
	char	*code = NULL;
	char	*receivedCode = NULL;

	while (lirc_nextcode(&code) == 0)
	{
		if (code == NULL)
			continue ;
		do
		{
			if (lirc_code2char(*lirc_config, code, &receivedCode) < 0)
			{
				free(code);
				cleanExit("lirc_code2char", EXIT_FAILURE);
			}
			if (receivedCode == NULL)
			{
				break ;
			}
			decodeKeyPress(receivedCode);
		} while (receivedCode != NULL);
		
		free(code);
		code = NULL;
	}
}

int	Keypress::discernCorrectKey(u_int16_t key)
{
	static int32_t			lastKey = -1;
	static int32_t			beforeLastKey = -1;
	static int32_t			beforeBeforeLastKey = -1;
	static struct timeval	currentTime;
	static time_t			lastKeyTime_sec = -1;
	static time_t			lastKeyTime_usec = -1;
	time_t					difference;

	gettimeofday(&currentTime, NULL);

	difference = currentTime.tv_sec - lastKeyTime_sec;
	difference += (currentTime.tv_usec - lastKeyTime_usec) / 1000000.0;
	if (difference >= 1.0)
	{
		lastKey = -1;
		beforeLastKey = -1;
		beforeBeforeLastKey = -1;
	}
	if (lastKey != key ||
			lastKeyTime_sec == -1 ||
				lastKeyTime_usec == -1)
	{
		lastKey = key;
		lastKeyTime_sec = currentTime.tv_sec;
		lastKeyTime_usec = currentTime.tv_usec;
		return (key);
	}

	if (key == lastKey &&
				(beforeLastKey == -1 ||
				key != beforeLastKey))
	{
		beforeLastKey = lastKey;
		lastKey = key;
		lastKeyTime_sec = currentTime.tv_sec;
		lastKeyTime_usec = currentTime.tv_usec;
		libUinputWrapper::press_key(uinput_fd, KEY_BACKSPACE, 0);
		switch (key)
		{
			case (KEY_0):
				return (KEY_SPACE);
			case (KEY_1):
				return (KEY_A);
			case (KEY_2):
				return (KEY_D);
			case (KEY_3):
				return (KEY_G);
			case (KEY_4):
				return (KEY_J);
			case (KEY_5):
				return (KEY_M);
			case (KEY_6):
				return (KEY_P);
			case (KEY_7):
				return (KEY_S);
			case (KEY_8):
				return (KEY_V);
			case (KEY_9):
				return (KEY_Y);
			default:
				cleanExit("Unexpected key (must be KEY_0-KEY_9)", EXIT_FAILURE);
		}
	}
	else if (key == lastKey && 
				key == beforeLastKey &&
					(beforeBeforeLastKey == -1 ||
					key != beforeBeforeLastKey))
	{
		beforeBeforeLastKey = beforeLastKey;
		beforeLastKey = lastKey;
		lastKey = key;
		lastKeyTime_sec = currentTime.tv_sec;
		lastKeyTime_usec = currentTime.tv_usec;
		if (key != KEY_BACKSPACE)
		{
			libUinputWrapper::press_key(uinput_fd, KEY_BACKSPACE, 0);
		}
		switch (key)
		{
			case (KEY_0):
				return (KEY_BACKSPACE);
			case (KEY_1):
				return (KEY_B);
			case (KEY_2):
				return (KEY_E);
			case (KEY_3):
				return (KEY_H);
			case (KEY_4):
				return (KEY_K);
			case (KEY_5):
				return (KEY_N);
			case (KEY_6):
				return (KEY_Q);
			case (KEY_7):
				return (KEY_T);
			case (KEY_8):
				return (KEY_W);
			case (KEY_9):
				return (KEY_Z);
			default:
				cleanExit("Unexpected key (must be KEY_0-KEY_9)", EXIT_FAILURE);
		}		
	}
	else if (key == lastKey && 
				key == beforeLastKey &&
					key == beforeBeforeLastKey)
	{
		libUinputWrapper::press_key(uinput_fd, KEY_BACKSPACE, 0);
		switch (key)
		{
			case (KEY_0):
				return (-1);
			case (KEY_1):
				return (KEY_C);
			case (KEY_2):
				return (KEY_F);
			case (KEY_3):
				return (KEY_I);
			case (KEY_4):
				return (KEY_L);
			case (KEY_5):
				return (KEY_O);
			case (KEY_6):
				return (KEY_R);
			case (KEY_7):
				return (KEY_U);
			case (KEY_8):
				return (KEY_X);
			case (KEY_9):
				return (KEY_9);
			default:
				cleanExit("Unexpected key (must be KEY_0-KEY_9)", EXIT_FAILURE);
		}		
	}
	return (-1);
}

void	Keypress::checkForNumberKeyAndPress(std::string &receivedCodeStr)
{
	bool error = false;

	if (receivedCodeStr == "KEY_0")
	{
		int key = discernCorrectKey(KEY_0);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_1")
	{
		int key = discernCorrectKey(KEY_1);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_2")
	{
		int key = discernCorrectKey(KEY_2);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_3")
	{
		int key = discernCorrectKey(KEY_3);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_4")
	{
		int key = discernCorrectKey(KEY_4);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_5")
	{
		int key = discernCorrectKey(KEY_5);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_6")
	{
		int key = discernCorrectKey(KEY_6);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_7")
	{
		int key = discernCorrectKey(KEY_7);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_8")
	{
		int key = discernCorrectKey(KEY_8);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	else if (receivedCodeStr == "KEY_9")
	{
		int key = discernCorrectKey(KEY_9);
		if (key == -1)
		{
			return ;
		}
		if (libUinputWrapper::press_key(uinput_fd, key, 0) < 0)
		{
			error = true;
		}
	}
	if (error == true)
	{
		cleanExit("Keypress failed", EXIT_FAILURE);
	}
}

bool	Keypress::checkForArrowKeyAndPress(std::string & receivedCodeStr)
{
	if (arrowKeyMovesMouse == true)
	{
		if (receivedCodeStr == "UP_KEY")
		{
			libUinputWrapper::move_mouse_from_cursor(uinput_fd, 0, -MOUSE_Y_MOVE_OFFSET);
			return (true);
		}
		else if (receivedCodeStr == "DOWN_KEY")
		{
			libUinputWrapper::move_mouse_from_cursor(uinput_fd, 0, MOUSE_Y_MOVE_OFFSET);
			return (true);
		}
		else if (receivedCodeStr == "RIGHT_KEY")
		{
			libUinputWrapper::move_mouse_from_cursor(uinput_fd, MOUSE_X_MOVE_OFFSET, 0);
			return (true);
		}
		else if (receivedCodeStr == "LEFT_KEY")
		{
			libUinputWrapper::move_mouse_from_cursor(uinput_fd, -MOUSE_X_MOVE_OFFSET, 0);
			return (true);
		}
		else if (receivedCodeStr == "CLICK_KEY")
		{
			libUinputWrapper::click(uinput_fd, LEFT_CLICK, 0);
			return (true);
		}
	}
	else
	{
		if (receivedCodeStr == "UP_KEY")
		{
			libUinputWrapper::press_key(uinput_fd, KEY_UP, 500);
			return (true);
		}
		else if (receivedCodeStr == "DOWN_KEY")
		{
			libUinputWrapper::press_key(uinput_fd, KEY_DOWN, 500);
			return (true);
		}
		else if (receivedCodeStr == "RIGHT_KEY")
		{
			libUinputWrapper::press_key(uinput_fd, KEY_RIGHT, 500);
			return (true);
		}
		else if (receivedCodeStr == "LEFT_KEY")
		{
			libUinputWrapper::press_key(uinput_fd, KEY_LEFT, 500);
			return (true);
		}
	}
	return (false);
}

void	Keypress::decodeKeyPress(char *receivedCode)
{
	std::string receivedCodeStr(receivedCode);

	if (receivedCodeStr == "KEY_ENTER")
	{
		libUinputWrapper::press_key(uinput_fd, KEY_ENTER, 0);
		return ;
	}
	if (receivedCodeStr == "KEY_RESTART")
	{
		arrowKeyMovesMouse = !arrowKeyMovesMouse;
		return ;
	}
	if (checkForArrowKeyAndPress(receivedCodeStr))
	{
		return ;		
	}
	checkForNumberKeyAndPress(receivedCodeStr);
}