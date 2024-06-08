#ifndef __GAME__
#define __GAME__

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

#define TIMESTEP 150

#define PLAYABLE_AREA_WIDTH 1024
#define PLAYABLE_AREA_HEIGHT 780

#define START_POS_X 128
#define START_POS_Y 128

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "list_internal.h"
#include "snake.h"
#include "item.h"
#include "sdl_utils.h"
#include "snake_events.h"

typedef struct s_game
{
	SDL_Texture* 	sprite_background;

	SDL_Surface*	surface;

	SDL_Renderer*	renderer;

	int				width, height;

	t_list* 		obstacles;
	t_items* 		items;

	t_snake* 		snake;

	int 			time;

	int				score;

	bool			paused;

	bool 			lost;
}t_game;

t_game* game_create(SDL_Renderer* renderer);

void game_init(t_game* game, SDL_Renderer* renderer);

void game_destroy(t_game* game);

void game_update(t_game* game);

void game_render(t_game* game, SDL_Renderer* renderer);

void game_run(SDL_Window* window, SDL_Renderer* renderer);

#endif
