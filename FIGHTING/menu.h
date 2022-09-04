#pragma once

#include"window.h"
#include"texture.h"

// BUTTON CONFIG

//#define BUTTON_WIDTH	win_width / 6     used for button from rect
//#define BUTTON_HEIGHT   win_height / 18
#define MENU_BUTTON_START_Y WINDOW_HEIGHT / 3
#define MENU_BUTTON_DISTANCE WINDOW_HEIGHT / 8

#define MENU_BUTTON_COUNT 4

extern SDL_Color BUTTON_COLOR;
extern SDL_Color ACTIVE_BUTTON_COLOR;

// MENU CONFIG

#define MENU_MUSIC "files\\assets\\sounds\\BBCF main menu.mp3"

#define MENU_FONT  "files\\assets\\fonts\\RED.ttf"
#define MENU_MAX_FONT_SIZE  100
#define MENU_MIN_FONT_SIZE  35

const char MENU_OPTIONS[MENU_BUTTON_COUNT][9] = {"start", "settings", "about", "exit"};

enum MenuStatus {
	MENU_NONE = -1,
	MENU_START,
	MENU_SETTINGS,
	MENU_ABOUT,
	MENU_EXIT
};

struct Menu {
	unsigned int status = MENU_NONE;
	Texture button[MENU_BUTTON_COUNT];

	Mix_Music* music = NULL;
	TTF_Font* font = NULL;

	const Uint8* keyState = NULL;
	int ticks;
};

// FUNCTIONS

// 1.Buttons
void setButtonCoords(Texture& button, int number);
void setButtons(Texture* array, TTF_Font* font);

void drawButton(const Texture& button);
void drawButtons(const Texture* array);

void changeActiveButton(Menu& menu);

// 2. Menu
void menuInit(Menu& menu);
void menuDeInit(Menu& menu);

void updateMenu(Menu& menu);

void drawMenu(const Menu& menu);