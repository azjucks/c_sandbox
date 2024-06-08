#include <stdlib.h>

#include "list_internal.h"


void list_destroy(t_list** list)
{
	if (*list == NULL)
		return;

	if ((*list)->head != NULL)
	{
		while((*list)->head != NULL)
		{
			t_list_node* current = (*list)->head;
			(*list)->head = (*list)->head->next;
			free(current);
		}
	}

	free(*list);

	*list = NULL;
}
