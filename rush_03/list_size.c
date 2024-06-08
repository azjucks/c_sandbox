#include <stdlib.h>

#include "list_internal.h"


unsigned int list_size(t_list const* list)
{
	if (list == NULL)
		return 0;

/*	unsigned int size = 0;

	t_list_node* current = list->head;
	
	while(current != NULL)
	{
		current = current->next;
		++size;
	}

	return size;*/
	return list->size;
}
