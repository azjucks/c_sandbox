#include <stdlib.h>
#include <stdio.h>

#include "list_internal.h"

void list_sort(t_list* list)
{
	if (list == NULL || list->head == NULL)
		return;

	int sw;
	t_list_node* current_node;
	t_list_node* prev_node = NULL;
	t_list_node* next_node = NULL;

	do
	{
		sw = 0;
		current_node = list->head;
		next_node = current_node->next;
		prev_node = NULL;
		while (next_node != NULL && current_node != list->tail)
		{
			if (list->compare(current_node->data, next_node->data) >= 0)
			{
				if (current_node == list->head)
					list->head = next_node;

				if (next_node == list->tail)
					list->tail = current_node;

				void* temp = next_node->next;
				next_node->next = current_node;
				current_node->next = temp;

				if (prev_node != NULL)
					prev_node->next = next_node;

				prev_node = next_node;
				sw = 1;
			}
			else
			{
				prev_node = current_node;
				current_node = next_node;
			}
			next_node = current_node->next;
		}
	}
	while (sw);

}
