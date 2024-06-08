#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "snake.h"
#include "list_internal.h"
#include "game.h"
#include "sdl_utils.h"
#include "snake_events.h"
#include "item.h"

t_snake* snake_create(t_game* game)
{
	t_snake* snake = malloc(sizeof(t_snake));

	if (snake == NULL)
		return NULL;

	snake_init(snake, game);

	return snake;
}

void snake_init(t_snake* snake, t_game* game)
{
	if (snake == NULL)
		return;

	snake->size = 3;
	snake->direction = E_RIGHT;
	snake->velocity = 1;
	snake->is_shielded = false;


	SDL_Surface* surface = IMG_Load("media/snake_tileset.png");
	if (surface == NULL)
		printf("Surface null\n");

	snake->tileset = utils_load_texture(game->renderer, surface);

	SDL_FreeSurface(surface);


	snake->body_parts = list_create();
	list_init(snake->body_parts, NULL, NULL);

	snake_first_init(snake);
}

void snake_first_init(t_snake* snake)
{
	list_insert_next(snake->body_parts,
					NULL, snake_init_body_part(E_HEAD, START_POS_X, START_POS_Y));
	int pos_x = START_POS_X;
	int pos_y = START_POS_Y + BODY_PART_SIZE;
	list_insert_next(snake->body_parts,
					snake->body_parts->tail,
					snake_init_body_part(E_BODY, pos_x, pos_y));
	pos_x += BODY_PART_SIZE;
	list_insert_next(snake->body_parts,
					snake->body_parts->tail,
					snake_init_body_part(E_TAIL, pos_x, pos_y));
}

t_snake_body_part* snake_init_body_part(int part_index, int pos_x, int pos_y)
{
	t_snake_body_part* body_part = malloc(sizeof(t_snake_body_part));

	body_part->pos_x = pos_x;
	body_part->pos_y = pos_y;
	body_part->index_ = part_index;
	body_part->direction = E_RIGHT;

	int w = 64, h = 64;
	int r = 0, c = 0;

	t_tile* tile = malloc(sizeof(t_tile));
	tile->width = w;
	tile->height = h;
	tile->row = r;
	tile->column = c;


	body_part->tile = tile;


	return body_part;
}

void snake_destroy(t_snake* snake)
{
	if (snake == NULL)
		return;

	snake->size = 3;
	list_destroy(&snake->body_parts);
	SDL_DestroyTexture(snake->tileset);
	free(snake);
}
void snake_divide_half(t_snake* snake)
{
	if (snake == NULL)
		return;

	int half_size = snake->size / 2;

	half_size = half_size < 3 ? 3 : half_size;

	int i = 0;

	t_list_node* snake_node = snake->body_parts->head;

	while (snake_node != NULL && i < half_size)
	{
		snake_node = snake_node->next;
		i++;
	}

	if (snake != NULL)
	{
		t_list_node* next_node = snake_node->next;
		snake_node->next = NULL;
		snake->body_parts->tail = snake_node;
		snake->size = half_size;

		while (next_node != NULL)
		{
			t_list_node* temp = next_node->next;
			free(next_node);
			next_node = temp;
		}
	}

}
void snake_move_body(t_snake* snake)
{
	t_list_node* current = snake->body_parts->tail;

	do
	{
		t_snake_body_part* part = (t_snake_body_part*)current->data;
		t_snake_body_part* prev_part = (t_snake_body_part*)current->prev->data;
		
		part->pos_x = prev_part->pos_x;
		part->pos_y = prev_part->pos_y;
		current = current->prev;
	}
	while (current->prev != NULL);
}

void snake_update(t_game* game, t_snake* snake)
{
	snake_move_body(snake);
	switch (snake->direction)
	{
		case E_UP:
			((t_snake_body_part*)snake->body_parts->head->data)->pos_y -= BODY_PART_SIZE;
			break;
		case E_DOWN:
			((t_snake_body_part*)snake->body_parts->head->data)->pos_y += BODY_PART_SIZE;
			break;
		case E_RIGHT:
			((t_snake_body_part*)snake->body_parts->head->data)->pos_x += BODY_PART_SIZE;
			break;
		case E_LEFT:
			((t_snake_body_part*)snake->body_parts->head->data)->pos_x -= BODY_PART_SIZE;
			break;
		default:;
	}
	snake_check_collision(game, snake);
}

void snake_event_handler(t_snake* snake, const SDL_Event* event)
{
	(void) snake;
	(void) event;
}

