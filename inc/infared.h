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

#define IR_OUTPUT_PIN 17
#define LIRC_DEBUG_LEVEL 1

namespace Infared
{
	/*
	*	Sets up WiringPi and LIRC
	*/
	void				setup();

	/*
	*	Releases resources used by LIRC
	*/
	void				destroy();

	/*
	*	Returns a pointer to the pointer referencing lirc_config
	*/
	struct lirc_config	**getLircConfig();
}	//namespace