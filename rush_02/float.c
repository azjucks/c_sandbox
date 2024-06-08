#include <stdlib.h>
#include <stdio.h>

#include "float.h"
#include "my_put_string.h"
#include "my_put_char.h"
#include "my_put_number.h"
#include "string_length.h"
#include "alpha_to_number.h"

//t_float works with a mantissa and an exponent
//the mantissa is the whole numbers contained in the mantissa
//there, in each mantissa, the first item is the size of the dynamically allocated array


//if the number is negative, return 1 and change it to its absolute value
int	is_negative(int* n)
{
	if(*n < 0)
	{
		*n = -*n;
		return 1;
	}
	else
	{
		return 0;
	}
}

//init the float to its base values
void	init_float(t_float* f)
{
	if (f == NULL)
		return;

	if (f == NULL)
		return;

	f->mantissa = NULL;
	f->exponent = 0;
}

//reset the float to its base values and free its allocated memory
void	reset_float(t_float* f)
{
	if (f == NULL)
		return;

	if (f->mantissa != NULL)
		free(f->mantissa);

	f->mantissa = NULL;
	f->exponent = 0;

}

//copy the content of the src to the dest one, by allocating the needed memory
void	duplicate_float(t_float* fdest, t_float const* fsrc)
{
	if (fdest == NULL || fsrc == NULL || fsrc->mantissa == NULL)
		return;

	fdest->mantissa = (int *) malloc((fsrc->mantissa[0] + 1) * sizeof(int));
	if (fdest->mantissa == NULL)
		return;

	fdest->mantissa = fsrc->mantissa;
	fdest->exponent = fsrc->exponent;
}

//add a digit to the right of the float
void	add_digit_right(t_float* f, int digit)
{
	if (digit < 0 || f == NULL)
		return;
	//realloc the memory add the digit to the mantissa
	f->mantissa =  realloc(f->mantissa, ++f->mantissa[0] * sizeof(int));
	if (f->mantissa == NULL)
		return;

	f->mantissa[f->mantissa[0]] = digit;
}

//add a digit to the left of the float
void	add_digit_left(t_float* f, int digit)
{
	if (digit < 0 || f == NULL)
		return;
	//realloc the memory to add the digit to the mantissa
	f->mantissa = (int *) realloc(f->mantissa, ++f->mantissa[0] * sizeof(int));
	if (f->mantissa == NULL)
		return;
	
	int i = f->mantissa[0];
	//loop through the mantissa items to move them to the right
	for (; i > 0; --i)
	{
		f->mantissa[i] = f->mantissa[i - 1];
	}
	
	//now the first place is free, so we can add the digit
	f->mantissa[1] = digit;


	//if the mantissa is negative, only its first item must also be, so change the minus to the new first digit
	if (is_negative(&f->mantissa[2]))
	{
		f->mantissa[1] = -f->mantissa[1];
	}
}

//init the float from the given string
void	init_from_string(t_float* f, char const* str)
{
	if (f == NULL || str == NULL || string_length(str) == 0 || str[0] == ',')
		return;

	init_float(f);

	int size = string_length(str), exp = size, nb_size = size, exponent = 0;

	//loop reversly through the string to get the exponent value
	for (; exp > 0; --exp)
	{
		++exponent;
		if (str[exp] == ',')
		{
			--nb_size;
			break;
		}
	}

	if (str[0] == '-')
		--nb_size;

	//allocate needed memory to the mantissa based of the number of digits in the string
	f->mantissa = malloc((nb_size + 1) * sizeof(int));
	if(f->mantissa == NULL)
		return;

	//store the size of the mantissa at its first item
	f->mantissa[0] = nb_size;

	int i = 1;

	//fill the mantissa by looping again through the string
	for (int j = 0; j <= size; ++j)
	{
		//only get digits
		if (str[j] >= '0' && str[j] <= '9')
		{
			char temp = str[j];
			//convert the char to digit and add it to the mantissa
			int temp_int = alpha_to_number(&temp);
			if (j == 1 && str[0] == '-')
				temp_int = -temp_int;
			f->mantissa[i] = temp_int;
			i++;
		}
	}

	f->exponent = --exponent;
}

//print the given float on the screen
void	print_float(t_float const* f)
{
	if (f == NULL)
		return;

	int size = f->mantissa[0], is_negative_var = is_negative(&f->mantissa[1]);
	//if the mantissa if negative, print a minus first
	if(is_negative_var)
		my_put_char('-');

	//loop to print the mantissa
	for (int i = 1; i < size + 1; ++i)
	{
		//if there is an exponent, add a comma to the output
		if (i == size - f->exponent + 2)
			my_put_char(',');
		my_put_number(f->mantissa[i]);
	}

	my_put_char('\n');

	//as the is_negative function changes the first digit to its absolute value, if the digit was firstly negative, we have to set it back (my_put_number might handle this but I realized it a bit later)
	if (is_negative_var)
		f->mantissa[1] = -f->mantissa[1];
}

//function to add two mantisses, in WIP, that's why the function exceeds the lines limit
void 	add_mantisses(t_float const* f1, t_float const* f2, t_float* fres)
{
	int		temp_int = 0;
	t_float	highest_sized_float;
	t_float	lowest_sized_float;
	
	if (f1->mantissa[0] > f2->mantissa[0])
	{
		duplicate_float(&highest_sized_float, f1);
		duplicate_float(&lowest_sized_float, f2);
	}
	else
	{
		duplicate_float(&highest_sized_float, f2);
		duplicate_float(&lowest_sized_float, f1);
	}
	
	int	highest = highest_sized_float.mantissa[0], lowest = lowest_sized_float.mantissa[0];

	int*	temp_array = malloc(highest * sizeof(int));

	int	current = 1;

	for (int i = 0; i < highest; ++i)
	{
		if (i < highest - lowest)
		{
			temp_array[i] = 0;
		}
		else
		{
			temp_array[i] = lowest_sized_float.mantissa[current];
			++current;
		}
	}

	for (int i = 0; i < highest; ++i)
	{
		temp_int *= 10;
		temp_int += highest_sized_float.mantissa[i + 1] + temp_array[i];
	}
	
	int count = 0;
	do
	{
		++count;
		num /= 10
	}
	while(num != 0)

	fres->mantissa = malloc(--count * sizeof(int));

	
}
