#include<stdio.h>

#include"texture.h"

SDL_Surface* loadImage(const char* file) {

    SDL_Surface* surface = IMG_Load(file);
    if (!surface) {
        printf("Couldn't load image: %s. Error: %s\n", file, IMG_GetError());
        deInit(1);
    }

    return surface;
}

SDL_Texture* createSdlTexture(const char* file) {

    SDL_Surface* surface = loadImage(file);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(RENDER, surface);
    SDL_FreeSurface(surface);

    return texture;
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

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text, color, WINDOW_WIDTH / 2);
    if (!surface) {
        printf("Couldn't create text: %s. Error: %s\n", text, SDL_GetError());
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