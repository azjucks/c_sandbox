#include "funny_alpha.h"
#include <stdio.h>
#define SPACE 32

void my_put_char(char c)
{
	fwrite(&c, 1, sizeof(c), stdout);
}

void funny_alpha(void)
{
	int j=65;
	for (size_t i=0; i<26; ++i)
	{
		my_put_char(j);
		if(i%2)
		{
			j-=SPACE;
		}
		else
		{
			j+=SPACE;
		}
		j++;
	}
}
