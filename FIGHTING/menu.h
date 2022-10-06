#pragma once

#include"window.h"
#include"texture.h"
#include"game.h"

// BUTTON CONFIG

//#define BUTTON_WIDTH	win_width / 6     used for button from rect
//#define BUTTON_HEIGHT   win_height / 18
#define MENU_BUTTON_START_Y WINDOW_HEIGHT / 3
#define MENU_BUTTON_DISTANCE WINDOW_HEIGHT / 8

#define MENU_BUTTON_COUNT 4

extern SDL_Color BUTTON_COLOR;
extern SDL_Color ACTIVE_BUTTON_COLOR;

// MENU CONFIG

#define MENU_MUSIC "files/assets/sounds/music/BBCF main menu.mp3"

#define MENU_FONT  "files/assets/fonts/RED.ttf"
#define MENU_MAX_FONT_SIZE  100
#define MENU_MIN_FONT_SIZE  35

extern const char MENU_OPTIONS[MENU_BUTTON_COUNT][9];

enum MenuStatus {
    MENU_NONE = -1,
    MENU_START,
    MENU_SETTINGS,
    MENU_ABOUT,
    MENU_EXIT
};


// STRUCTS
struct MenuKey {
    bool up     = false,
         down   = false;

    bool accept = false;
};

struct Menu {
    
    bool run = false;
    SDL_Event event;
    
    int status = MENU_NONE;
    Texture button[MENU_BUTTON_COUNT];

    Mix_Music* music = NULL;
    TTF_Font* font = NULL;

    MenuKey key;

    int ticks;
};

// FUNCTIONS

// 1.Buttons
void setButtonCoords(Texture& button, int number);
void setButtons(Texture* array, TTF_Font* font);

void drawButton(const Texture& button);
void drawButtons(const Texture* array);

SDL_Texture* changeButtonTexture(SDL_Texture* texture, TTF_Font* font, int number, SDL_Color color);
void changeActiveButton(Menu& menu);

// 2. Menu
void initMenu(Menu& menu);
void deInitMenu(Menu& menu);

void updateMeneKeyStatus(MenuKey& key);
void updateMenuStatus(Menu& menu, Game& game);
void updateMenu(Menu& menu, Game& game);

void drawMenu(const Menu& menu);

void menu(Game& game);