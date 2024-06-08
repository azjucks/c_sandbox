#include <stdlib.h>

#include "commands.h"
#include "directory.h"
#include "directory_read.h"
#include "directory_write.h"
#include "directory_tools.h"
#include "parse_file.h"
#include "string_compare.h"
#include "list_internal.h"
#include "my_put_string.h"


void	exec_cmd(char* file_path, char* cmd, char** person_infos, char** person_attributes)
{
	if( file_path == NULL)
		return;

	if (string_compare(cmd, "display") == 0)
	{
		(void)person_attributes;
		(void)person_infos;
		t_directory* directory = read_directory_file(file_path);
		print_directory(directory);
		destroy_directory(directory);
	}
	else if (string_compare(cmd, "add") == 0)
	{
		t_directory* directory = read_directory_file(file_path);
		set_person(directory, person_infos, person_attributes);
		write_directory_file(file_path, directory);
		destroy_directory(directory);
	}
	else if (string_compare(cmd, "find") == 0)
	{
		t_directory* directory = read_directory_file(file_path);

		char* login = person_infos[0];

		t_person* person = find_person(directory, login);

		print_person(person);

		destroy_directory(directory);
	}
	else if (string_compare(cmd, "remove") == 0)
	{
		(void)person_attributes;
		t_directory* directory = read_directory_file(file_path);

		char* login = person_infos[2];

		t_person* person = find_person(directory, login);
		destroy_person(person);

		write_directory_file(file_path, directory);
		destroy_directory(directory);
	}
	else if (string_compare(cmd, "modify") == 0)
	{
		t_directory* directory = read_directory_file(file_path);

		char* login = person_infos[2];

		t_person* person = find_person(directory, login);
		char* a_name = NULL;
		char* a_value = NULL;
		parse_attribute(person_infos[0], &a_name, &a_value);

		if (string_compare(a_name, "first_name") == 0)
		{
			char* infos[5] = {a_value, person->last_name, 
											person->login, person->function, NULL};
			set_person(directory, infos, NULL);
		}

		if (string_compare(a_name, "last_name") == 0)
		{
			char* infos[5] = {person->first_name, a_value, 
											person->login, person->function, NULL};
			set_person(directory, infos, NULL);
		}

		if (string_compare(a_name, "login") == 0)
		{
			char* infos[5] = {person->first_name, person->last_name, 
											a_value, person->function, NULL};
			set_person(directory, infos, NULL);
		}

		if (string_compare(a_name, "function") == 0)
		{
			char* infos[5] = {person->first_name, person->last_name, 
											person->login, a_value, NULL};
			set_person(directory, infos, NULL);
		}
		free(a_name);
		free(a_value);

		destroy_person(person);

		write_directory_file(file_path, directory);
		destroy_directory(directory);
	}
	else
	{
		my_put_string("Invalid command.\nList of all available commands:\n	- display\n	- add\n	- remove\n	- find\n	- modify\n");
	}
}
