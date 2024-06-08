#include <stdlib.h>

#include "list_internal.h"

void list_reverse(t_list* list)
{
	if(list == NULL)
		return;

	t_list_node* current = list_head(list);
	t_list_node* prev = NULL;
	list->tail = list_head(list);
	
	while(current != NULL)
	{
		t_list_node* temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	list->head = prev;
}
