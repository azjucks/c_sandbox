#include "directory_tools.h"
#include "my_put_string.h"
#include "my_put_char.h"
#include "my_put_number.h"
#include "string_compare.h"
#include "parse_file.h"

void	print_person(void* person)
{
	if (person == NULL)
		return;
	
	t_person* pers = (t_person*) person;

	my_put_string("\n + name: ");
	my_put_string(pers->first_name);
	my_put_char(' ');
	my_put_string(pers->last_name);

	my_put_string("\n + login: ");
	my_put_string(pers->login);

	my_put_string("\n + function: ");
	my_put_string(pers->function);
	my_put_char('\n');

	if (pers->attributes == NULL)
		return;

	int i = 0;

	while (pers->attributes[i] != NULL)
	{
		char* attr_name = NULL;
		char* attr_value = NULL;
		int is_attr = parse_attribute(pers->attributes[i], &attr_name, &attr_value);
		if (is_attr == 1)
		{
			my_put_string(" + ");
			my_put_string(attr_name);
			my_put_string(": ");
			my_put_string(attr_value);
			my_put_char('\n');
		}
		if (attr_name != NULL)
			free(attr_name);

		if (attr_value != NULL)
			free(attr_value);

		++i;
	}

}

void	print_directory(t_directory* directory)
{
	if (directory == NULL)
		return;
	
	t_list_node* current = directory->people->head;

	int i = 0;
	while (current != NULL)
	{
		my_put_string("Entry ");
		my_put_number(i++);
		print_person(current->data);
		current = current->next;
	}
}

t_person*	add_person(t_directory* directory, char** person_infos, char** person_attributes)
{
	if (directory == NULL || person_infos == NULL)
		return NULL;

	t_person* person = create_person(person_infos[0], person_infos[1],
																	person_infos[2], person_infos[3],
																	person_attributes);

	list_insert_next(directory->people, NULL, person);

	return person;
}

t_person*	find_person(t_directory* directory, char* login)
{
	if (directory == NULL || login == NULL)
		return NULL;

	t_list_node* current = directory->people->head;
	
	while (current != NULL)
	{
		if (string_compare(((t_person*)current->data)->login, login) == 0)
			return ((t_person*)current->data);

		current = current->next;
	}
	return NULL;
}
