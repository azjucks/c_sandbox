#include <unistd.h>
#include <stdio.h>
#include "string_length.h"
#include "my_put_char.h"

#define START_ASCII 48
#define MAX_ASCII 61
#define SLEEP_TIME 150000

//functions declaration
void	fill_buffer(char const* base, char* buffer, int size);

int		add_value(char const base, char buffer, int i);

//function to loop on a buffer to get the needed result;
void	station(char const* result)
{
	//size of the string to print
	int			size = string_length(result);
	//creation of a buffer to contain the changing string
	char	 	buffer[size];

	//call of fill_buffer function to get the correct starting buffer
	fill_buffer(result, buffer, size);

//loop to go from 0 to 61, [0-9A-Za-z]
for (int i = 0; i < MAX_ASCII; ++i)
	{
		//loop on each char on the buffer
		for (int j = 0; j < size; ++j)
		{
			//condition to check if the current char needs to be changed or not
			buffer[j] += result[j] < START_ASCII ? 0 : add_value(result[j], buffer[j], i);

			//print of the current char on the terminal
			my_put_char(buffer[j]);
			//function to force the stdout to write buffered data of above line
			fflush(stdout);
		}
		//after each iteration of the first loop, go back to the beginning of the line
		my_put_char('\r');
		//wait to see the progress
		usleep(SLEEP_TIME);
	}
	//new line to get the matching result from the example
	my_put_char('\n');
}

// function that returns an integer
int		add_value(char const base, char buf_char, int i)
{
	int add;
	
	//conditions to check which number to return
	if (buf_char == base)
		add = 0;
	else if (i == 9)
		add = 8;
	else if (i == 35)
		add = 7;
	else
		add = 1;
	
	//return the number given by the conditions
	return add;
}

// function to create the correct base_buffer
void	fill_buffer(char const* base, char* buffer, int size)
{
	//loop to iterate through the buffer_size and set matching chars to '0'
	//matching chars are from 0 to z in ASCII table
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = base[i] > START_ASCII ? '0' : base[i];
	}
}
