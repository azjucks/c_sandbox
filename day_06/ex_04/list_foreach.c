#include <stdlib.h>

#include "list_internal.h"


void list_foreach(t_list const* list, void (*action)(void*))
{
	if (list == NULL || action == NULL)
		return;

	for (t_list_node* node = list->head; node != NULL; node = node->next)
	{
		action(node->data);
	}
}
