#include "display_combination.h"
#include "my_put_char.h"
#include <stdio.h>

void display_combination(void)
{
	int f_ascii = 48;
	for(size_t i = 0; i<=9; i++)
	{
		int s_ascii = 49+i;
		for (size_t j = i+1; j<=9; j++)
		{
			my_put_char(f_ascii);
			my_put_char(s_ascii);
			my_put_char(' ');
			s_ascii++;
		}
		f_ascii++;
	}
}
