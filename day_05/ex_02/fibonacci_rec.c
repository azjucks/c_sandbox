#include "fibonacci_rec.h"

unsigned int fibonacci_rec(unsigned int n)
{
	if (n <= 0)
		return 0;
	else if (n == 1)
		return 1;
	return fibonacci_rec(n - 2) + fibonacci_rec(n - 1);
}
