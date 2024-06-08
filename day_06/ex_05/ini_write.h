#ifndef __INI_WRITE__
#define __INI_WRITE__

#include <stdio.h>
#include <stdlib.h>

#include "list_internal.h"
#include "ini.h"
#include "ini_tools.h"
#include "parse_file.h"
#include "ini_read.h"
#include "string_duplicate.h"

char const* get_property(t_ini* ini, char const* section_name, char const* name);

void set_property(t_ini* ini, char const* section_name, char const* name, char const* value);

void write_ini_file(char const* file_path, t_ini* ini);

#endif
