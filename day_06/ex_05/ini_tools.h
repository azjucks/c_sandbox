#ifndef __PRINT_PROPERTY__
#define __PRINT_PROPERTY__

#include "ini.h"

void print_property(void* property);

void print_section(void* section);

void print_ini(t_ini* ini);

t_section* add_section(t_ini* ini, char const* section);

t_property* add_property(t_section* section, char const* name, char const* value);

t_section* find_section(t_ini* ini, char const* section);

t_property* find_property(t_section* section, char const* name);

#endif
