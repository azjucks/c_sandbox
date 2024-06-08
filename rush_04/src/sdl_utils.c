#include <stdio.h>
#include <stdlib.h>

#include "sdl_utils.h"
#include "game.h"
#include "snake.h"
#include "item.h"


void utils_init_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO != 0))
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return;
	}

	*window = SDL_CreateWindow("snake",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);
	if (*window == NULL)
	{
		printf("Error creating window: %s\n", SDL_GetError());
		return;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (*renderer == NULL)
	{
		printf("Error creating renderer: %s\n", SDL_GetError());
		return;
	}
}

SDL_Texture* utils_load_texture(SDL_Renderer* renderer, SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(
							renderer, surface);

	return texture;
}

void utils_render_cpy(t_game* game, void* master_object, void* object)
{
	if (game == NULL || master_object == NULL || object == NULL)
		return;

	t_items* master_obj = (t_items*)master_object;
	t_item* obj = (t_item*)object;
	t_tile* object_tile = obj->tile;

	SDL_Rect src_rect = {object_tile->column * object_tile->width, object_tile->row * object_tile->height, object_tile->width, object_tile->height};
	SDL_Rect dst_rect = {obj->pos_x, obj->pos_y, 32, 32};

	SDL_RenderCopy(game->renderer, master_obj->tileset, &src_rect, &dst_rect);
}
