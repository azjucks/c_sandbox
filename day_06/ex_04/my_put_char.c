#include <stdio.h>
#include "my_put_char.h"

void my_put_char(char c)
{
	fwrite(&c, 1, sizeof(c), stdout);
}
