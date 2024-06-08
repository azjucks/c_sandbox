#include <stdio.h>
#include <stdlib.h>

#include "ini.h"
#include "string_duplicate.h"


void destroy_property(void* property)
{
	if (property == NULL)
		return;

	t_property* prop = (t_property*)property;

	if (prop->name != NULL)
		free(prop->name);
	
	if (prop->value != NULL)
		free(prop->value);

	free(prop);
}

t_property* create_property(char const* name, char const* value)
{
	if (name == NULL || value == NULL)
		return NULL;

	t_property* prop = malloc(sizeof(t_property));

	if (prop == NULL)
		return NULL;

	prop->name = string_duplicate(name);
	prop->value = string_duplicate(value);

	return prop;
}

void destroy_section(void* section)
{
	if (section == NULL)
		return;

	
	t_section* sect = (t_section*)section;

	if (sect->properties != NULL)
	{
		/*t_list_node* prop = sect->properties->head;

		while (prop != NULL)
		{
			t_list_node* temp = prop->next;
			sect->properties->destroy(prop->data);;
			prop = temp;
		}*/

		list_destroy(&sect->properties);
	}

	free(sect->name);
	free(sect);
}

t_section* create_section(char const* name)
{
	t_section* sect = malloc(sizeof(t_section));
	
	if (sect == NULL)
		return NULL;

	sect->properties = list_create();
	list_init(sect->properties, NULL, destroy_property);

	if (sect->properties == NULL)
		return NULL;

	sect->name = string_duplicate(name);

	return sect;
}

void destroy_ini(void* ini)
{
	if (ini == NULL)
		return;
	
	t_ini* ini_ = (t_ini*)ini;

	if (ini_->sections != NULL)
	{
		/*t_list_node* current = ini_->sections->head;
		while (current != NULL)
		{
			t_list_node* temp = current->next;
			ini_->sections->destroy(current->data);
			current = temp;
		}*/
		list_destroy(&ini_->sections);
	}
	free(ini_);
}

t_ini* create_ini()
{
	t_ini* ini = malloc(sizeof(t_ini));

	if (ini == NULL)
		return NULL;

	ini->sections = list_create();
	list_init(ini->sections, NULL, destroy_section);

	return ini;
}
