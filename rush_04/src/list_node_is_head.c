#include <stdbool.h>
#include <stdlib.h>

#include "list_internal.h"


bool list_node_is_head(t_list const* list, t_list_node const* node)
{
	if (list == NULL || node == NULL)
		return false;

	if (list->head == node)
		return true;
	
	return false;
}
