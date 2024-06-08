#include <stdlib.h>

#include "list_internal.h"


void list_init(t_list* list, int (*compare)(void*, void*),
							void (*destroy)(void*))
{
	if(list == NULL)
		return;

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->compare = compare;
	list->destroy = destroy;
}
