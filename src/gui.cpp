#include "../inc/gui.h"
#include <iostream>

static void openBrowser()
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
	else
	{
		if (wait(NULL) < 0)
		{
			cleanExit("wait", EXIT_FAILURE);
		}
	}
	std::cout << "browser opening..." << std::endl;
}

static void loadGuiHtmlPage()
{

}

static void defineMouseOffsets()
{

}

gui::gui()
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

/*
*	Opens browser, loads GUI page, defines mouse movement offsets
*/
void gui::setupGui()
{
	openBrowser();
	loadGuiHtmlPage();
	defineMouseOffsets();
}