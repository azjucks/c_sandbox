#ifndef __INI_WRITE__
#define __INI_WRITE__

#include <stdio.h>
#include <stdlib.h>

#include "list_internal.h"
#include "directory.h"
#include "directory_tools.h"
#include "parse_file.h"
#include "directory_read.h"

//get the person in the directory according to its login
char const*	get_person(t_directory* directory, char* login);

void	set_person(t_directory* directory, char** infos, char** attr);

void	write_directory_file(char const* file_path, t_directory* directory);

#endif
