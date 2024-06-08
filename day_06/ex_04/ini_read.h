#ifndef __INI_READ__
#define __INI_READ__

#include "ini.h"
#include "ini_tools.h"
#include "parse_file.h"

t_section* read_section(t_ini* ini, char const* str);

t_property* read_property(t_ini* ini, char const* str, char const* section);

t_ini* read_ini_file(char const* file_path);

#endif
