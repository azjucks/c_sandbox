#include <stdlib.h>

#include "list_internal.h"


void list_remove_node(t_list* list, t_list_node* node, void** data)
{
	if (list == NULL)
		return;

	if (list->head == NULL)
		return;

	if (node == NULL)
		return;

	t_list_node* next_node = node->next;

	t_list_node* prev_node = node->prev;

	if (next_node != NULL)
		next_node->prev = prev_node;

	t_list_node* current = list->head;

	t_list_node* current_prev = NULL;

	while (current != NULL && current != node)
	{
		current_prev = current;
		current = current->next;
	}

	if (current_prev != NULL)
		current_prev->next = next_node;

	if (node == list->head)
		list->head = next_node;

	if(node == list->tail)
		list->tail = prev_node;

	*data = next_node->data;

	free(node);

	--(list->size);
}
