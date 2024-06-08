#include "string_length.h"
#include "is_palindrome.h"
//#include "reverse_string.h"
//#include "string_compare.h"
#include <stdbool.h>
#include <stdio.h>


bool is_palindrome(char const* str)
{
	if (str == NULL)
		return NULL;
	int i, count = 0, size = string_length(str);

	for (i = 0; i < size/2; ++i)
	{

		if (str[i] == str[size - i - 1])
			++count;
	}

	if (i == count)
		return true;
	return false;
}
