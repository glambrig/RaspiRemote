#include "../inc/keypress.h"
#include "../inc/gui.h"
#include "../inc/main.h"

void	Keypress::listenForKeyPress(struct lirc_config **lirc_config)
{
	char	*code = NULL;
	char	*receivedCode = NULL;

	while (lirc_nextcode(&code) == 0)
	{
		if (code == NULL)
			continue ;
		do
		{
			if (lirc_code2char(*lirc_config, code, &receivedCode) < 0)
			{
				free(code);
				cleanExit("lirc_code2char", EXIT_FAILURE);
			}
			if (receivedCode == NULL)
			{
				break ;
			}
			decodeKeyPress(receivedCode);
		} while (receivedCode != NULL);
		
		free(code);
		code = NULL;
	}
}

void	Keypress::checkForNumberKey(char *receivedCode)
{
	static int32_t			lastKey = -1;
	static int32_t			beforeLastKey = -1;
	static int32_t			beforeBeforeLastKey = -1;
	static struct timeval	lastKeyTime;

	if (guiPtr->isCursorOnSearchBar() == false)
		return ;
		// TODO
// 	gettimeofday(&lastKeyTime, NULL);
// 	if (ft_strncmp(receivedCode, "KEY_0", 5) == 0)
// 	{
// 		struct timeval temp;
// 		gettimeofday(&temp, NULL);
// 		if (lastKey != -1)
// 		{
// 			if (beforeLastKey != -1)
// 			{
// 				if (beforeBeforeLastKey != -1)
// 				{

// 				}
// 				beforeBeforeLastKey = KEY_0;
// 			}
// 			beforeLastKey = KEY_0;
// 		}
// 		lastKey = KEY_0;
// 	}
}

bool	Keypress::checkForArrowKey(char *receivedCode)
{
	if (ft_strncmp(receivedCode, "UP_KEY", 6) == 0)
	{
		uinputWrapperLib::move_mouse_from_cursor(uinput_fd, 0, -10);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "DOWN_KEY", 8) == 0)
	{
		uinputWrapperLib::move_mouse_from_cursor(uinput_fd, 0, 10);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "RIGHT_KEY", 9) == 0)
	{
		uinputWrapperLib::move_mouse_from_cursor(uinput_fd, 10, 0);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "LEFT_KEY", 8) == 0)
	{
		uinputWrapperLib::move_mouse_from_cursor(uinput_fd, -10, 0);
		return (true);
	}
	else if (ft_strncmp(receivedCode, "CLICK_KEY", 9) == 0)
	{
		uinputWrapperLib::click(uinput_fd, 0);
		return (true);
	}
	return (false);
}

void	Keypress::decodeKeyPress(char *receivedCodeStr)
{
	if (checkForArrowKey(receivedCodeStr))
		return ;		
	checkForNumberKey(receivedCodeStr);
}