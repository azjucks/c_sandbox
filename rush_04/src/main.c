#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "sdl_utils.h"
#include "game.h"

int main()
{
	srand(time(0));
	SDL_Renderer* renderer;
	SDL_Window* window;

	utils_init_window_and_renderer(&window, &renderer);

	game_run(window, renderer);

	return 0;
}
