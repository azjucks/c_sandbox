#include <stdbool.h>
#include <stdlib.h>

#include "list_internal.h"


bool list_node_is_tail(t_list const* list, t_list_node const* node)
{
	if (list == NULL || node == NULL)
		return false;
	
	if (list->tail == node)
		return true;

	return false;
}
