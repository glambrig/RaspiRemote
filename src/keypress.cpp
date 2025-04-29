#include "../inc/keypress.h"
#include "../inc/gui.h"
#include "../inc/main.h"

int uinp_fd = -1;

static void	checkIoctlErrors()
{
	int8_t errs[NB_BUTTONS];

	errs[0] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_0);
	errs[1] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_1);
	errs[2] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_2);
	errs[3] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_3);
	errs[4] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_4);
	errs[5] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_5);
	errs[6] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_6);
	errs[7] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_7);
	errs[8] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_8);
	errs[9] = ioctl(uinp_fd, UI_SET_KEYBIT, KEY_9);
    errs[10] = ioctl(uinp_fd, UI_SET_RELBIT, REL_X);
    errs[11] = ioctl(uinp_fd, UI_SET_RELBIT, REL_Y);
	errs[12] = ioctl(uinp_fd, UI_SET_KEYBIT, BTN_LEFT);
	errs[13] = 0;
	for (int i = 0; i < NB_BUTTONS - 1; i++)
	{
		if (errs[i] < 0)
		{
			std::cout << i << '\n';
			cleanExit("checkIoctlErrors::ioctl", EXIT_FAILURE);
		}
	}
}

static void sendEvent(int fd, unsigned int keycode, int keyValue, int eventType)
{
    struct input_event	event;

    gettimeofday(&event.time, NULL);
	if (eventType == KEY_EVENT)
    	event.type = EV_KEY;
	else if (eventType == MOUSE_EVENT)
    	event.type = EV_REL;
    event.code = keycode;
    event.value = keyValue;
    if (write(fd, &event, sizeof(event)) < 0)
	{
		cleanExit("write event", EXIT_FAILURE);
    }

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 1;
    if (write(fd, &event, sizeof(event)) < 0)
	{
		cleanExit("write event", EXIT_FAILURE);
    }
}

/*
*	/dev/uinput is correct on raspiOS, but must be switched to /dev/input/uinput on other systems
*/
void Keypress::setupUinputDevice()
{
	struct uinput_user_dev uinp;

	uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if (uinp_fd < 0)
	{
		cleanExit("open /dev/uinput", EXIT_FAILURE);
	}
	if (ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY) < 0 || ioctl(uinp_fd, UI_SET_EVBIT, EV_REL) < 0)
	{
		cleanExit("setupUinputDevice::ioctl", EXIT_FAILURE);
	}

    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "raspiremote", 12);
    uinp.id.version = 1;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

	checkIoctlErrors();

	if (write(uinp_fd, &uinp, sizeof(uinp)) < 0)
	{
		cleanExit("write", EXIT_FAILURE);
	}
    if (ioctl(uinp_fd, UI_DEV_CREATE) < 0)
	{
		cleanExit("ioctl UI_DEV_CREATE", EXIT_FAILURE);
    }
}

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

void	Keypress::checkForNumberKey(char *receivedCode)
{
	static int32_t			lastKey = -1;
	static int32_t			beforeLastKey = -1;
	static int32_t			beforebeforeLastKey = -1;
	static struct timeval	lastKeyTime;

	if (guiPtr->isCursorOnSearchBar() == false)
		return ;
	gettimeofday(&lastKeyTime, NULL);
	if (ft_strncmp(receivedCode, "KEY_0", 5) == 0)
	{
		if (gettimeofday() - lastKeyTime < 400)
		{
			if (lastKey == KEY_0 && beforeLastKey == KEY_0)
				sendEventWrapper(KEY_SPACE, 1, KEY_EVENT);
			else if (lastKey == KEY_0)
				sendEventWrapper(KEY_BACKSPACE, 1, KEY_EVENT);
		}
		else
			sendEventWrapper(KEY_0, 1, KEY_EVENT);
		beforebeforeLastKey = beforeLastKey;
		beforeLastKey = lastKey;
		lastKey = KEY_0;
		lastKeyTime = gettimeofday();
		return ;
	}
}

// void	Keypress::checkForNumberKey(char *receivedCode)
// {
// 	static int32_t	lastKey = -1;
// 	static int32_t	beforeLastKey = -1;
// 	static int32_t	beforebeforeLastKey = -1;
// 	static time_t	lastKeyTime = time(NULL);

