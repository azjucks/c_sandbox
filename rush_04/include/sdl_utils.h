#ifndef __SDL_UTILS__
#define __SDL_UTILS__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


typedef struct s_game t_game;

typedef struct s_tile
{
	int width, height;
	int row, column;
}t_tile;

void utils_init_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer);

SDL_Texture* utils_load_texture(SDL_Renderer* renderer, SDL_Surface* surface);

void utils_render_cpy(t_game* game, void* master_object, void* object);

#endif
