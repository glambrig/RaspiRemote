#include "../inc/gui.h"
#include "../inc/keypress.h"
#include <iostream>


gui::gui() : cursorOnSearchBar(false)
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
	openBrowser();
	loadGuiHtmlPage();
	defineMouseOffsets();
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
	char	*buff = NULL;

	fd = open("../gui/guioffset.conf", O_RDONLY);
	if (fd < 0)
	{
		cleanExit("open guioffset.conf", EXIT_FAILURE);
	}
	while (read(fd, buff, 128) > 0)
	{
		//find each value and set
	}
	keypress->sendEventWrapper(REL_Y, SCREEN_SIZE_Y, MOUSE_EVENT);
	keypress->sendEventWrapper(REL_X, -SCREEN_SIZE_X, MOUSE_EVENT);
}

// void	gui::guiUpdate(uint8_t buttonPressType, char *receivedCode)
// {
// 	if (buttonPressType > 1)
// 	{
// 		std::cerr << "Unknown button type\n";
// 		return ;
// 	}
// 	switch (buttonPressType)
// 	{
// 		case BUTTONPRESS_ARROW:
// 			break ;
// 		case BUTTONPRESS_NUMBER:
// 			break ;
// 	}
// }