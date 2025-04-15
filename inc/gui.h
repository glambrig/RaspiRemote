#pragma once

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "main.h"

#define EXIT_FAILURE 1
#define SCREEN_SIZE_X 1920
#define SCREEN_SIZE_Y 1080

enum currentGuiLayer
{
	YOUTUBE,
	MOVIES,
	CARTOONS,
	SETTINGS
};

struct	Keypress;

class gui
{
private:
	struct Keypress			*keypress;
	enum currentGuiLayer	currentGuiLayer;
	
	void defineMouseOffsets();
	void loadGuiHtmlPage();
	void openBrowser();
	gui& operator=(const gui& rhs);
	gui(const gui& copy);
public:
	gui();
	~gui();

	void	setupGui();
	void	setKeypressPtr(class Keypress *kp)
	{
		keypress = kp;
	}
};

