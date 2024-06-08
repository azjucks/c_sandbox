#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "parse_file.h"
#include "string_length.h"
#include "string_duplicate.h"

int	read_char(FILE* file, char* pointer_c)
{
	if (file == NULL || pointer_c == NULL)
		return 0;
	char c = fgetc(file);

	if (feof(file) != 0)	
		return 0;

	*pointer_c = c;

	return 1;
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	
	return 0;
}

char*	sub_string(char const* str, unsigned int pos, unsigned int len)
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

char*	read_line(FILE* file)
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

	string_cpy = realloc(string_cpy, (size + 1) * sizeof(char));

	string_cpy[size] = '\0';

	if (string_cpy == NULL)
		return NULL;

	for (int i = 0; i < size; ++i)
		if (string_cpy[i] == '\n')
			string_cpy[i] = '\0';

	return string_cpy;
}

char**	parse_line_infos(char const* line)
{
	if (line == NULL)
		return NULL;

	char** infos = malloc(5 * sizeof(char*));

	int infos_count = 0, j = 0;

//	infos[0] = malloc(sizeof(char*));

	char* temp = malloc(sizeof(char));

	for (int i = 0; infos_count < 4; ++i)
	{
		if (line[i] == '|' || line[i] == '\0')
		{
			temp[j] = '\0';
			infos[infos_count] = string_duplicate(temp);
			free(temp);
			temp = malloc(sizeof(char));
			j = 0;
			++infos_count;
//			infos[infos_count] = malloc(sizeof(char*));
			continue;
		}
		temp[j] = line[i];
		temp = realloc(temp, (++j + 1) * sizeof(char));
	}
	free(temp);
	if (infos_count != 4)
	{
		for (int i = 0; i < infos_count; ++i)
			free(infos[i]);
		return NULL;
	}
	
	infos[4] = NULL;
	return infos;
}

char**	parse_line_attributes(char const* line)
{
	if (line == NULL)
		return NULL;

	char** infos_line = parse_line_infos(line);

	if(infos_line == NULL)
		return NULL;

	int infos_i = 0;
	while(infos_line[infos_i])
		free(infos_line[infos_i++]);
	free(infos_line);

	int attr_start = 0, separator_count = 0;

	while (separator_count != 4)
	{
		if (line[attr_start] == '|')
			++separator_count;
		if (line[attr_start] == '\0')
			return NULL;
		++attr_start;
	}

	char** attr = malloc(sizeof(char*));

	char* temp = malloc(sizeof(char));

	int current_attr = 0, j = 0;

	for (unsigned int i = attr_start; i < string_length(line) + 1; ++i)
	{
		if (line[i] == '|' || line[i] == '\0')
		{
			temp[j] = '\0';
			attr[current_attr] = string_duplicate(temp);
			free(temp);
			temp = malloc(sizeof(char));
			attr = realloc(attr, (++current_attr + 1) * sizeof(char*));
			j = 0;
			continue;
		}
		temp[j] = line[i];
		temp = realloc(temp, (++j + 1) * sizeof(char));
	}
	free(temp);

	attr[current_attr] = NULL;

	return attr;
}

int	parse_attribute(char const* str, char** attr_name, char** attr_value)
{
	if (str == NULL || attr_name == NULL || attr_value == NULL || 
		!is_attribute(str, string_length(str)))
		return 0;

	int size = string_length(str);

	char* temp_name = malloc((string_length(str) + 1) * sizeof(char));
	if (temp_name == NULL)
		return 0;

	char* temp_value = malloc((string_length(str) + 1) * sizeof(char));
	if (temp_value == NULL)
		return 0;

	temp_name[size] = '\0';
	temp_value[size] = '\0';

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
	temp_value[j] = '\0';

	*attr_name = string_duplicate(temp_name);
	*attr_value = string_duplicate(temp_value);

	free(temp_name);
	free(temp_value);

	return 1;
}

bool	is_attribute(char const* str, int size)
{
	if (str == NULL)
		return 0;

	int cond = 0, i = 0;
	
	while (i <= size)
		if (str[i++] == '=')
			++cond;

	if (cond == 1)
		return 1;
	
	return 0;
}
