#include <stdlib.h>
#include <stdio.h>

#include "expression.h"
#include "operation.h"
#include "string_length.h"
#include "string_duplicate.h"
#include "my_put_string.h"
#include "my_put_char.h"
#include "alpha_to_number.h"


char const* consume_operator(char const* str, char* operator)
{
	pointer_operation_type op_type = get_pointer_operation(str[0]);
	
	if(str == NULL || op_type == NULL || string_length(str) == 0)
		return NULL;
	
	*operator = str[0];

	return &str[1];
}

char const* consume_operand(char const* str, int* operand)
{
	if(str == NULL || string_length(str) == 0)
		return NULL;
		
	int i = 0, size = string_length(str);
	char* buffer;
	buffer = malloc((size + 1) * sizeof(char));

	for (; i < size; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			break;
		buffer[i] = str[i];
	}

	buffer[i] = '\0';
	*operand = alpha_to_number(buffer);
	
	free(buffer);
	return &str[i];
}

int parse_expression(char const* str, int* l_operand, char* operator, int* r_operand)
{
	char const* buffer = str;

	buffer = consume_operand(str, l_operand);

	if (buffer == NULL)
		return 0;

	buffer = consume_operator(buffer, operator);

	if (buffer == NULL)
		return 0;

	buffer = consume_operand(buffer, r_operand);

	if (buffer == NULL)
		return 0;
//	free(buffer);
	return 1;
}

void execute_expression(char const* str)
{
	int l;
	char op;
	int r;

	int executed = parse_expression(str, &l , &op, &r);

	if (!executed)
	{
		my_put_string("Expression is invalid\n");
	}
	else
	{
		execute_operation(l, op, r);
	}
}
