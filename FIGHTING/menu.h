#pragma once

#include<SDL.h>

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
#define MENU_MUSIC      "files/assets/sounds/music/BBCF main menu.mp3"
#define MENU_FONT       "files/assets/fonts/RED.ttf"
#define MENU_BACKGROUND "files/assets/sprites/backgrounds/menu/main menu.jpg"

#define MENU_MAX_FONT_SIZE  100
#define MENU_MIN_FONT_SIZE  35

extern const char MENU_OPTIONS[MENU_BUTTON_COUNT][9];

// ABOUT CONFIG
#define MENU_ABOUT_SIZE 70
#define MENU_ABOUT_TEXT "Final project on programming on the topic '2D fighting'\nwas developed by a student of BSTU group O - 21 - IVT - 2 - PO - B\nSychev Dmitry"

extern const SDL_Color MENU_ABOUT_TEXT_COLOR;


enum MenuStatus {
    MENU_NONE = -1,
    MENU_MAIN_MENU,
    MENU_SETTINGS,
    MENU_ABOUT
};

enum activeButton {
    BUTTON_NONE = -1,
    BUTTON_START,
    BUTTON_SETTINGS,
    BUTTON_ABOUT,
    BUTTON_EXIT
};


// STRUCTS
struct MenuKey {
    bool up     = false,
         down   = false;

    bool accept = false,
         back   = false;
};

struct About {
    Texture  text;
    SDL_Rect background;
};

struct Menu {
    
    bool run = false;
    int status = MENU_NONE;

    int activeButton = BUTTON_NONE;
    Texture button[MENU_BUTTON_COUNT];

    Texture about;

    SDL_Texture* background = nullptr;
    Mix_Music*   music      = nullptr;
    TTF_Font*    font       = nullptr;

    MenuKey key;

    int ticks;
};


// FUNCTIONS
// 1.Buttons
void setButtonCoords(SDL_Rect& rect, int number);
void setButtons(Texture* array, TTF_Font* font);

void drawButton(const Texture& button);
void drawButtons(const Texture* array);

SDL_Texture* changeButtonTexture(SDL_Texture* texture, TTF_Font* font, int number, SDL_Color color);
void changeActiveButton(MenuKey& key, Texture* array, int& activeButton, int& ticks, TTF_Font* font);

// 2. Menu
void initMenu(Menu& menu);
void deInitMenu(Menu& menu);

void updateMeneKeyStatus(MenuKey& key);
void updateMenuStatus(Menu& menu, Game& game);
void updateMenu(Menu& menu, Game& game);

void drawMainMenu(const Menu& menu);

void menu(Game& game);