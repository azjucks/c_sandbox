#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_events.h>

#include "snake_events.h"
#include "game.h"
#include "snake.h"
#include "item.h"
#include "list_internal.h"

void snake_use_item_event(t_game* game, t_snake* snake, t_list_node* item_node)
{
	t_item* item = (t_item*)item_node->data;

	switch (item->item_)
	{
		case E_APPLE:
			list_insert_next(snake->body_parts, snake->body_parts->tail,
							snake_init_body_part(E_BODY,
							((t_snake_body_part*)snake->body_parts->tail)->pos_x,
							((t_snake_body_part*)snake->body_parts->tail)->pos_y));
			++game->score;
			break;
		case E_CHRONO_MORE:
			snake->velocity *= 1.05f;
			break;
		case E_CHRONO_LESS:
			snake->velocity /= 1.05f;
			break;
		case E_CAPS:
			snake_divide_half(snake);
			break;
		case E_SHIELD:
			snake->is_shielded = true;
			break;
		default:;
	}
	item_used(game, item_node);
}

void snake_collide_event(t_game* game, e_collision_type type, t_snake* snake, t_list_node* item_node)
{
	switch (type)
	{
		case E_ITEM_COLLIDE:
			snake_use_item_event(game, snake, item_node);
			break;
		case E_BODY_COLLIDE:
			game->lost = true;
			break;
		case E_WALL_COLLIDE:
			game->lost = true;
			break;
		default:;
	}
}

void snake_move_event(t_game* game, t_snake* snake, t_move_inputs* inputs, const SDL_Event* event)
{
	if (snake == NULL || inputs == NULL || event == NULL)
		return;

	if (event->type == SDL_KEYDOWN)
	{
		snake_keydown_event(snake, inputs, event);
		switch (event->key.keysym.scancode)
		{
			case SDL_SCANCODE_A:
				snake_use_item_event(game, snake, game->items->items_list->tail);
				break;
			case SDL_SCANCODE_P:
				game->paused = !game->paused;
				break;
			default:;
		}

	}
}

void snake_keydown_event(t_snake* snake, t_move_inputs* inputs, const SDL_Event* event)
{
	switch (event->key.keysym.scancode)
	{
		case SDL_SCANCODE_RIGHT:
			if (snake->direction != E_LEFT)
			{
			snake->direction = E_RIGHT;
			inputs->right = true;
			inputs->left = false;
			inputs->up = false;
			inputs->down = false;
			}
			break;

		case SDL_SCANCODE_LEFT:
			if (snake->direction != E_RIGHT)
			{
			snake->direction = E_LEFT;
			inputs->right = false;
			inputs->left = true;
			inputs->up = false;
			inputs->down = false;
			}
			break;

		case SDL_SCANCODE_UP:
			if (snake->direction != E_DOWN)
			{
				snake->direction = E_UP;
				inputs->right = false;
				inputs->left = false;
				inputs->up = true;
				inputs->down = false;
			}
			break;

		case SDL_SCANCODE_DOWN:
			if (snake->direction != E_UP)
			{
				snake->direction = E_DOWN;
				inputs->right = false;
				inputs->left = false;
				inputs->up = false;
				inputs->down = true;
			}
			break;

		default:;
	}
}
