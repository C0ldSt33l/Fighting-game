#include<stdio.h>
#include"window.h"

SDL_Window* WINDOW   = NULL;
SDL_Rect BOARD = { 
    0, 0,
    WINDOW_WIDTH, WINDOW_HEIGHT - WINDOW_HEIGHT / 30
};

SDL_Renderer* RENDER = NULL;

int WINDOW_WIDTH  = WINDOW_MAX_RESOLUTION,
    WINDOW_HEIGHT = 1080;

void deInit(int error)
{
    if (RENDER) SDL_DestroyRenderer(RENDER);
    if (WINDOW) SDL_DestroyWindow(WINDOW);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(error);
}

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("Couldn't init SDL. Error: %s", SDL_GetError());
        deInit(1);
    }

    int res;
    if (!(res = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))) {
        printf("Couldn't init SDL_image. Error: %s", SDL_GetError());
        deInit(1);
    }
    if (res & IMG_INIT_PNG) printf("Initialized PNG library\n");
    if (res & IMG_INIT_JPG) printf("Initialized JPG library\n");

    if (TTF_Init()) {
        printf("Couldn't init SDL_ttf. Error: %s", SDL_GetError());
        deInit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
        printf("Couldn't init SDL_mixer. Error: %s", SDL_GetError());
        deInit(1);
    }

    WINDOW = SDL_CreateWindow("window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!WINDOW) {
        printf("Couldn't create window. Error: %s", SDL_GetError());
        deInit(1);
    }

    RENDER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
    if (!RENDER) {
        printf("Couldn't create render. Error: %s", SDL_GetError());
        deInit(1);
    }
}