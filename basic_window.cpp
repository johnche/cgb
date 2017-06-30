// Tutorial:
// lazyfoo.net/tutorials/SDL/

#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main()
{
	// Window
	SDL_Window* window = NULL;

	// Window content (or surface)
	SDL_Surface* screenSurface = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL initialize fail, error: %s\n", SDL_GetError());
	}
	else
	{
		// Get surface
		screenSurface = SDL_GetWindowSurface(window);

		// Draw on surface
		SDL_FillRect(
				screenSurface,
				NULL,
				SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));

		// Update surface
		SDL_UpdateWindowSurface(window);

		// Wait
		SDL_Delay(2000);
	}

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL
	SDL_Quit();

	return 0;
}
