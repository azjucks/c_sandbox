#include <stdlib.h>
#include <stdio.h>

#include "directory_read.h"
#include "parse_file.h"
#include "directory_tools.h"

t_person*	read_person(t_directory* directory, char ** infos, char** attr)
{
	if (directory == NULL || infos == NULL)
		return NULL;

	char* login = infos[2];

	t_person* person = find_person(directory, login);

	if (person != NULL)
		return NULL;

	person = add_person(directory, infos, attr);

	return person;
}

t_directory*	read_directory_file(char const* file_path)
{
	if (file_path == NULL)
		return NULL;

	t_directory* directory = create_directory();

	FILE* file = fopen(file_path, "rb");

	char* line = read_line(file);

	while (line != NULL)
	{
		char** line_infos = parse_line_infos(line);
		char** line_attr = parse_line_attributes(line);

		read_person(directory, line_infos, line_attr);
		free(line);

		int i = 0;

		if (line_infos != NULL)
		{
			while (line_infos[i] != NULL)
				free(line_infos[i++]);

			free(line_infos);
		}

		i = 0;
		if (line_attr != NULL)
		{
			while (line_attr[i] != NULL)
				free(line_attr[i++]);

			free(line_attr);
		}
		line = read_line(file);
	}
	free(line);

	fclose(file);

	return directory;
}
