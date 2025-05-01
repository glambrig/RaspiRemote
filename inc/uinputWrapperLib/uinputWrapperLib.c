#include "uinputWrapperLib.h"

int wrapper_lib_uinput_fd = -1;

static int	checkIoctlErrors()
{
	int8_t errs[NB_BUTTONS];

	errs[0] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_0);
	errs[1] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_1);
	errs[2] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_2);
	errs[3] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_3);
	errs[4] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_4);
	errs[5] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_5);
	errs[6] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_6);
	errs[7] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_7);
	errs[8] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_8);
	errs[9] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_9);

	errs[10] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_A);
	errs[11] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_B);
	errs[12] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_C);
	errs[13] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_D);
	errs[14] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_E);
	errs[15] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_F);
	errs[16] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_G);
	errs[17] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_H);
	errs[18] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_I);
	errs[19] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_J);
	errs[20] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_K);
	errs[21] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_L);
	errs[22] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_M);
	errs[23] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_N);
	errs[24] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_O);
	errs[25] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_P);
	errs[26] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_Q);
	errs[27] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_R);
	errs[28] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_S);
	errs[29] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_T);
	errs[30] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_U);
	errs[31] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_V);
	errs[32] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_W);
	errs[33] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_X);
	errs[34] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_Y);
	errs[35] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, KEY_Z);

    errs[36] = ioctl(wrapper_lib_uinput_fd, UI_SET_RELBIT, REL_X);
    errs[37] = ioctl(wrapper_lib_uinput_fd, UI_SET_RELBIT, REL_Y);
	errs[38] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, BTN_LEFT);
	errs[39] = ioctl(wrapper_lib_uinput_fd, UI_SET_KEYBIT, BTN_RIGHT);
	errs[40] = 0;
	for (int i = 0; i < NB_BUTTONS - 1; i++)
	{
		if (errs[i] < 0)
		{
			(void)write(STDERR_FILENO, "uinput: failed to set ioctl\n", 29);
			return (-1);
		}
	}
	return (0);
}

int setup_device(const char *device_name, const char *path_to_uinput)
{
	struct uinput_user_dev uinp;

	wrapper_lib_uinput_fd = open(path_to_uinput, O_WRONLY | O_NONBLOCK);
	if (wrapper_lib_uinput_fd < 0)
	{
		return (-1);
	}
	if (ioctl(wrapper_lib_uinput_fd, UI_SET_EVBIT, EV_KEY) < 0 || ioctl(wrapper_lib_uinput_fd, UI_SET_EVBIT, EV_REL) < 0)
	{
		return (-1);
	}

    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, device_name, strlen(device_name));
    uinp.id.version = 1;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

	if (checkIoctlErrors() < 0)
	{
		return (-1);
	}
	if (write(wrapper_lib_uinput_fd, &uinp, sizeof(uinp)) < 0)
	{
		return (-1);
	}
    if (ioctl(wrapper_lib_uinput_fd, UI_DEV_CREATE) < 0)
	{
		return (-1);
    }
	return (wrapper_lib_uinput_fd);
}

int	send_event_to_device(int device_fd, unsigned int which_key, int key_value, int event_type, u_int32_t release_key_after_ms)
{
	struct input_event	event;

    gettimeofday(&event.time, NULL);
	if (event_type == KEY_EVENT)
	{
    	event.type = EV_KEY;
	}
	else if (event_type == MOUSE_EVENT)
	{
    	event.type = EV_REL;
	}
	else
	{
		(void)write(STDERR_FILENO, "uinput: invalid event type\n", 28);
		return (-1);
	}
    event.code = which_key;
    event.value = key_value;
    if (write(device_fd, &event, sizeof(event)) < 0)
	{
		(void)write(STDERR_FILENO, "uinput: write to device failed\n", 32);
		return (-1);
    }

	if (release_key_after_ms > 0)
	{
		usleep(release_key_after_ms);
	}
	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 1;
	if (write(device_fd, &event, sizeof(event)) < 0)
	{
		(void)write(STDERR_FILENO, "uinput: write to device failed\n", 32);
		return (-1);
	}
	return (0);
}

int	click(int device_fd, u_int32_t release_key_after_ms)
{
	return (send_event_to_device(device_fd, BTN_LEFT, 1, MOUSE_EVENT, release_key_after_ms));
}

int	press_key(int device_fd, u_int16_t key, u_int32_t release_key_after_ms)
{
	return (send_event_to_device(device_fd, key, 1, MOUSE_EVENT, release_key_after_ms));
}

int	move_mouse_to_pos(int device_fd, int16_t x, int16_t y, struct screensize screensize)
{
	if (send_event_to_device(device_fd, REL_X, screensize.x - x, MOUSE_EVENT, 0) < 0)
	{
		return (-1);
	}
	if (send_event_to_device(device_fd, REL_Y, screensize.y - y, MOUSE_EVENT, 0) < 0)
	{
		return (-1);
	}
	return (0);
}

int	move_mouse_from_cursor(int device_fd, int16_t x, int16_t y)
{
	if (send_event_to_device(device_fd, REL_X, x, MOUSE_EVENT, 0) < 0)
	{
		return (-1);
	}
	if (send_event_to_device(device_fd, REL_Y, y, MOUSE_EVENT, 0) < 0)
	{
		return (-1);
	}
	return (0);	
}

int cleanup_device(int device_fd)
{
	if (device_fd > 0)
	{
		if (ioctl(device_fd, UI_DEV_DESTROY) < 0)
		{
			return (-1);
		}
		if (close(device_fd) < 0)
		{
			return (-1);
		}
	}
	return (0);
}
