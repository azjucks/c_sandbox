#include "is_prime.h"
#include "my_put_char.h"
#include <stdio.h>

void is_prime(unsigned int num)
{
	unsigned int nb = num/2;
	int prime_check = 1;
	if(num == 0) prime_check = 0;
	if(num == 1) prime_check = 0;
	for(size_t i = 2; i < nb; i++)
	{
		if(num % i == 0)
		{
			prime_check = 0;
		}
	}
	if(prime_check) my_put_char('Y');
	else my_put_char('N');
}
