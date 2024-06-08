#include "sort_char.h"
#include "swap_char.h"
#include <stdio.h>


void sort_char(char* tab, unsigned int tab_length)
{
	if (tab == NULL || tab_length == 0)
	{
		return;
	}
	for (unsigned int i = 0; i < tab_length-1; ++i)
	{
		for (unsigned int j = 0; j < tab_length-i-1; ++j)
		{
			if (tab[j] > tab[j + 1])
			{
				swap_char(&tab[j], &tab[j + 1]);
			}
		}
	}
}
