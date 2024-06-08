#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "parse_file.h"
#include "string_length.h"
#include "string_duplicate.h"


int read_char(FILE* file, char* pointer_c)
{
	if (file == NULL || pointer_c == NULL)
		return 0;
	char c = fgetc(file);

	if (feof(file) != 0)	
		return 0;

	*pointer_c = c;

	return 1;
}

int is_space(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	
	return 0;
}

char* sub_string(char const* str, unsigned int pos, unsigned int len)
{
	if (str == NULL || (pos - len) == 0)
		return NULL;

	char* string_cpy = malloc((len + 1) * sizeof(char));

	if (string_cpy == NULL)
		return NULL;

	string_cpy[len] = '\0';

	for (unsigned int i = 0; i < len; ++i)
	{
		string_cpy[i] = str[pos++];
	}

	return string_cpy;
}

char* read_line(FILE* file)
{
	if (file == NULL)
		return NULL;

	char* string_cpy = malloc((150) * sizeof(char));

	char* t = string_cpy;

	string_cpy = fgets(string_cpy, 150, file);

	int size = string_length(string_cpy);

	if (size == 0)
	{
		free(t);
		return NULL;
	}

	string_cpy = realloc(string_cpy, (size +1) * sizeof(char));

	string_cpy[size] = '\0';

	if (string_cpy == NULL)
		return NULL;

	for (int i = 0; i < size; ++i)
		if (string_cpy[i] == '\n')
			string_cpy[i] = '\0';

	return string_cpy;
}

int parse_section(const char* str, char** p_section_name)
{
	int f = 0, s = 0;
	if (str == NULL || p_section_name == NULL ||
		!is_section(str, string_length(str), &f, &s))
		return 0;

	char* temp = malloc(sizeof(char));

	int size = 1, i = f + 1;

	while (i < s)
	{
		temp[size - 1] = str[i];
		++i;
		++size;
		temp = realloc(temp, size * sizeof(char));
	}

	temp[size - 1] = '\0';

	*p_section_name = temp;

	return 1;

}

int parse_property(const char* str, char** p_name, char** p_value)
{
	if (str == NULL || p_name == NULL || p_value == NULL ||
		!is_property(str, string_length(str)))
		return 0;

	char *temp_name = malloc((string_length(str) + 1) * sizeof(char));
	char *temp_value = malloc((string_length(str) + 1) * sizeof(char));

	temp_name[string_length(str)] = '\0';

	temp_value[string_length(str)] = '\0';

	int i = 0, j = 0;

	while (str[i] != '=')
		temp_name[j++] = str[i++];

	temp_name = realloc(temp_name, (i + 1) * sizeof(char));

	temp_name[i] = '\0';

	++i;
	j = 0;

	while (str[i] != '\0')
		temp_value[j++] = str[i++];

	temp_value = realloc(temp_value, (j + 1) * sizeof(char));

	*p_name = string_duplicate(temp_name);
	*p_value = string_duplicate(temp_value);

	free(temp_name);
	free(temp_value);

	return 1;
}

bool is_section(char const* str, int size, int* f, int* s)
{
	int cond = 0;
	for (int i = 0; i <= size; ++i)
	{
		if (str[i] == '[' || str[i] == ']')
			++cond;
		if (str[i] == '[')
			*f = i;
		if (str[i] == ']')
			*s = i;
	}

	if (cond == 2)
		return 1;

	return 0;
}

bool is_property(char const* str, int size)
{
	int cond = 0, i = 0;

	for (; i <= size; ++i)
	{
		if (str[i] == '=')
			++cond;
	}
	if (cond == 1)
		return 1;

	return 0;
}
