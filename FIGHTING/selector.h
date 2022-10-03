#pragma once

#include"texture.h"
#include"sound.h"
#include"game.h"
#include"window.h"


// SELECTOR CONFIG
#define ICON_PATH       "files/assets/sprites/icons/"
#define ARENA_PATH      "files/assets/sprites/backgrounds/arenas/"
#define SPLASH_ART_PATH "files/assets/sprites/splash arts/"

#define ICON_DISTANCE WINDOW_WIDTH / 10

#define SELECTOR_FONT_SIZE 12

const char arenaName[4][10] = {

};

enum SelectStatus {
    SELECT_NONE = -1,
    SELECT_CHARACTER,
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
    Icon* icon = NULL;

    int select = -1;
    Texture* arenaSelect = NULL;
    Texture* musicSelect = NULL;

    Mix_Music* music = NULL;
    Mix_Chunk* chunk = NULL;

    TTF_Font* font = NULL;
    
    SDL_Event event;

    KeyStatus keyStatus;
};

// FUNCTION
void setIcons(Icon* array);

void initSelector(Selector& selector);
void deInitSelector(Selector& selector);
void destroyIcons(Icon* array);

void updateSelector(Selector& selector);

void drawIcon(Icon& icon);
void drawIcons(Icon* array);

void drawSelector(const Selector selector);

void selector(Game& game);