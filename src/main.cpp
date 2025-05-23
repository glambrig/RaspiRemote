#include "../inc/infared.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"
#include <signal.h>

int			uinput_fd;

static void	sighandler(int unused)
{
	(void)unused;
	Infared::destroy();
	uinputWrapperLib::cleanup_device(uinput_fd);
	std::cout << " Signal caught, raspiremote exited successfully" << std::endl;
	exit(EXIT_SUCCESS);
}

static void	setupSigHandling()
{
	struct sigaction	sa;

	sa.sa_handler = &sighandler;
	sigaction(SIGINT, &sa, NULL);
}

static void	setupPointers(Keypress &kp, gui &gui)
{
	gui.setKeypressPtr(&kp);
	kp.setGuiPtr(&gui);
}

void	cleanExit(const char *exitMessage, int status)
{
	if (status == EXIT_FAILURE)
		perror(exitMessage);
	Infared::destroy();
	uinputWrapperLib::cleanup_device(uinput_fd);
	exit(status);
}

int	main(void)
{
	Keypress	kp;
	gui			gui;

	setupPointers(kp, gui);
	setupSigHandling();
	Infared::setup();

	uinput_fd = uinputWrapperLib::setup_device("raspiremote", "/dev/uinput");
	if (uinput_fd < 0)
	{
		cleanExit("Failed to set up uinput device", EXIT_FAILURE);
	}
	kp.setUinputFd(uinput_fd);
	kp.listenForKeyPress(Infared::getLircConfig());

	return (0);
}