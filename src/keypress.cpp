#include "../inc/keypress.h"
#include "../inc/main.h"

int uinp_fd = -1;

static void	checkIoctlErrors()
{
	int8_t errs[15];

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
    errs[12] = ioctl(uinp_fd, UI_SET_RELBIT, REL_Y);
	errs[14] = ioctl(uinp_fd, UI_SET_KEYBIT, BTN_LEFT);
	// errs[15] = 0;
	for (int i = 0; i < 15; i++)
	{
		if (errs[i] < 0)
		{
			perror("checkIoctlErrors::ioctl");
			std::cerr << '\n' << i << '\n' ;
			cleanExit(EXIT_FAILURE);
		}
	}
}

static void sendEvent(int fd, unsigned int keycode, int keyvalue, int eventType)
{
    struct input_event	event;

    gettimeofday(&event.time, NULL);
	if (eventType == KEY_EVENT)
    	event.type = EV_KEY;
	else if (eventType == MOUSE_EVENT)
    	event.type = EV_REL;
    event.code = keycode;
    event.value = keyvalue;
    if (write(fd, &event, sizeof(event)) < 0)
	{
		perror("write event");
		cleanExit(EXIT_FAILURE);
    }

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 1;
    write(fd, &event, sizeof(event));
    if (write(fd, &event, sizeof(event)) < 0)
	{
		perror("write event");
		cleanExit(EXIT_FAILURE);
    }
}

/*
*	/dev/uinput is correct on raspiOS, but must be switched to /dev/input/uinput on other systems
*/
void setupUinputDevice()
{
	struct uinput_user_dev uinp;

	uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if (uinp_fd < 0)
	{
		perror("open /dev/uinput");
		cleanExit(EXIT_FAILURE);
	}
	if (ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY) < 0 || ioctl(uinp_fd, UI_SET_EVBIT, EV_REL) < 0)
	{
		perror("setupUinputDevice::ioctl");
		cleanExit(EXIT_FAILURE);
	}

    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "raspiremote", 12);
    uinp.id.version = 1;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

	checkIoctlErrors();

	write(uinp_fd, &uinp, sizeof(uinp));
    if (ioctl(uinp_fd, UI_DEV_CREATE) < 0)
	{
		perror("ioctl UI_DEV_CREATE");
		cleanExit(EXIT_FAILURE);
    }
}

void	listenForKeyPress(struct lirc_config **lirc_config)
{
	char	*code = NULL;
	char	*receivedCodeStr = NULL;

	while (lirc_nextcode(&code) == 0)
	{
		if (code == NULL)
			continue ;
		do
		{
			if (lirc_code2char(*lirc_config, code, &receivedCodeStr) < 0)
			{
				throw (std::string("Infared::lircSetup()::lirc_code2char() FAILED..."));
			}
			if (receivedCodeStr == NULL)
			{
				break ;
			}
			decodeKeyPress(receivedCodeStr);
		} while (receivedCodeStr != NULL);
		
		free(code);
		code = NULL;
	}
}

void	decodeKeyPress(char *receivedCodeStr)
{
	if (ft_strncmp(receivedCodeStr, "KEY_0", 5) == 0)
		std::cout << "KEY_0\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_1", 5) == 0)
		std::cout << "KEY_1\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_2", 5) == 0)
		std::cout << "KEY_2\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_3", 5) == 0)
		std::cout << "KEY_3\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_4", 5) == 0)
		std::cout << "KEY_4\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_5", 5) == 0)
		std::cout << "KEY_5\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_6", 5) == 0)
		std::cout << "KEY_6\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_7", 5) == 0)
		std::cout << "KEY_7\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_8", 5) == 0)
		std::cout << "KEY_8\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_9", 5) == 0)
		std::cout << "KEY_9\n";
	else if (ft_strncmp(receivedCodeStr, "UP_KEY", 6) == 0)
	{
		for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_Y, -2, MOUSE_EVENT);
	}
	else if (ft_strncmp(receivedCodeStr, "DOWN_KEY", 8) == 0)
	{
		for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_Y, 2, MOUSE_EVENT);
	}
	else if (ft_strncmp(receivedCodeStr, "RIGHT_KEY", 9) == 0)
	{
		for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_X, 2, MOUSE_EVENT);
	}
	else if (ft_strncmp(receivedCodeStr, "LEFT_KEY", 8) == 0)
	{
		for (int i = 0; i < 25; i++)
			sendEventWrapper(REL_X, -2, MOUSE_EVENT);
	}
	else if (ft_strncmp(receivedCodeStr, "CLICK_KEY", 9) == 0)
	{
		std::cout << "CLICK_KEY\n";
		sendEventWrapper(BTN_LEFT, 1, KEY_EVENT);
	}
	else
		std::cerr << "BAD KEY\n";
}

void sendEventWrapper(unsigned int code, int value, int eventType)
{
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