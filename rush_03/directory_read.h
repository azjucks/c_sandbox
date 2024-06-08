#ifndef __DIRECTORY_READ__
#define __DIRECTORY_READ__

#include "directory_tools.h"
#include "list_internal.h"

//if the person does not exist in the directory, add it and return it
t_person*	read_person(t_directory* directory, char** infos, char** attr);

//reads the directory and create a struct according to it
t_directory*	read_directory_file(char const* file_path);

#endif
