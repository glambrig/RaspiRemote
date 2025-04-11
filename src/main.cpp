#include "../inc/infared.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"
#include <signal.h>

Infared *ir_ptr = NULL;

void	sighandler(int unused)
{
	(void)unused;
	ir_ptr->~Infared();
	std::cout << "Signal caught, raspiremote exited successfully" << std::endl;
	exit(EXIT_SUCCESS);
}

void	setupSigHandling(Infared& ir)
{
	struct sigaction	sa;

	ir_ptr = &ir;
	sa.sa_handler = &sighandler;
	sigaction(SIGINT, &sa, NULL);
}

int	main(void)
{
	Infared ir;

	setupSigHandling(ir);
	try
	{
		listenForKeyPress(ir.getLircConfig());
	}
	catch (std::string& e)
	{
		std::cerr << e << std::endl;
	}

	return (0);
}