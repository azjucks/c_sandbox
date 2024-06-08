#include <stdlib.h>

#include "list_internal.h"


t_list_node* list_tail(t_list const* list)
{
	if (list == NULL)
		return NULL;
	
	return list->tail;
}
