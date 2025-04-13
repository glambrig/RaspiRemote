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

}

static void loadGuiHtmlPage()
{

}

static void defineMouseOffsets()
{

}