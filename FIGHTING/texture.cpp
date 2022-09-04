#include<stdio.h>

#include"texture.h"

SDL_Surface* loadImage(const char* file) {

	SDL_Surface* surface = IMG_Load(file);
	if (!surface) {
		printf("Couldn't load image: %s. Error: %s\n", file, IMG_GetError());
		system("pause");
		deInit(1);
	}

	return surface;
}

Texture createTexture(const char* file) {
	
	SDL_Surface* surface = loadImage(file);

	Texture texture;
	texture.text = SDL_CreateTextureFromSurface(RENDER, surface);
	texture.dstrect.w = surface->w;
	texture.dstrect.h = surface->h;

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Surface* loadText(TTF_Font* font, const char* text, const SDL_Color& color) {

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (!surface) {
		printf("Couldn't create text: %s. Error: %s\n", text, SDL_GetError());
		system("pause");
		deInit(1);
	}

	return surface;
}

Texture createText(TTF_Font* font, const char* text, const SDL_Color& color) {
	
	SDL_Surface* surface = loadText(font, text, color);

	Texture texture;
	texture.text = SDL_CreateTextureFromSurface(RENDER, surface);
	texture.dstrect.w = surface->w;
	texture.dstrect.h = surface->h;

	SDL_FreeSurface(surface);

	return texture;
}