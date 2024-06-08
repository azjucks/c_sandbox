#ifndef __SNAKE__
#define __SNAKE__

#define BODY_PART_SIZE 32

#include "list_internal.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "sdl_utils.h"

typedef struct s_move_inputs t_move_inputs;

typedef union SDL_Event SDL_Event;

typedef enum direction
{
	E_UP=3,
	E_RIGHT=4,
	E_LEFT=8,
	E_DOWN=9
}e_direction;

typedef enum index
{
	E_BODY=2,
	E_HEAD=0,
	E_TAIL=10
}e_index;

typedef struct s_game_inputs t_game_inputs;

typedef struct s_game t_game;

typedef struct s_snake
{
	SDL_Texture* tileset;
	int size;
	bool is_shielded;
	float velocity;
	e_direction direction;
	t_list* body_parts;
}t_snake;

typedef struct s_snake_body_part
{
	t_tile* tile;
	int pos_x;
	int pos_y;
	e_index index_;
	e_direction direction;
}t_snake_body_part;

typedef struct s_snake_event
{
	void* event;
}t_snake_event;

t_snake*	snake_create(t_game* game);

void	snake_init(t_snake* snake, t_game* game);

void	snake_destroy(t_snake* snake);

void	snake_first_init(t_snake* snake);

t_snake_body_part*	snake_init_body_part(int part_index, int pos_x, int pos_y);

void snake_move_body(t_snake* snake);

void snake_divide_half(t_snake* snake);

void snake_check_collision(t_game* game, t_snake* snake);

void	snake_update(t_game* game, t_snake* snake);

void	snake_event_handler(t_snake* snake, const SDL_Event* event);

void snake_update_head_sprite(t_list_node* node, t_snake_body_part* part);

void snake_update_body_part_sprite(t_list_node* node, t_snake_body_part* part);

void	snake_render_part(t_game* game, void* body_part);

void	snake_render(t_game* game, t_snake* snake);

#endif
