#include <stdlib.h>

#include "list_internal.h"


void list_remove_next(t_list* list, t_list_node* node, void** data)
{
	if (list == NULL)
		return;
	
	if (node == NULL && list->head != NULL)
	{
		*data = list->head->data;
		t_list_node* temp  = list->head->next;
		
		//if (list->destroy != NULL)
			//list->destroy(list->head->data);

		free(list->head);
		
		list->head = temp;
		--(list->size);

		if (list->size <= 1)
			list->tail = list->head;

		return;
	}

	if(list->head == NULL)
		return;

	t_list_node* next_node = node->next;

	if (next_node == NULL)
		return;

	if(next_node == list->tail)
		list->tail = node;

	*data = next_node->data;

	node->next = next_node->next;

	free(next_node);

	--(list->size);
}
