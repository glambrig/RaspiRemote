#include "../inc/infared.h"
#include "../inc/main.h"

struct lirc_config	*lirc_config = NULL;

static void	lircSetup()
{	
	if (lirc_init("raspiremote", LIRC_DEBUG_LEVEL) == -1)
	{
		cleanExit("lirc_init", EXIT_FAILURE);
	}
	if (lirc_readconfig("/etc/lirc/lircrc", &lirc_config, NULL) == -1)
	{
		cleanExit("lirc_readconfig", EXIT_FAILURE);
	}
}

void Infared::setup()
{
	wiringPiSetup();
	pinMode(IR_OUTPUT_PIN, INPUT);
	lircSetup();
}

void Infared::destroy()
{
	lirc_freeconfig(lirc_config);
	lirc_deinit();
}

struct lirc_config	**Infared::getLircConfig()
{
	return (&lirc_config);
}