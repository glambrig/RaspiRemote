#include "../inc/infared.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"
#include <signal.h>

Infared *ir_ptr = NULL;

static void	sighandler(int unused)
{
	(void)unused;
	ir_ptr->~Infared();
	std::cout << " Signal caught, raspiremote exited successfully" << std::endl;
	exit(EXIT_SUCCESS);
}

static void	setupSigHandling()
{
	struct sigaction	sa;

	sa.sa_handler = &sighandler;
	sigaction(SIGINT, &sa, NULL);
}

static void	setupPointers(Infared &ir, Keypress &kp, gui &gui)
{
	ir_ptr = &ir;
	gui.setKeypressPtr(&kp);
	kp.setGuiPtr(&gui);
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

	setupPointers(ir, kp, gui);
	setupSigHandling();
	std::cout << "setup finished\n";

	// gui.setupGui();
	// std::cout << "gui setup finished\n";
	kp.setupUinputDevice();
	std::cout << "uinput setup finished\n";
	kp.listenForKeyPress(&(ir.getLircConfig()));

	return (0);
}