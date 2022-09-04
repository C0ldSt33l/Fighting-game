#include<stdio.h>

#include"font.h"
#include"menu.h"

int getFontSize(int width) {

	int fontDif = MENU_MAX_FONT_SIZE - MENU_MIN_FONT_SIZE,
		widthDif = WINDOW_MAX_RESOLUTION - WINDOW_MIN_RESOLUTION;

	return ((width - MENU_MIN_FONT_SIZE) / fontDif * widthDif + WINDOW_MIN_RESOLUTION) / 300;
}

TTF_Font* loadFont(const char* file) {
	TTF_Font* font = TTF_OpenFont(file, getFontSize(WINDOW_WIDTH));
	if (!font) {
		printf("Couldn't open font: %s. Error: %s\n", file, SDL_GetError());
		system("pause");
		deInit(1);
	}

	return font;
}