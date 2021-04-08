#pragma once
#ifndef COLORS_H_
#define COLORS_H_
#include <iostream>
#include <SDL.h>

struct {
	SDL_Color cyan = { 0, 255, 255, 255 };
	SDL_Color orange = { 255, 165, 0, 255 };
	SDL_Color yellow = { 255, 255, 0, 255 };
	SDL_Color purple = { 160, 32, 240, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };
	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color green = { 0, 255, 0, 255 };
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Color grey = { 24, 24, 24, 255 };
} COLOR;
//cyan I, yellow O, purple T, green S, blue J, red Z, orange L

#endif // !COLORS_H_