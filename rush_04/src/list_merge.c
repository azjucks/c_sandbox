#include <stdlib.h>

#include "list_internal.h"

t_list* list_merge(t_list* list1, t_list* list2)
{
	if (list1 == NULL && list2 == NULL)
		return NULL;

	t_list* list3 = list_create();
	list_init(list3, list1->compare, list1->destroy);

	if (list1 != NULL && list2 == NULL)
	{
		list3->head = list_head(list1);
		list3->tail = list_tail(list1);
		list3->size = list_size(list1);
		list1->size = 0;
		list1->head = NULL;
		list1->tail = NULL;
	}
	else if (list1 == NULL && list2 != NULL)
	{
		list3->head = list_head(list2);
		list3->tail = list_tail(list2);
		list3->size = list_size(list2);;
		list2->size = 0;
		list2->head = NULL;
		list2->tail = NULL;
	}
	else
	{
		list3->head = list_head(list1);
		list3->tail = list_tail(list1);
		list3->tail->next = list_head(list2);
		list3->tail = list_tail(list2);
		list3->size = (list_size(list1) + list_size(list2));

		list1->size = 0;
		list2->size = 0;
		list1->head = NULL;
		list1->tail = NULL;
		list2->head = NULL;
		list2->tail = NULL;
	}

	return list3;
}
