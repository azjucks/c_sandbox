#include "directory.h"


void	destroy_person(void* person)
{
	if (person == NULL)
		return;
	
	t_person* pers = (t_person*)person;

	if (pers->first_name != NULL)
		free(pers->first_name);

	if (pers->last_name != NULL)
		free(pers->last_name);

	if (pers->login != NULL)
		free(pers->login);

	if (pers->function != NULL)
		free(pers->function);

	if (pers->attributes != NULL)
	{
		int i = 0;
		while (pers->attributes[i] != NULL)
			free(pers->attributes[i++]);
		free(pers->attributes);
	}
	
	free(pers);
}

t_person*	create_person(char const* first_name, char const* last_name,
												char const* login, char const* function,
												char** attributes)
{
	if (first_name == NULL || last_name == NULL || login == NULL ||
			function == NULL)
		return NULL;

	t_person* person = malloc(sizeof(t_person));

	if (person == NULL)
		return NULL;

	person->first_name = string_duplicate(first_name);
	person->last_name = string_duplicate(last_name);
	person->login = string_duplicate(login);
	person->function = string_duplicate(function);

	if (attributes == NULL)
	{
		person->attributes = NULL;
		return person;
	}

	int i = 0;

	while (attributes[i] != NULL)
		++i;

	person->attributes = malloc((i + 1) * sizeof(char*));
	person->attributes[i] = NULL;

	for (int j = 0; j < i; ++j)
	{
		person->attributes[j] = string_duplicate(attributes[j]);
	}

	return person;

}

void	destroy_directory(void* directory)
{
	if (directory == NULL)
		return;

	t_directory* dir = (t_directory*)directory;

	if (dir->people != NULL)
		list_destroy(&dir->people);
	
	free(dir);
}

t_directory*	create_directory()
{
	t_directory* directory = malloc(sizeof(t_directory));

	if (directory == NULL)
		return NULL;
	
	directory->people = list_create();
	list_init(directory->people, NULL, destroy_person);

	return directory;
}
