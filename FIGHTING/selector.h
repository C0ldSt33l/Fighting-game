#pragma once

#include"texture.h"
#include"sound.h"
#include"game.h"
#include"window.h"


// SELECTOR CONFIG
#define ICON_PATH       "files/assets/sprites/icons/"
#define SPLASH_ART_PATH "files/assets/sprites/splash arts/"

#define ICON_DISTANCE WINDOW_WIDTH / 10

#define SELECTOR_FONT_SIZE 12

enum SelectStatus {
    SELECT_NONE = -1,
    SELECT_CHARACTER_1,
    SELECT_CHARACTER_2,
    SELECT_ARENA,
    SELECT_MUSIC
};


// STRUCT
struct KeyStatus {
    bool accept = false,
         back   = false;

    bool up    = false,
         down  = false,
         right = false,
         left  = false;
};

struct Icon {
    bool active = false;
    Texture texture;
};

struct Selector {
    bool run = false;
    int status = SELECT_NONE;

    int player1select = -1,
        player2select = -1;
    Icon* icon = nullptr;

    Texture* arenaSelect = nullptr;
    Texture* musicSelect = nullptr;

    Mix_Music* music = nullptr;
    Mix_Chunk* chunk = nullptr;

    TTF_Font* font = nullptr;
    
    SDL_Event event;
    KeyStatus keyStatus;
};

// FUNCTION
// Icon
void setIcons(Icon* array);
void destroyIcons(Icon* array);

void drawIcons(Icon* array);
void drawIcon(Icon& icon);

// Selector
void initSelector(Selector& selector);
void deInitSelector(Selector& selector);

void updateSelector(Selector& selector);

void drawSelector(const Selector selector);

void selector(Game& game);