#ifndef __SNAKE_EVENT__
#define __SNAKE_EVENT__

#include <stdbool.h>

#include "game_inputs.h"

#include "item.h"

typedef struct s_snake t_snake;
typedef struct s_game t_game;

typedef union SDL_Event SDL_Event;

typedef struct s_move_inputs
{
	bool right;
	bool left;
	bool up;
	bool down;
}t_move_inputs;

typedef enum collision_type
{
	E_ITEM_COLLIDE,
	E_BODY_COLLIDE,
	E_WALL_COLLIDE
}e_collision_type;

void snake_use_item_event(t_game* game, t_snake* snake, t_list_node* item_node);

void snake_collide_event(t_game* game, e_collision_type type, t_snake* snake, t_list_node* item_node);

void snake_move_event(t_game* game, t_snake* snake, t_move_inputs* inputs, const SDL_Event* event);

void snake_keydown_event(t_snake* snake, t_move_inputs* inputs, const SDL_Event* event);

#endif
