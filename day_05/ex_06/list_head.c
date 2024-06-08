#include <stdlib.h>

#include "list_internal.h"


t_list_node* list_head(t_list const* list)
{
	if (list == NULL)
		return NULL;
	
	return list->head;
}
