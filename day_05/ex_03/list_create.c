#include <stdlib.h>

#include "list_internal.h"


t_list* list_create(void)
{
	t_list* list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return NULL;

	return list;
}
