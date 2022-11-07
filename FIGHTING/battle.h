#pragma once

#include<SDL.h>
#include<SDL_mixer.h>

#include"player.h"
#include"interface.h"
#include"game.h"


// STRUCTS
struct Player;

struct BattleKey {
    bool w = false,
         s = false,
         a = false,
         d = false,
         
         u = false,
         i = false,
         o = false,
         q = false,
         
         e = false;

    bool up = false,
         down = false,
         left = false,
         right = false,
         
         n4 = false,
         n5 = false,
         n6 = false,
         n2 = false,
         
         n8 = false;
};

struct Battle {

    bool run = false;

    SDL_Event event;
    BattleKey key;

    Texture*   arena = nullptr;
    Mix_Music* music = nullptr;

    Player *player1 = nullptr,
           *player2 = nullptr;

    Interface interface;
};


// FUNCTIONS
void initBattle(Battle& battle);
void deInitBattle(Battle& battle);

void updateBattleKey(bool& run, SDL_Event& event, BattleKey& key, Game& game);
void updateBattle(Battle& battle, Game& game);

void drawBattle(Battle& battle);

void battle(Game& game);
