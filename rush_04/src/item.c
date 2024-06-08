#include "item.h"
#include "game.h"
#include "snake.h"
#include "sdl_utils.h"

t_items* items_create(t_game* game)
{
	if (game == NULL)
		return NULL;

	t_items* items = malloc(sizeof(t_items));

	if (items == NULL)
		return NULL;
	items_init(game, items);

	return items;
}

void items_init(t_game* game, t_items* items)
{
	if (game == NULL || items == NULL)
		return;

	items->items_list = list_create();
	list_init(items->items_list, NULL, NULL);

	SDL_Surface* surface = IMG_Load("media/items_tileset.png");

	items->tileset = utils_load_texture(game->renderer, surface);

	SDL_FreeSurface(surface);

	items_first_init(items);
}

void items_destroy(t_items* items)
{
	list_destroy(&items->items_list);
	SDL_DestroyTexture(items->tileset);
	free(items);
}

int item_rand_pos_x(t_item* item)
{
	return item->tile->width * (rand() % (PLAYABLE_AREA_WIDTH/item->tile->width));
}

int item_rand_pos_y(t_item* item)
{
	return item->tile->height * (rand() % (PLAYABLE_AREA_HEIGHT/item->tile->height));
}

void items_first_init(t_items* items)
{
	t_item* item = item_init(E_APPLE, 0, 0);
	item->pos_x = item_rand_pos_x(item);
	item->pos_y = item_rand_pos_y(item);
	list_insert_next(items->items_list, NULL, item);
}

t_item* item_init(e_item item_index, int pos_x, int pos_y)
{
	t_item* item = malloc(sizeof(t_item));;
	if (item == NULL)
		return NULL;

	item->pos_x = pos_x;
	item->pos_y = pos_y;
	item->item_ = item_index;

	int max_line = 8;
	int w = 32;
	int h = 32;

	int r = item_index / max_line;
	int c = item_index % max_line;

	t_tile* tile = malloc(sizeof(t_tile));
	tile->width = w;
	tile->height = h;
	tile->row = r;
	tile->column = c;

	item->tile = tile;

	return item;
}

void item_used(t_game* game, t_list_node* item_node)
{
	t_item* item = (t_item*)item_node->data;

	if (item == NULL)
		return;

	if (item->item_ == E_APPLE)
	{
		list_insert_next(game->items->items_list, item_node,
						item_init(E_APPLE,
								item_rand_pos_x(item),
								item_rand_pos_y(item)));
	}
	insert_random_item(game, item_node, item);
	t_item* temp_item;
	list_remove_node(game->items->items_list, item_node, (void**)&temp_item);
}

void insert_random_item(t_game* game, t_list_node* item_node, t_item* item)
{
	int random = rand() % 10;

	e_item type = 1;

	switch (random)
	{
		case 0:
			type = E_CHRONO_MORE;
			break;
		case 1:
			type = E_CHRONO_LESS;
			break;
		case 2:
			type = E_SHIELD;
			break;
		case 3:
			type = E_CAPS;
			break;
		default:;
	}
	if (type != 1)
	{
	list_insert_next(game->items->items_list, item_node,
						item_init(type,
								item_rand_pos_x(item),
								item_rand_pos_y(item)));

	}
}

void item_render(t_game* game, void* node_item)
{
	t_list_node* node = (t_list_node*)node_item;
	t_item* item = (t_item*)node->data;

	utils_render_cpy(game, game->items, item);
}

void items_render(t_game* game, t_items* items)
{
	list_foreach(items->items_list, &item_render, game);
}
