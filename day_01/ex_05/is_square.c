#include "is_square.h"
#include "my_put_char.h"
#include <stdio.h>

void is_square(unsigned int num)
{

	for(size_t i=1; i<=num; i++)
	{
		if(i*i == num)
		{
			my_put_char('Y');
			return;
		}
	}
	my_put_char('N');

}
