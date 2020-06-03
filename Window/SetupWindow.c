#include <stdio.h>
#include "WindowDefines.h"

#include "SDL.h"

SDL_Window *CreateWindow(char title[], int width, int height) {
	SDL_Window *win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		printf("Failed to create window. Error: %s\n", SDL_GetError());
		SDL_Quit();
	}

	return win;
}
SDL_Renderer * CreateRenderer(SDL_Window *window) {
	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC removed for testing
	if (ren == NULL) {
		SDL_DestroyWindow(window);
		printf("Failed to create renderer. Error: %s\n", SDL_GetError());
		SDL_Quit();
	}

	return ren;
}