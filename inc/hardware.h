#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <wiringPi.h>
#include <lirc/lirc_client.h>
#include "../inc/libft/libft.h"

#define IR_OUTPUT_PIN 17
#define LIRC_DEBUG_LEVEL 1
#define KEYPRESSCODES_SIZE 15

// 	 KEY_0 = 0x00FF6897;
// 	 KEY_1 = 0x00FF30CF;
// 	 KEY_2 = 0x00FF18E7;
// 	 KEY_3 = 0x00FF7A85;
// 	 KEY_4 = 0x00FF10EF;
// 	 KEY_5 = 0x00FF38C7;
// 	 KEY_6 = 0x00FF5AA5;
// 	 KEY_7 = 0x00FF42BD;
// 	 KEY_8 = 0x00FF4AB5;
// 	 KEY_9 = 0x00FF52AD;
// 	 BTN_DPAD_LEFT = 0x00FF22DD;
// 	 BTN_DPAD_RIGHT = 0x00FFC23D;
// 	 BTN_DPAD_DOWN = 0x00FFE01F;
// 	 BTN_DPAD_UP = 0x00FF906F;
// 	 BTN_MOUSE = 0x00FF02FD;

typedef class Hardware
{
private:
	struct lirc_config	*lirc_config = NULL;

	Hardware(const Hardware& copy);
	Hardware& 	operator=(const Hardware& rhs);
	void		lircSetup();
public:
	Hardware();
	~Hardware();
}	Hardware;