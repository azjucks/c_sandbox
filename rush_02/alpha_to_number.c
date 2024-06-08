#include "string_length.h"
#include "alpha_to_number.h"
#include <stdio.h>

int alpha_to_number(char const* str)
{
	if(str == NULL) return 0;
	int size = string_length(str);
	int is_negative = 0;
	if(str[0] == 45)
	{
		is_negative = 1;
	}
	int number = 0;
	for(int i = 0; i < size; ++i)
	{
		int temp = number;
		for(int j = 48; j < 58; ++j)
		{
			if(str[i] == j)
			{
				number+=j-48;
				number*=10;
			}
		}
		if(is_negative && i == 0)
		{	
		}
		else if (number == temp && i != 0)
		{
			break;
		}
	}
	number/=10;
	if(is_negative)
	{
		number = -number;
	}
	return number;
}
