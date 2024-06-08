#include <stdlib.h>
#include <stdio.h>

#include "ini_read.h"

t_section* read_section(t_ini* ini, char const* str)
{
	if (ini == NULL || str == NULL)
		return NULL;

	char* sect_name = NULL;

	int i = parse_section(str, &sect_name);

	t_section* sect = find_section(ini, sect_name);

	if (i == 0 || sect != NULL)
	{
		free(sect_name);

		return NULL;
	}

	sect = add_section(ini, sect_name);

	if (sect_name != NULL)
		free(sect_name);

	return sect;
}

t_property* read_property(t_ini* ini, char const* str, char const* section)
{
	if ( ini == NULL || str == NULL || section == NULL)
		return NULL;

	char* prop_name = NULL;
	char* prop_value = NULL;

	int i = parse_property(str, &prop_name, &prop_value);

	t_section* sect = find_section(ini, section);

	t_property* prop = find_property(sect, prop_name);

	if (sect == NULL || i == 0)
	{
		if (prop_name != NULL && sect == NULL)
			free(prop_name);

		if (prop_value != NULL && sect == NULL)
			free(prop_value);

		return NULL;
	}
	if (prop != NULL)
	{
		if (prop_name != NULL)
			free(prop_name);

		if (prop_value != NULL)
			free(prop_value);

		return NULL;
	}

	prop = add_property(sect, prop_name, prop_value);
	if (prop_name != NULL)
		free(prop_name);

	if (prop_value != NULL)
		free(prop_value);

	return prop;
}

t_ini* read_ini_file(char const* file_path)
{
	if (file_path == NULL)
		return NULL;

	t_ini* ini = create_ini();

	FILE* file = fopen(file_path, "rb");

	char* line = read_line(file);

	t_section* sect = NULL;
	t_section* last_sect = NULL;

	char* sect_name = NULL;

	while (line != NULL)
	{
		char* prop_name = NULL;
		char* prop_value = NULL;

		int is_sec = parse_section(line, &sect_name);

		int is_prop = parse_property(line, &prop_name, &prop_value);
		if (prop_name != NULL)
			free(prop_name);

		if (prop_value != NULL)
			free(prop_value);

		if (is_sec)
		{
			last_sect = find_section(ini, sect_name);

			sect = read_section(ini, line);
			if (sect_name != NULL)
			{
				free(sect_name);
				sect_name = NULL;
			}
		}
		else if (is_prop)
		{
			if (last_sect != NULL)
				read_property(ini, line, last_sect->name);
			else if (sect != NULL)
				read_property(ini, line, sect->name);
		}
		free(line);
		line = read_line(file);
	}
	free(line);

	fclose(file);

	return ini;
}
