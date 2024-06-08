#ifndef __ITEM__
#define __ITEM__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl_utils.h"
#include "list_internal.h"


typedef enum item_
{
	E_APPLE = 160,
	E_SHIELD = 105,
	E_CAPS = 42,
	E_CHRONO_MORE = 137,
	E_CHRONO_LESS = 138
}e_item;

typedef struct s_items
{
	SDL_Texture* tileset;
	t_list* items_list;
}t_items;

typedef struct s_item
{
	t_tile* tile;
	int pos_x;
	int pos_y;
	e_item item_;
}t_item;

t_items* items_create(t_game* game);

void items_init(t_game* game, t_items* items);

void items_destroy(t_items* items);

void items_first_init(t_items* items);

t_item* item_init(e_item item_index, int pos_x, int pos_y);

void insert_random_item(t_game* game, t_list_node* item_node, t_item* item);

void item_used(t_game* game, t_list_node* item_node);

void item_render(t_game* game, void* node_item);

void items_render(t_game* game, t_items* items);

#endif
