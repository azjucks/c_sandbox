#include <stdlib.h>

#include "power_it.h"


int power_it(int base, unsigned int pow)
{
	int result = 1;

	for (unsigned int i = 0; i < pow; ++i)
	{
		result *= base;
	}

	return result;

}
