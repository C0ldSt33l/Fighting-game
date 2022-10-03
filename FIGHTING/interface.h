#pragma once

#include<SDL.h>

#include"texture.h"

// INTERFACE CONFIGS
#define HEALTH_RECT_WIDTH WINDOW_WIDTH / 5


// STRUCTS
struct Interface {
    SDL_Rect health1,
             health2;

    SDL_Rect meter1,
             meter2;

    int time = 0;
    Texture timer;
};


// FUNCTIONS
void initInterface(Interface& interface);
void deInitInterface(Interface& interface);

void updateHealth(SDL_Rect& rect, int playerHealth, int maxPlayerHealth);
void updateInterface(Interface& interface, int health1, int maxHealth1,
                                           int health2, int maxHealth2);
SDL_Rect createOutline(SDL_Rect rect);
void drawInterface(const Interface& interface);
