#pragma once

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "main.h"

#define EXIT_FAILURE 1

enum currentGuiLayer
{
	YOUTUBE,
	MOVIES,
	CARTOONS,
	SETTINGS
};

class gui
{
private:
	enum currentGuiLayer currentGuiLayer;
	
	gui& operator=(const gui& rhs);
	gui(const gui& copy);
public:
	gui();
	~gui();

	void setupGui();
};

