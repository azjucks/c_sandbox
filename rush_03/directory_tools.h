#ifndef __DIRECTORY_TOOLS__
#define __DIRECTORY_TOOLS__

#include "directory.h"
#include <stdlib.h>
#include <stdio.h>


void	print_person(void* person);

void	print_directory(t_directory* directory);

t_person*	add_person(t_directory* directory, char** person_infos, char** person_attributes);

t_person*	find_person(t_directory* directory, char* login);

#endif
