#include <stdlib.h>
#include <stdio.h>

#include "my_put_string.h"
#include "list_internal.h"
#include "string_compare.h"
#include "ini.h"
#include "ini_tools.h"


void print_property(void* property)
{
	if (property == NULL)
		return;
	
	t_property* prop = (t_property*)property;

	my_put_string("  \"");
	my_put_string(prop->name);
	my_put_string("\" = \"");
	my_put_string(prop->value);
	my_put_string("\"\n");
}

void print_section(void* section)
{
	if (section == NULL)
		return;

	t_section* sect = (t_section*)section;

	my_put_string("Section : \"");
	my_put_string(sect->name);
	my_put_string("\"\n");

	t_list_node* current = sect->properties->head;
	while (current != NULL)
	{
		print_property(current->data);
		current = current->next;
	}
}

void print_ini(t_ini* ini)
{
	if (ini == NULL)
		return;

	t_list_node* current = ini->sections->head;
	while (current != NULL)
	{
		print_section(current->data);
		current = current->next;
	}
}

t_section* add_section(t_ini* ini, char const* section)
{
	if (ini == NULL || section == NULL)
		return NULL;

	t_section* sect = create_section(section);

	list_insert_next(ini->sections, NULL, sect);

	return sect;
}

t_property* add_property(t_section* section, char const* name, char const* value)
{
	if (section == NULL || name == NULL || value == NULL)
		return NULL;

	t_property* prop = create_property(name, value);

	list_insert_next(section->properties, NULL, prop);

	return prop;
}

t_section* find_section(t_ini* ini, char const* section)
{
	if (ini == NULL || section == NULL || ini->sections == NULL)
		return NULL;

	t_list_node* current = ini->sections->head;

	while (current != NULL)
	{
		t_section* sect = ((t_section*)current->data);
		if (sect != NULL)
			if (string_compare(sect->name, section) == 0)
				return (sect);
		current = current->next;
	}
	return NULL;
}

t_property* find_property(t_section* section, char const* name)
{
	if (section == NULL || name == NULL || section->properties == NULL)
		return NULL;

	t_list_node* current = section->properties->head;
	while (current != NULL)
	{
		if(string_compare(((t_property*)current->data)->name, name) == 0)
			return ((t_property*)current->data);
		current = current->next;
	}
	return NULL;
}
