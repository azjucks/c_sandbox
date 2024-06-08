#ifndef __LIST__
#define __LIST__

#include <stdbool.h>


typedef struct s_list_node t_list_node;

typedef struct s_list t_list;

t_list *list_create(void);

void list_init(t_list* list, int (*compare)(void*, void*),
							void (*destroy)(void*));

void list_destroy(t_list** list);

void list_insert_next(t_list* list, t_list_node* node, void* data);

void list_remove_next(t_list* list, t_list_node* node, void** data);

bool list_node_is_head(t_list const* list, t_list_node const* node);

bool list_node_is_tail(t_list const* list, t_list_node const* node);

t_list_node* list_head(t_list const* list);

t_list_node* list_tail(t_list const* list);

unsigned int list_size(t_list const* list);

#endif
