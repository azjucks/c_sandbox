#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "string_length.h"
#include "string_to_word_array.h"
#include "string_sized_copy.h"

char ** string_to_word_array (char const * str)
{
	if(str == NULL)
		return NULL;

	int startingIndex = 0;
	int endingIndex = 0;
	int wordsQuantity = 0;
	int strLength = string_length (str);
	
	//check words quantity
	for ( int j = 0; j < strLength + 1 ; j++)
	{
		if ( str[j] == ' ' || str[j] == '\n' || str[j] == '\t' || str[j] == '\0')
		{
			endingIndex = j;
			if(str[startingIndex] != ' ' && str[startingIndex] != '\n' && str[startingIndex]!= '\t' && str[startingIndex] != '\0')
			{
				wordsQuantity ++;
			}
			startingIndex = endingIndex + 1;
		}
	}
	
	startingIndex = 0;
	endingIndex = 0;

	int wordIndex = 0;
	char ** wordArray = malloc ((wordsQuantity + 1) * sizeof(char *));
	wordArray[wordsQuantity] = NULL;

	for ( int j = 0; j < strLength + 1 ; j++)
	{
		if ( str[j] == ' ' || str[j] == '\n' || str[j] == '\t' || str[j] == '\0')
		{
			endingIndex = j;
			if(str[startingIndex] != ' ' && str[startingIndex] != '\n' && str[startingIndex] != '\t' && str[startingIndex] != '\0')
			{
				wordArray[wordIndex] = malloc (( endingIndex - startingIndex + 1) * sizeof (char));
				wordArray[wordIndex][endingIndex - startingIndex] = '\0';
				
				
				string_sized_copy(wordArray[wordIndex], &str[startingIndex], endingIndex - startingIndex);
				/*for (int i = 0; i < endingIndex - startingIndex ; i++)
				{	
				wordArray[wordIndex][i] = str[i + startingIndex];
				}*/
				wordIndex++;
			}
			startingIndex = endingIndex + 1;
		}
		
	}		
	
	
	return wordArray;


		
}
