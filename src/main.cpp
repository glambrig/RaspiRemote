#include "../inc/hardware.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"

int	main(void)
{
	Hardware hw;
	
	int fd = open("keycodes.txt", O_CREAT | O_RDWR);
	while (1)
	{
		sleep(1);
		std::cout << "hi\n";
		int n = digitalRead(IR_OUTPUT_PIN);
		if (n != 0)
		{
			write(fd, ft_itoa(n), ft_strlen(ft_itoa(n)));
			write(fd, "\n", 1);
		}
	}
	return (0);
}