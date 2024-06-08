#include <stdlib.h>

#include "list_internal.h"


void list_destroy(t_list** list)
{
	if (list == NULL || *list == NULL)
		return;

	if ((*list)->head != NULL)
	{
		while((*list)->head != NULL)
		{
			t_list_node* current = (*list)->head;

			if (current->data != NULL)
			{
				if ((*list)->destroy != NULL)
					(*list)->destroy(current->data);
			}
			(*list)->head = (*list)->head->next;
			free(current);
		}
	}

	free(*list);

	*list = NULL;
}
