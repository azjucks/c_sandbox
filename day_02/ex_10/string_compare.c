#include "string_compare.h"
#include "string_length.h"
#include <stdio.h>

int min_size();

int string_compare(char const* str1, char const* str2)
{
	int str1_length = string_length(str1);
	int str2_length = string_length(str2);
	int min = min_size(str1_length, str2_length);

	int result = 0;

	for (int i = 0; i < min; i++)
	{
		if (str1[i] < str2[i])
			return result=-1;
		else if (str2[i] < str1[i])
			return result=1;
	}
	if (str1_length < str2_length)
		return result=-1;
	else if (str2_length < str1_length)
		return result=1;
	else
		return result=0;
}

int min_size(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
