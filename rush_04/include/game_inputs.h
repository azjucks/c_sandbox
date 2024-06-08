#ifndef __GAME_INPUTS__
#define __GAME_INPUTS__

#include <SDL2/SDL.h>

typedef union SDL_Event SDL_Event;

typedef struct s_game_inputs
{
	SDL_Scancode scancode;
	
	bool key_pressed;
	float delta_time;
}t_game_inputs;

void game_inputs_handler(t_game_inputs* inputs,
						const SDL_Event* event);

#endif
