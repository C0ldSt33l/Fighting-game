#pragma once

#include"window.h"

struct Texture {
	SDL_Texture* text = NULL;

	SDL_Rect dstrect = { 0, 0, 0, 0 };
};

SDL_Surface* loadImage(const char* file);
Texture createTexture(const char* file);

SDL_Surface* loadText(TTF_Font* font, const char* text, const SDL_Color& color);
Texture createText(TTF_Font* font, const char* text, const SDL_Color& color);