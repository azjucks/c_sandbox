#include <stdlib.h>

#include "float.h"
#include "my_put_char.h"
#include "my_put_string.h"

int main()
{
	t_float f;

	init_from_string(&f, "1,234");

	print_float(&f);

	my_put_char('\n');

	add_digit_right(&f, 0);

	print_float(&f);

	my_put_char('\n');

	add_digit_left(&f, 7);

	print_float(&f);

	t_float f2;

	t_float f3;

	init_from_string(&f2, "15");

	init_float(&f3);

	print_float(&f2);

	my_put_string("-------------\n");

	add_mantisses(&f, &f2, &f3);

	reset_float(&f);
	reset_float(&f2);
	reset_float(&f3);

	return 0;
}
