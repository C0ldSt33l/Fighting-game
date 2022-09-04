#include<stdio.h>

#include"menu.h"
#include"font.h"
#include"sound.h"

SDL_Color ACTIVE_BUTTON_COLOR = { 255, 0, 0, 255 };
SDL_Color BUTTON_COLOR		  = { 0, 0, 0, 255 };

void setButtonCoords(Texture& button, int number) {

	button.dstrect.x = (WINDOW_WIDTH - button.dstrect.w) / 2;
	button.dstrect.y = MENU_BUTTON_START_Y + MENU_BUTTON_DISTANCE * number;
}

void setButtons(Texture* array, TTF_Font* font) {

	array[0] = createText(font, MENU_OPTIONS[0], ACTIVE_BUTTON_COLOR);
	setButtonCoords(array[0], 0);
	for (int i = 1; i < MENU_BUTTON_COUNT; i++) {
		
		array[i] = createText(font, MENU_OPTIONS[i], BUTTON_COLOR);
		setButtonCoords(array[i], i);
	}

	
}

void drawButton(const Texture& button) {

	SDL_RenderCopy(RENDER, button.text, NULL, &button.dstrect);
}

void drawButtons(const Texture* array) {

	for (int i = 0; i < MENU_BUTTON_COUNT; i++) {
		SDL_RenderCopy(RENDER, array[i].text, NULL, &array[i].dstrect);
	}
}

void changeActiveButton(Menu& menu) {

	if (!menu.keyState[SDL_SCANCODE_UP] && !menu.keyState[SDL_SCANCODE_DOWN]) return;

	int offset, i = menu.status;
	if (menu.keyState[SDL_SCANCODE_UP]) offset = -1;
	if (menu.keyState[SDL_SCANCODE_DOWN]) offset = 1;

	SDL_DestroyTexture(menu.button[i].text);
	SDL_Surface* surface = loadText(menu.font, MENU_OPTIONS[i], BUTTON_COLOR);
	menu.button[i].text = SDL_CreateTextureFromSurface(RENDER, surface);
	SDL_FreeSurface(surface);

	menu.status = i = (i + 1) % MENU_BUTTON_COUNT;

	SDL_DestroyTexture(menu.button[i].text);
	surface = loadText(menu.font, MENU_OPTIONS[i], BUTTON_COLOR);
	menu.button[i].text = SDL_CreateTextureFromSurface(RENDER, surface);
	SDL_FreeSurface(surface);
}

void menuInit(Menu& menu) {
	
	menu.status = MENU_START;
	menu.music = loadMusic(MENU_MUSIC);
	menu.font = loadFont(MENU_FONT);
	menu.keyState = SDL_GetKeyboardState(NULL);
	menu.ticks = SDL_GetTicks();

	setButtons(menu.button, menu.font);
}

void menuDeInit(Menu& menu) {
	
	for (int i = 0; i < MENU_BUTTON_COUNT; i++) {
		
		SDL_DestroyTexture(menu.button[i].text);
		menu.button[i].text = NULL;
		menu.button[i].dstrect = { 0, 0, 0, 0 };
	}

	Mix_FreeMusic(menu.music);
	TTF_CloseFont(menu.font);

	menu.status = MENU_NONE;
	menu.music = NULL;
	menu.font = NULL;
	menu.keyState = NULL;
	menu.ticks = 0;
}

void updateMenu(Menu& menu) {

	changeActiveButton(menu);
}

void drawMenu(const Menu& menu) {

	SDL_SetRenderDrawColor(RENDER, 255, 255, 255, 255);
	SDL_RenderClear(RENDER);

	drawButtons(menu.button);
}