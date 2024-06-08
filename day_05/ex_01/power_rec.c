#include <stdlib.h>

#include "power_rec.h"


int power_rec(int base, unsigned int pow)
{
	if (pow == 0)
		return 1;

	return power_rec(base, --pow) * base;
}
