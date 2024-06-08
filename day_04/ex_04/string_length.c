#include "string_length.h"
#include <stdio.h>

unsigned int string_length(char const* str)
{
	if(str == NULL) return 0;
	int size = 0;
	for(int i=0; str[i] != '\0'; ++i)
	{
		++size;
	}
	return size;
}
