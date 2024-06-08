#ifndef __DIRECTORY__
#define __DIRECTORY__

#include <stdlib.h>
#include <stdio.h>

#include "list_internal.h"
#include "string_duplicate.h"


typedef struct s_person
{
	char* first_name;
	char* last_name;
	char* login;
	char* function;
	char** attributes;

}t_person;

typedef struct s_directory
{
	t_list* people;
}t_directory;

void	destroy_person(void* person);

t_person*	create_person(char const* first_name, char const* last_name,
												char const* login, char const* function,
												char** attributes);

void	destroy_directory(void* directory);

t_directory*	create_directory();

#endif
