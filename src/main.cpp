#include "../inc/infared.h"
#include "../inc/keypress.h"
#include "../inc/gui.h"

int	main(void)
{
	Infared ir;
	
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