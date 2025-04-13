#include "../inc/gui.h"

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

static void openBrowser()
{
	int		pid;
	char	*argv[] = {"/usr/bin/chromium-browser", NULL};

	pid = fork();
	if (pid <= 0)
	{
		if (pid < 0)
		{
			cleanExit("fork", EXIT_FAILURE);
		}
		execve("/usr/bin/chromium-browser", argv, __environ);
	}
	else
	{
		if (wait(NULL) < 0)
		{
			cleanExit("wait", EXIT_FAILURE);
		}
	}
}

static void loadGuiHtmlPage()
{

}

static void defineMouseOffsets()
{

}