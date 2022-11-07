#pragma once

#include<SDL_ttf.h>


// FUNCTIONS
int getFontSize(int width);
TTF_Font* loadFont(const char* file, int size);
void centerText(int& coord, int& size, int maxSize);