#include "swap_char.h"


void swap_char(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}
