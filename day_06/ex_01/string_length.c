#include "string_length.h"
#include <stdio.h>
unsigned int string_length(char const* str)
{
	if(str == NULL) return 0;
	size_t size = 0;
	for(size_t i=0; str[i] != '\0'; ++i)
	{
		++size;
	}
	return size;
}
