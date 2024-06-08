#include <stdlib.h>

#include "list_internal.h"


void* list_node_data(t_list_node const* node)
{
	if (node == NULL)
		return NULL;

	return node->data;
}
