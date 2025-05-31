#include "../inc/gui.h"
#include "../inc/keypress.h"
#include <iostream>

//cursorOnSearchBar(true) is for TESTING, change to FALSE
gui::gui() : cursorOnSearchBar(true)
{
}

gui& gui::operator=(const gui& rhs)
{
	(void)rhs;
	return (*this);
}

gui::gui(const gui& copy)
{
	(void)copy;
}

gui::~gui()
{
}

void gui::setupGui()
{
	// openBrowser();
	// loadGuiHtmlPage();
	// defineMouseOffsets();
}

void gui::openBrowser()
{
	int			pid;
	const char	*argv[] = {"/usr/bin/chromium-browser", "--start-maximized", "--app=localhost:8080", NULL};

	pid = fork();
	if (pid <= 0)
	{
		if (pid < 0)
		{
			cleanExit("fork", EXIT_FAILURE);
		}
		execve("/usr/bin/chromium-browser", (char * const *)argv, __environ);
	}
	if (wait(NULL) < 0)
	{
		cleanExit("wait", EXIT_FAILURE);
	}
	std::cout << "browser opening..." << std::endl;
}

void gui::loadGuiHtmlPage()
{

}

void gui::defineMouseOffsets()
{
	int		fd;
	char	buff[129];

	buff[128] = '\0';
	fd = open("../gui/guioffset.conf", O_RDONLY);
	if (fd < 0)
	{
		cleanExit("open guioffset.conf", EXIT_FAILURE);
	}
	while (read(fd, buff, 128) > 0)
	{
		//find each value and set
	}
	// keypress->sendEventWrapper(REL_Y, SCREEN_SIZE_Y, MOUSE_EVENT);
	// keypress->sendEventWrapper(REL_X, -SCREEN_SIZE_X, MOUSE_EVENT);
}