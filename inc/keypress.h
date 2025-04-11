#pragma once

#include <iostream>

#include <lirc/lirc_client.h>
#include "../inc/libft/libft.h"

void	decodeKeyPress(char *receivedCodeStr);
void	listenForKeyPress(struct lirc_config *&lirc_config);