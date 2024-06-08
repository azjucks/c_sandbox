#include "string_length.h"
#include "string_compare.h"
#include "find_string.h"
#include <stdio.h>

char const* find_string(char const* to_find, char const* str)
{
	int find_length = string_length(to_find);
	int str_length = string_length(str);

	if (find_length == 0 || str_length == 0)
		return NULL;

	for (int i = 0; i < str_length - find_length + 1; ++i)
	{

		if (str[i] == to_find[0])
		{
			char temp[find_length+1];
			temp[find_length] = '\0';
			int k = 0;
			
			for (int j = i; j < i + find_length; j++)
			{
				temp[k] = str[j];
				++k;
			}

			if (string_compare(to_find, temp) == 0)
				return &str[i];
		}
	}
	return NULL;
}
