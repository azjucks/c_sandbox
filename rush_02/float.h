#ifndef __FLOAT__
#define __FLOAT__

struct s_float
{
	int* mantissa;
	int exponent;
};

typedef struct s_float t_float;

//function to return if number is negative and change its value to absolute
int	is_negative(int* n);

//init the float, sets the mantissa to NULL and exponent to 0
void	init_float(t_float* f);

//reset the float free the mantissa if it exists, and set mantissa to NULL and exponent to 0
void	reset_float(t_float* f);

//copy the src float to the dest one, by allocating the needed memory to it
void	duplicate_float(t_float* fdest, t_float const* fsrc);

//add a digit to the right of the float
void	add_digit_right(t_float* f, int digit);

//add a digit to the left of the float
void	add_digit_left(t_float* f, int digit);

//init the float from a string, set the correct mantissa and exponent values
void	init_from_string(t_float* f, char const* str);

//print the given float to the terminal
void	print_float(t_float const* f);

//add two mantisses and return it to the mantissa of fres
void	add_mantisses(t_float const* f1, t_float const* f2, t_float* fres);

#endif
