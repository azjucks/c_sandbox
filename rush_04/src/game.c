#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "sdl_utils.h"
#include "snake.h"
#include "item.h"
#include "game_inputs.h"
#include "list_internal.h"
#include "snake_events.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

t_game* game_create(SDL_Renderer* renderer)
{
	if (renderer == NULL)
		return NULL;

	t_game* game = malloc(sizeof(t_game));
	
	game_init(game, renderer);

	SDL_assert(game != NULL);

	char* img_path = "media/bg.png";

	game->surface = IMG_Load(img_path);

	game->sprite_background = utils_load_texture(renderer, game->surface);

	return game;
}

void game_init(t_game* game, SDL_Renderer* renderer)
{
	if (game == NULL)
		return;

	game->sprite_background = NULL;
	game->surface = NULL;
	game->renderer = renderer;
	game->width = PLAYABLE_AREA_WIDTH;
	game->height = PLAYABLE_AREA_HEIGHT;
	game->obstacles = list_create();
	list_init(game->obstacles, NULL, NULL);
	game->items = items_create(game);
	game->snake = snake_create(game);
	game->score = 0;
	game->time = 0;
	game->paused = false;
	game->lost = false;
}

void game_destroy(t_game* game)
{
	if (game == NULL)
		return;
	SDL_DestroyTexture(game->sprite_background);
	list_destroy(&(game->obstacles));
	items_destroy(game->items);
	snake_destroy(game->snake);

	SDL_FreeSurface(game->surface);
	free(game);
}

void game_render(t_game* game, SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, game->sprite_background, NULL, &(SDL_Rect){0, 0, game->width, game->height});
	items_render(game, game->items);
	snake_render(game, game->snake);
}

void game_update(t_game* game)
{
	snake_update(game, game->snake);
}

void game_run(SDL_Window* window, SDL_Renderer* renderer)
{
	if (window == NULL || renderer == NULL)
		return;

	t_game* game = game_create(renderer);

	t_move_inputs inputs = {};

	bool running = true;
	
	while (running)
	{
		
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				snake_move_event(game, game->snake, &inputs, &event);
				switch (event.type)
				{
					case SDL_QUIT:
						running = false;
						break;
					default:;
				}
			}
		}
		if(!game->paused && !game->lost)
		{
			game_update(game);
		}
		SDL_RenderClear(renderer);

		game_render(game, renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(TIMESTEP / game->snake->velocity);
	}

	game_destroy(game);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
