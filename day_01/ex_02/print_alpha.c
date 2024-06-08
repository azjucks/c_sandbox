#include "print_alpha.h"
#include <stdio.h>


void my_put_char(char c)
{
	fwrite(&c, 1, sizeof(c), stdout);
}

void print_alpha(void)
{
	for(size_t i=97; i <= 122; ++i)
	{
		my_put_char(i);
	}
}
