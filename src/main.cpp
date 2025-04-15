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

void	cleanExit(const char *exitMessage, int status)
{
	if (status == EXIT_FAILURE)
		perror(exitMessage);
	ir_ptr->~Infared();
	exit(status);
}

int	main(void)
{
	Infared		ir;
	Keypress	kp;
	gui			gui;

	ir_ptr = &ir;
	gui.setKeypressPtr(&kp);
	setupSigHandling();
	try
	{
		gui.setupGui();
		kp.setupUinputDevice();
		kp.listenForKeyPress(&(ir.getLircConfig()));
	}
	catch (std::string& e)
	{
		std::cerr << e << std::endl;
	}

	return (0);
}