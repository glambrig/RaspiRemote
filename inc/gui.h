#pragma once

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

