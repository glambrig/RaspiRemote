#include "../inc/hardware.h"

Hardware::Hardware()
{
	wiringPiSetup();
	pinMode(IR_OUTPUT_PIN, INPUT);
}

Hardware::~Hardware()
{
}

Hardware::Hardware(const Hardware& copy)
{
	(void)copy;
}

Hardware& Hardware::operator=(const Hardware& rhs)
{
	(void)rhs;
	return (*this);
}
