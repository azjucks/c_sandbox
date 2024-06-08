#ifndef __INI__
#define __INI__

#include "list_internal.h"

typedef struct s_property
{
	char* name;
	char* value;
}t_property;

typedef struct s_section
{
	char* name;
	t_list* properties;
}t_section;

typedef struct s_ini
{
	t_list* sections;
}t_ini;

void destroy_property(void* property);

t_property* create_property(char const* name, char const* value);

void destroy_section(void* section);

t_section* create_section(char const* name);

void destroy_ini(void* ini);

t_ini* create_ini();

#endif
