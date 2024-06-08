#include <stdlib.h>
#include <stdio.h>

#include "directory_write.h"
#include "string_duplicate.h"

char const*	get_person(t_directory* directory, char* login)
{
	if (directory == NULL || login == NULL)
		return NULL;

	t_person* person = find_person(directory, login);

	if (person == NULL)
		return NULL;

	return person->login;
}

void	set_person(t_directory* directory, char** infos, char** attr)
{
	if (directory == NULL || infos == NULL)
		return;

	char* first_name = infos[0];
	char* last_name = infos[1];
	char* login = infos[2];
	char* function = infos[3];

	t_person* person = find_person(directory, login);
	if (person == NULL)
	{
		person = add_person(directory, infos, attr);
	}
	else
	{
		char* p_login = person->login;
		char* p_first_name = person->first_name;
		char* p_last_name = person->last_name;
		char* p_function = person->function;
		if(p_login != NULL)
			free(p_login);
		if(p_function != NULL)
			free(p_function);
		if(p_first_name != NULL)
			free(p_first_name);
		if(p_last_name != NULL)
			free(p_last_name);

		person->first_name = first_name;
		person->last_name = last_name;
		person->login = login;
		person->function = function;
	}
}

void	write_directory_file(char const* file_path, t_directory* directory)
{
	if (file_path == NULL || directory == NULL)
		return;

	FILE* file = fopen(file_path, "w");

	t_list_node* person_node = directory->people->head;

	while (person_node != NULL)
	{
		t_person* person = ((t_person*)person_node->data);
		fputs(person->first_name, file);
		fputc('|', file);
		fputs(person->last_name, file);
		fputc('|', file);
		fputs(person->login, file);
		fputc('|', file);
		fputs(person->function, file);
		fputc('|', file);
		int i = 0;
		if (person->attributes != NULL)
		{
			while (person->attributes[i] != NULL)
			{
				fputs(person->attributes[i++], file);
				fputc('|', file);
			}
		}
		fseek(file, -1L, SEEK_CUR);
		fputc('\n', file);
		person_node = person_node->next;
	}

	fseek(file, -1L, SEEK_CUR);
	fputc('\n', file);
	fclose(file);
}
