#include "ini_write.h"


char const* get_property(t_ini* ini, char const* section_name, char const* name)
{
	if (ini == NULL || section_name == NULL || name == NULL)
		return NULL;
	
	t_section* sect = find_section(ini, section_name);
	if (sect == NULL)
		return NULL;

	t_property* prop = find_property(sect, name);
	if (prop != NULL)
		return prop->value;

	return NULL;
}

void set_property(t_ini* ini, char const* section_name, char const* name, char const* value)
{
	if (ini == NULL || section_name == NULL || name == NULL || value == NULL)
		return;
	
	t_section* sect = find_section(ini, section_name);
	if (sect == NULL)
		sect = add_section(ini, section_name);
	
	t_property* prop = find_property(sect, name);
	if (prop == NULL)
	{
		prop = add_property(sect, name, value);
	}
	else
	{
		if (prop->value != NULL)
			free(prop->value);

		prop->value = string_duplicate(value);
	}
}

void write_ini_file(char const* file_path, t_ini* ini)
{
	if (file_path == NULL || ini == NULL || ini->sections == NULL)
		return;

	FILE* file = fopen(file_path, "w");

	t_list_node* sect_node = ini->sections->head;
	t_list_node* prop_node = NULL;

	while(sect_node != NULL)
	{
		fputc('[', file);
		fputs(((t_section*)sect_node->data)->name, file);
		fputs("]\n", file);
		if (((t_section*)sect_node->data)->properties != NULL)
		{
			prop_node = ((t_section*)sect_node->data)->properties->head;
		}
		while(prop_node != NULL)
		{
			fputs(((t_property*)prop_node->data)->name, file);
			fputc('=', file);
			fputs(((t_property*)prop_node->data)->value, file);
			fputc('\n', file);
			prop_node = prop_node->next;
		}
		sect_node = sect_node->next;
	}
	fclose(file);
}
