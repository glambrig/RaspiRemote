#include "../inc/infared.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"
#include <signal.h>

Infared *ir_ptr = NULL;

void	sighandler(int unused)
{
	(void)unused;
	ir_ptr->~Infared();
	std::cout << " Signal caught, raspiremote exited successfully" << std::endl;
	exit(EXIT_SUCCESS);
}

void	setupSigHandling()
{
	struct sigaction	sa;

	sa.sa_handler = &sighandler;
	sigaction(SIGINT, &sa, NULL);
}

void	cleanExit(int status)
{
	ir_ptr->~Infared();
	exit(status);
}

int	main(void)
{
	Infared ir;

	ir_ptr = &ir;
	setupSigHandling();
	try
	{
		setupUinputDevice();
		listenForKeyPress(&(ir.getLircConfig()));
	}
	catch (std::string& e)
	{
		std::cerr << e << std::endl;
	}

	return (0);
}