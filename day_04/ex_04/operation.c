#include <stdlib.h>

#include "operation.h"
#include "my_put_number.h"
#include "my_put_char.h"


int addition(int a, int b)
{
	int c = a + b;

	return c;
}

int substraction(int a, int b)
{
	int c = a - b;

	return c;
}

int multiplication(int a, int b)
{
	int c = a * b;

	return c;
}

int division(int a, int b)
{
	if (b == 0)
		return 0;

	int c = a / b;

	return c;
}

pointer_operation_type get_pointer_operation(char operator)
{
	switch(operator)
	{
		case '+':
			return addition;
		case '-':
			return substraction;
		case '*':
			return multiplication;
		case '/':
			return division;
		default:
			return NULL;
	}
}

void execute_operation(int l_operand, char operator, int r_operand)
{
	pointer_operation_type operation_type = get_pointer_operation(operator);

	if (operation_type == NULL)
		return;

	int result = operation_type(l_operand, r_operand);

	my_put_number(result);
	my_put_char('\n');
}
