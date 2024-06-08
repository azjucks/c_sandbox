#include "my_put_char.h"
#include "my_put_number.h"
#include <stdio.h>

int abs(int n);

void my_put_number(int num)
{
	size_t i = 0;
	if(num < 0)
	{
		my_put_char('-');
		num = -num;
	}
	char buffer[16];
	do
	{
		buffer[i++] = abs(num % 10) + '0';
		num /= 10;
	}
	while(num != 0);
	
	while(i-- > 0) my_put_char(buffer[i]);

}
int abs(int n)
{
	if(n < 0) return -n;
	else return n;
}
