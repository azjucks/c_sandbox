#include <stdlib.h>

#include "list_internal.h"
#include <SDL2/SDL.h>

void list_foreach(t_list const* list, void (*action)(t_game*, void*), t_game* game)
{
	if (list == NULL || action == NULL)
		return;

	for (t_list_node* node = list->head; node != NULL; node = node->next)
	{
		action(game, node);
	}
}