// 	std::cout << "lastKeyTime: " << lastKeyTime << '\n';
// 	if (guiPtr->isCursorOnSearchBar() == false)
// 		return ;
// 	if (ft_strncmp(receivedCode, "KEY_0", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			std::cout << "in\n";
// 			if (lastKey == KEY_0 && beforeLastKey == KEY_0)
// 				sendEventWrapper(KEY_SPACE, 1, KEY_EVENT);
// 			else if (lastKey == KEY_0)
// 				sendEventWrapper(KEY_BACKSPACE, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_0, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_0;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_1", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_1 && beforeLastKey == KEY_1 && beforebeforeLastKey == KEY_1)
// 				sendEventWrapper(KEY_C, 1, KEY_EVENT);
// 			else if (lastKey == KEY_1 && beforeLastKey == KEY_1)
// 				sendEventWrapper(KEY_B, 1, KEY_EVENT);
// 			else if (lastKey == KEY_1)
// 				sendEventWrapper(KEY_A, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_1, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_1;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_2", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_2 && beforeLastKey == KEY_2 && beforebeforeLastKey == KEY_2)
// 				sendEventWrapper(KEY_F, 1, KEY_EVENT);
// 			else if (lastKey == KEY_2 && beforeLastKey == KEY_2)
// 				sendEventWrapper(KEY_E, 1, KEY_EVENT);
// 			else if (lastKey == KEY_2)
// 				sendEventWrapper(KEY_D, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_2, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_2;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_3", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_3 && beforeLastKey == KEY_3 && beforebeforeLastKey == KEY_3)
// 				sendEventWrapper(KEY_I, 1, KEY_EVENT);
// 			else if (lastKey == KEY_3 && beforeLastKey == KEY_3)
// 				sendEventWrapper(KEY_H, 1, KEY_EVENT);
// 			else if (lastKey == KEY_3)
// 				sendEventWrapper(KEY_G, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_3, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_3;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_4", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_4 && beforeLastKey == KEY_4 && beforebeforeLastKey == KEY_4)
// 				sendEventWrapper(KEY_L, 1, KEY_EVENT);
// 			else if (lastKey == KEY_4 && beforeLastKey == KEY_4)
// 				sendEventWrapper(KEY_K, 1, KEY_EVENT);
// 			else if (lastKey == KEY_4)
// 				sendEventWrapper(KEY_J, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_4, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_4;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_5", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_5 && beforeLastKey == KEY_5 && beforebeforeLastKey == KEY_5)
// 				sendEventWrapper(KEY_O, 1, KEY_EVENT);
// 			else if (lastKey == KEY_5 && beforeLastKey == KEY_5)
// 				sendEventWrapper(KEY_N, 1, KEY_EVENT);
// 			else if (lastKey == KEY_5)
// 				sendEventWrapper(KEY_M, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_5, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_5;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_6", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_6 && beforeLastKey == KEY_6 && beforebeforeLastKey == KEY_6)
// 				sendEventWrapper(KEY_R, 1, KEY_EVENT);
// 			else if (lastKey == KEY_6 && beforeLastKey == KEY_6)
// 				sendEventWrapper(KEY_Q, 1, KEY_EVENT);
// 			else if (lastKey == KEY_6)
// 				sendEventWrapper(KEY_P, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_6, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_6;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_7", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_7 && beforeLastKey == KEY_7 && beforebeforeLastKey == KEY_7)
// 				sendEventWrapper(KEY_U, 1, KEY_EVENT);
// 			else if (lastKey == KEY_7 && beforeLastKey == KEY_7)
// 				sendEventWrapper(KEY_T, 1, KEY_EVENT);
// 			else if (lastKey == KEY_7)
// 				sendEventWrapper(KEY_S, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_7, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_7;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_8", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_8 && beforeLastKey == KEY_8 && beforebeforeLastKey == KEY_8)
// 				sendEventWrapper(KEY_X, 1, KEY_EVENT);
// 			else if (lastKey == KEY_8 && beforeLastKey == KEY_8)
// 				sendEventWrapper(KEY_W, 1, KEY_EVENT);
// 			else if (lastKey == KEY_8)
// 				sendEventWrapper(KEY_V, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_8, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_8;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	if (ft_strncmp(receivedCode, "KEY_9", 5) == 0)
// 	{
// 		if (time(NULL) - lastKeyTime < 400)
// 		{
// 			if (lastKey == KEY_9 && beforeLastKey == KEY_9)
// 				sendEventWrapper(KEY_Z, 1, KEY_EVENT);
// 			else if (lastKey == KEY_9)
// 				sendEventWrapper(KEY_Y, 1, KEY_EVENT);
// 		}
// 		sendEventWrapper(KEY_9, 1, KEY_EVENT);
// 		beforebeforeLastKey = beforeLastKey;
// 		beforeLastKey = lastKey;
// 		lastKey = KEY_9;
// 		lastKeyTime = time(NULL);
// 		return ;
// 	}
// 	return ;
// }

bool	Keypress::checkForArrowKey(char *receivedCode)
{
	if (ft_strncmp(receivedCode, "UP_KEY", 6) == 0)
	{
		// for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_Y, -10, MOUSE_EVENT);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "DOWN_KEY", 8) == 0)
	{
		// for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_Y, 10, MOUSE_EVENT);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "RIGHT_KEY", 9) == 0)
	{
		// for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_X, 10, MOUSE_EVENT);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "LEFT_KEY", 8) == 0)
	{
		// for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_X, -10, MOUSE_EVENT);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "CLICK_KEY", 9) == 0)
	{
		sendEventWrapper(BTN_LEFT, 1, KEY_EVENT);
		sendEventWrapper(BTN_LEFT, 0, KEY_EVENT);
		return (true);
	}
	return (false);
}

void	Keypress::decodeKeyPress(char *receivedCodeStr)
{
	if (checkForArrowKey(receivedCodeStr))
		return ;		
	checkForNumberKey(receivedCodeStr);
}

void Keypress::sendEventWrapper(unsigned int code, int value, int eventType)
{
	std::cout << "code: " << code << '\n';
	sendEvent(uinp_fd, code, value, eventType);
}

void cleanupUinputDevice()
{
	if (uinp_fd > 0)
	{
		ioctl(uinp_fd, UI_DEV_DESTROY);
		close(uinp_fd);
	}
}