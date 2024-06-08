#include "my_put_char.h"
#include "string_length.h"
#include "put_number_base.h"
#include <stdio.h>

int power(int n, int p);

void put_numbase(int number, char const* base)
{
	int size = string_length(base);

	if (number < 0)
	{
		my_put_char('-');
		number = -number;
	}

	if (size == 0 || base == NULL) return;

	if (size == 1)
	{
		for (int i = 0; i < number+1; ++i)
		{
			my_put_char(base[0]);
		}
		return;
	}

	int	max_pow = 0;
	
	for (int i = 0; power(size, i) <= number; ++i)
	{

		max_pow = i;
	}
	
	int temp;

	while (max_pow >= 0)
	{
		
		temp = number/(power(size, max_pow));
		my_put_char(base[temp]);
		number -= temp * power(size, max_pow);
		--max_pow;
	}
}

int power(int num, int power)
{

	int result = 1;

	for (int i = 0; i < power; ++i)
	{
			result *= num;
	}

	return result;
}
