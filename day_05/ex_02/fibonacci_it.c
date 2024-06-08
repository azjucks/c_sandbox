#include "fibonacci_it.h"


unsigned int fibonacci_it(unsigned int n)
{
	if (n == 0)
		return 0;

	unsigned int result = 1;

	unsigned int prev = 0;

	for (unsigned int i = 0; i < n; ++i)
	{
		unsigned int temp = result + prev;
		prev = result;
		result = temp;
	}

	return prev;
}
