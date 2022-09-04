#pragma once

#include<SDL.h>

#include"texture.h"

struct Interface {
	SDL_Rect hp1,
			 hp2;

	SDL_Rect meter1,
			 meter2;

	Texture timer;
};

void initInterface(Interface& interface);
void deInitInterface(Interface& interface);

void updateInterface(Interface& interface);
 
void drawInterface(const Interface& interface);