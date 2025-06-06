#include "../inc/infared.h"
#include "../inc/keypress.h"
#include "../inc/main.h"
#include <signal.h>

int			uinput_fd;

static void	sighandler(int unused)
{
	(void)unused;
	cleanExit("\nSignal caught, raspiremote exited successfully\n", EXIT_SUCCESS);
}

static void	setupSigHandling()
{
	struct sigaction	sa;

	sa.sa_handler = &sighandler;
	sigaction(SIGINT, &sa, NULL);
}

void	cleanExit(const char *exitMessage, int status)
{
	if (status == EXIT_FAILURE)
	{
		perror(exitMessage);
	}
	else
	{
		std::cout << exitMessage;
	}
	Infared::destroy();
	libUinputWrapper::cleanup_device(uinput_fd);
	exit(status);
}

int	main(void)
{
	Keypress	kp;

	setupSigHandling();
	Infared::setup();

	uinput_fd = libUinputWrapper::setup_device("raspiremote", "/dev/uinput");
	if (uinput_fd < 0)
	{
		cleanExit("Failed to set up uinput device", EXIT_FAILURE);
	}
	kp.setUinputFd(uinput_fd);
	kp.listenForKeyPress(Infared::getLircConfig());

	return (0);
}