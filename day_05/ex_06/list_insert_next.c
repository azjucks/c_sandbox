#include <stdlib.h>

#include "list_internal.h"


void list_insert_next(t_list* list, t_list_node* node, void* data)
{
	if (list == NULL)
		return;

	t_list_node* new_node;

	new_node = malloc(sizeof(t_list_node));

	if (new_node == NULL)
		return;

	new_node->data = data;

	if (node == NULL)
	{
		new_node->next = list->head;
		list->head = new_node;
		if(list->head->next == NULL)
			list->tail = new_node;
	}
	else
	{
		if (node == list->tail)
			list->tail = new_node;

		new_node->next = node->next;
		node->next = new_node;
	}
	++(list->size);
}
