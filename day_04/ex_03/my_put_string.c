#include "my_put_string.h"
#include "my_put_char.h"
#include <stdio.h>


void my_put_string(char const* str)
{
	if(str == NULL) return;
	for(size_t i=0; str[i] != '\0'; ++i)
	{
		my_put_char(str[i]);
	}
}
