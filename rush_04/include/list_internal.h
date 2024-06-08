#ifndef __LIST_INTERNAL__
#define __LIST_INTERNAL__

#include "list.h"


struct s_list_node
{
	void* data;
	struct s_list_node* prev;
	struct s_list_node* next;
};

typedef struct s_list_node t_list_node;

struct s_list
{
	unsigned int size;
	t_list_node* head;
	t_list_node* tail;
	int (*compare)(void*, void*);
	void (*destroy)(void*);
};

typedef struct s_list t_list;

int compare(void*, void*);

#endif
