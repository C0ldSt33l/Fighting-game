#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#define FRAME_COUNT 60.0f;

#define WINDOW_MIN_RESOLUTION 600
#define WINDOW_MAX_RESOLUTION 1920

extern SDL_Window* WINDOW;
extern SDL_Rect BOARD;

extern SDL_Renderer* RENDER;

extern int WINDOW_WIDTH,
		   WINDOW_HEIGHT;

void deInit(int error);
void init();