#include "../inc/keypress.h"

void	listenForKeyPress(struct lirc_config *&lirc_config)
{
	char	*code = NULL;
	char	*receivedCodeStr = NULL;

	while (lirc_nextcode(&code) == 0)
	{
		if (code == NULL)
			continue ;
		do
		{
			if (lirc_code2char(lirc_config, code, &receivedCodeStr) < 0)
			{
				throw (std::string("Infared::lircSetup()::lirc_code2char() FAILED..."));
			}
			if (receivedCodeStr == NULL)
			{
				break ;
			}
			decodeKeyPress(receivedCodeStr);
		} while (receivedCodeStr != NULL);
		
		free(code);
		code = NULL;
	}
}

void	decodeKeyPress(char *receivedCodeStr)
{
	if (ft_strncmp(receivedCodeStr, "KEY_0", 5) == 0)
		std::cout << "KEY_0\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_1", 5) == 0)
		std::cout << "KEY_1\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_2", 5) == 0)
		std::cout << "KEY_2\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_3", 5) == 0)
		std::cout << "KEY_3\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_4", 5) == 0)
		std::cout << "KEY_4\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_5", 5) == 0)
		std::cout << "KEY_5\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_6", 5) == 0)
		std::cout << "KEY_6\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_7", 5) == 0)
		std::cout << "KEY_7\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_8", 5) == 0)
		std::cout << "KEY_8\n";
	else if (ft_strncmp(receivedCodeStr, "KEY_9", 5) == 0)
		std::cout << "KEY_9\n";
	else if (ft_strncmp(receivedCodeStr, "UP_KEY", 6) == 0)
		std::cout << "UP_KEY\n";
	else if (ft_strncmp(receivedCodeStr, "DOWN_KEY", 8) == 0)
		std::cout << "DOWN_KEY\n";
	else if (ft_strncmp(receivedCodeStr, "LEFT_KEY", 8) == 0)
		std::cout << "LEFT_KEY\n";
	else if (ft_strncmp(receivedCodeStr, "RIGHT_KEY", 9) == 0)
		std::cout << "RIGHT_KEY\n";
	else if (ft_strncmp(receivedCodeStr, "CLICK_KEY", 9) == 0)
		std::cout << "CLICK_KEY\n";
	else
		std::cerr << "BAD KEY\n";
}