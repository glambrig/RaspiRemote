#pragma once

#include <iostream>
#include <string>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "../inc/libft/libft.h"

#define IR_OUTPUT_PIN 0

typedef class Hardware
{
private:
	Hardware(const Hardware& copy);
	Hardware& operator=(const Hardware& rhs);
public:
	Hardware();
	~Hardware();
}	Hardware;