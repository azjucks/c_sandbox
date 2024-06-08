#ifndef __LIST__
#define __LIST__


typedef struct s_list_node t_list_node;

typedef struct s_list t_list;

t_list *list_create(void);

void list_init(t_list* list, int (*compare)(void*, void*),
							void (*destroy)(void*));

void list_destroy(t_list** list);

#endif
