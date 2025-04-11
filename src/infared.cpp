#include "../inc/infared.h"

Infared::Infared()
{
	wiringPiSetup();
	pinMode(IR_OUTPUT_PIN, INPUT);
	lircSetup();
}

Infared::~Infared()
{
	lirc_freeconfig(lirc_config);
	lirc_deinit();
}

Infared::Infared(const Infared& copy)
{
	(void)copy;
}

Infared& Infared::operator=(const Infared& rhs)
{
	(void)rhs;
	return (*this);
}

struct lirc_config	*&Infared::getLircConfig()
{
	return (lirc_config);
}

void	Infared::lircSetup()
{	
	if (lirc_init("raspiremote", LIRC_DEBUG_LEVEL) == -1)
	{
		perror("lirc_init");
		exit(EXIT_FAILURE);
	}
	if (lirc_readconfig("/etc/lirc/lircrc", &lirc_config, NULL) == -1)
	{
		perror("lirc_readconfig");
		exit(EXIT_FAILURE);
	}
}