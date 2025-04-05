#include "../inc/hardware.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"

int	main(void)
{
	int fd = open("keycodes", O_CREAT | O_RDWR);
	while (1)
	{
		int n = digitalRead(IR_OUTPUT_PIN);
		write(fd, ft_itoa(n), ft_strlen(ft_itoa(n)));
		write(fd, "\n", 1);
	}
	return (0);
}