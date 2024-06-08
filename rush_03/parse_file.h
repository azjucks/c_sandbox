#ifndef __PARSE_FILE__
#define __PARSE_FILE__

#include <stdbool.h>
#include <stdio.h>

int	read_char(FILE* file, char* pointer_c);

int	is_space(char c);

char*	sub_string(char const* str, unsigned int pos, unsigned int len);

char*	read_line(FILE* file);

bool	is_attribute(char const* str, int size);

int	parse_attribute(char const* str, char** a_name, char** a_value);

//parse the line and return an array of mandatory infos
char** parse_line_infos(char const* line);

//parse the line from after the informations and return
//an array of attributes
char** parse_line_attributes(char const* line);

#endif