void snake_check_collision(t_game* game, t_snake* snake)
{
	t_snake_body_part* snake_head = (t_snake_body_part*)snake->body_parts->head->data;

	if (snake_head->pos_x >= PLAYABLE_AREA_WIDTH ||
		snake_head->pos_x <= 0 ||
		snake_head->pos_y >= PLAYABLE_AREA_HEIGHT ||
		snake_head->pos_y <= 0)
	{
		game->lost = true;
	}

	t_list_node* item_node = game->items->items_list->head;

	while (item_node != NULL)
	{
		t_item* item = (t_item*)item_node->data;
		if (snake_head->pos_x == item->pos_x &&
			snake_head->pos_y == item->pos_y)
		{
			snake_collide_event(game, E_ITEM_COLLIDE, snake, item_node);
			return;
		}

		item_node = item_node->next;
	}
	t_list_node* node_body_part = snake->body_parts->head->next;
	while (node_body_part != NULL)
	{
		t_snake_body_part* body_part = (t_snake_body_part*)node_body_part->data;

		if (snake_head->pos_x == body_part->pos_x &&
			snake_head->pos_y == body_part->pos_y)
		{
			snake_collide_event(game, E_BODY_COLLIDE, snake, item_node);
			return;
		}
		node_body_part = node_body_part->next;
	}
}

void snake_update_head_sprite(t_list_node* node, t_snake_body_part* part)
{
	if (node->next != NULL)
	{
		// HEAD
		t_snake_body_part* other_part = (t_snake_body_part*)node->next->data;
		
		if (other_part->pos_y == part->pos_y)
		{
			part->tile->row = other_part->pos_x > part->pos_x ? 1 : 0;
			part->tile->column = other_part->pos_x > part->pos_x ? 3 : 4;
		} 
		else
		{
			part->tile->row = other_part->pos_y > part->pos_y ? 0 : 1;
			part->tile->column = other_part->pos_y > part->pos_y ? 3 : 4;
		}
	} 
	else {
		// TAIL
		t_snake_body_part* other_part = (t_snake_body_part*)node->prev->data;
		
		if (other_part->pos_y == part->pos_y)
		{
			part->tile->row = other_part->pos_x > part->pos_x ? 2 : 3;
			part->tile->column = other_part->pos_x > part->pos_x ? 4 : 3;
		}
		else
		{
			part->tile->row = other_part->pos_y > part->pos_y ? 3 : 2;
			part->tile->column = other_part->pos_y > part->pos_y ? 4 : 3;
		}
	}
}

void snake_update_body_part_sprite(t_list_node* node, t_snake_body_part* part)
{
	if (node->prev == NULL || node->next == NULL)
		return snake_update_head_sprite(node, part);

	t_snake_body_part* prev_part = (t_snake_body_part*)node->prev->data;
	t_snake_body_part* next_part = (t_snake_body_part*)node->next->data;
	if (prev_part->pos_x < part->pos_x)
	{
		if (next_part->pos_x == part->pos_x)
		{
			part->tile->row = next_part->pos_y > part->pos_y ? 0 : 2;
			part->tile->column = 2;
		}
		else
		{
			part->tile->row = 0;
			part->tile->column = 1;
		}
	}
	else if (prev_part->pos_x > part->pos_x)
	{
		if (next_part->pos_x == part->pos_x)
		{
			part->tile->row = next_part->pos_y > part->pos_y ? 0 : 1;
			part->tile->column = 0;
		}
		else
		{
			part->tile->row = 0;
			part->tile->column = 1;
		}
	}
	else if (prev_part->pos_y < part->pos_y)
	{
		if (next_part->pos_y != part->pos_y)
		{
			part->tile->row = 1;
			part->tile->column = 2;
		}
		else
		{
			part->tile->row = next_part->pos_x < part->pos_x ? 2 : 1;
			part->tile->column = next_part->pos_x < part->pos_x ? 2 : 0;
		}
	}
	else if (prev_part->pos_y > part->pos_y)
	{
		if (next_part->pos_y != part->pos_y)
		{
			part->tile->row = 1;
			part->tile->column = 2;
		}
		else
		{
			part->tile->row = next_part->pos_x < part->pos_x ? 0 : 0;
			part->tile->column = next_part->pos_x < part->pos_x ? 2 : 0;
		}
	}
}

void snake_render_part(t_game* game, void* node_body_part)
{
	t_list_node* node = (t_list_node*)node_body_part;
	t_snake_body_part* part = (t_snake_body_part*)node->data;
	
	snake_update_body_part_sprite(node, part);
	
	utils_render_cpy(game, game->snake, part);
}

void snake_render(t_game* game, t_snake* snake)
{
	list_foreach(snake->body_parts, &snake_render_part, game);
}
