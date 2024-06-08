#include <stdio.h>
#include "my_put_char.h"
#include "string_length.h"
#include "my_put_string.h"

void reverse_string(char const* str)
{
	size_t size = string_length(str);
	char temp[size];
	temp[size] = '\0';

	for(size_t i = 0; i < size; ++i)
	{
		temp[i] = str[size-1-i];
	}
	my_put_string(temp);
}
