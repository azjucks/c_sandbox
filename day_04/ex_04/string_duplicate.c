#include <stdlib.h>
#include <stdio.h>
#include "string_length.h"
#include "string_sized_copy.h"
#include "string_sized_concatenate.h"


char* string_duplicate(char const* str)
{
	if (str == NULL)
		return NULL;

	int			size = string_length(str) + 1;
	char*		duplicated;


	duplicated = malloc(size * sizeof(char));

	if (duplicated == NULL)
		return NULL;

	string_sized_copy(duplicated, str, size);

	return duplicated;
}
