// Tutorial:
// lazyfoo.net/tutorials/SDL/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Window
SDL_Window* window = NULL;

// Window content (or surface)
SDL_Surface* screenSurface = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL initialize fail, error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window creation error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}


int main()
{

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL
	SDL_Quit();

	return 0;
}
