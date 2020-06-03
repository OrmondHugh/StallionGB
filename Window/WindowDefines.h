#ifndef STALLIONGB_WINDOWDEFINES_H
#define STALLIONGB_WINDOWDEFINES_H

#include "SDL.h"

SDL_Window *CreateWindow(char title[], int width, int height);
SDL_Renderer *CreateRenderer(SDL_Window *window);

#endif //STALLIONGB_WINDOWDEFINES_H
