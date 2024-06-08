#include <stdlib.h>
#include <stdbool.h>

#include "list_internal.h"

t_list_node* list_find_if(t_list const* list, bool (*predicate)(void*))
{
	if (list == NULL || predicate == NULL)
		return NULL;

	for (t_list_node* node = list->head; node != NULL; node = node->next)
	{
		bool cond = predicate(node->data);

		if (cond)
			return node;
	}
	return NULL;
}
