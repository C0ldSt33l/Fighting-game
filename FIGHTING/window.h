#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>


// WINDOW CONFIG
#define WINDOW_FRAME_COUNT 60.0f
#define WINDOW_DELAY       1000 / WINDOW_FRAME_COUNT

#define WINDOW_MIN_RESOLUTION 600
#define WINDOW_MAX_RESOLUTION 1920


// VARS
extern SDL_Window* WINDOW;
extern SDL_Rect BOARD;

extern SDL_Renderer* RENDER;

extern int WINDOW_WIDTH,
           WINDOW_HEIGHT;


// FUNCTIONS
void deInit(int error);
void init();