#include "../inc/hardware.h"

Hardware::Hardware()
{
	wiringPiSetup();
	pinMode(IR_OUTPUT_PIN, INPUT);
	lircSetup();
}

Hardware::~Hardware()
{
	lirc_freeconfig(lirc_config);
	lirc_deinit();
}

Hardware::Hardware(const Hardware& copy)
{
	(void)copy;
}

Hardware& Hardware::operator=(const Hardware& rhs)
{
	(void)rhs;
	return (*this);
}

void	Hardware::lircSetup()
{
	char	*code;
	
	if (lirc_init("raspi", LIRC_DEBUG_LEVEL) == -1)
		exit(EXIT_FAILURE);
	if (lirc_readconfig("/etc/lirc/lircrc", &lirc_config, NULL) == -1)
		exit(EXIT_FAILURE);
	while (lirc_nextcode(&code) == 0)
	{
		if (code == NULL)
			continue ;
		for (int i = 0; i < KEYPRESSCODES_SIZE; i++)
		{
			// if (ft_strncmp(code, "0x00FF6897", 11) == 0)
			// 	std::cout << "0x00FF6897\n";
			// else if (ft_strncmp(code, "0x00FF30CF", 11) == 0)
			// 	std::cout << "0x00FF30CF\n";
			// else if (ft_strncmp(code, "0x00FF18E7", 11) == 0)
			// 	std::cout << "0x00FF18E7\n";
			// else if (ft_strncmp(code, "0x00FF7A85", 11) == 0)
			// 	std::cout << "0x00FF7A85\n";
			// else if (ft_strncmp(code, "0x00FF10EF", 11) == 0)
			// 	std::cout << "0x00FF10EF\n";
			// else if (ft_strncmp(code, "0x00FF38C7", 11) == 0)
			// 	std::cout << "0x00FF38C7\n";
			// else if (ft_strncmp(code, "0x00FF5AA5", 11) == 0)
			// 	std::cout << "0x00FF5AA5\n";
			// else if (ft_strncmp(code, "0x00FF42BD", 11) == 0)
			// 	std::cout << "0x00FF42BD\n";
			// else if (ft_strncmp(code, "0x00FF4AB5", 11) == 0)
			// 	std::cout << "0x00FF4AB5\n";
			// else if (ft_strncmp(code, "0x00FF52AD", 11) == 0)
			// 	std::cout << "0x00FF52AD\n";
			// else if (ft_strncmp(code, "0x00FF22DD", 11) == 0)
			// 	std::cout << "0x00FF22DD\n";
			// else if (ft_strncmp(code, "0x00FFC23D", 11) == 0)
			// 	std::cout << "0x00FFC23D\n";
			// else if (ft_strncmp(code, "0x00FFE01F", 11) == 0)
			// 	std::cout << "0x00FFE01F\n";
			// else if (ft_strncmp(code, "0x00FF906F", 11) == 0)
			// 	std::cout << "0x00FF906F\n";
			// else if (ft_strncmp(code, "0x00FF02FD", 11) == 0)
			// 	std::cout << "0x00FF02FD\n";
			std::cout << code << '\n';
			// else
			// 	std::cout << "nope\n";
		}
		free(code);
	}
}