#include<stdio.h>

#include"window.h"
#include"battle.h"
#include"sound.h"
#include"player.h"
#include"game.h"
#include"arena.h"
#include"box.h"
#include"file.h"


void initBattle(Battle& battle) {
    
    battle.run = true;
    
    battle.arena = initArena(6);

    battle.music = loadMusic("files/assets/sounds/music/GGXrd main menu.mp3");

    battle.player1 = (Player*)malloc(sizeof(Player));
    if (!battle.player1) {
        printf("Memory allocate error for player1\n");
        deInit(1);
    }
    battle.player2 = (Player*)malloc(sizeof(Player));
    if (!battle.player2) {
        printf("Memory allocate error for player2\n");
        deInit(1);
    }


    initPlayer(*battle.player1, "naoto", SIDE_LEFT);
    initPlayer(*battle.player2, "naoto", SIDE_RIGHT);
    initInterface(battle.interface);
}

void deInitBattle(Battle& battle) {

    battle.run = false;

    Mix_HaltMusic();
    Mix_FreeMusic(battle.music);

    deInitPlayer(*battle.player1);
    free(battle.player1);

    deInitPlayer(*battle.player2);
    free(battle.player2);

    deInitArena(battle.arena);

    deInitInterface(battle.interface);
}

void updateBattleKey(bool& run, SDL_Event& event, BattleKey& key, Game& game) {

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: run = game.run = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE: run = game.run = false;
                break;


            case SDL_SCANCODE_W: key.w = true;
                break;
            case SDL_SCANCODE_S: key.s = true;
                break;
            case SDL_SCANCODE_A: key.a = true;
                break;
            case SDL_SCANCODE_D: key.d = true;
                break;

            case SDL_SCANCODE_U: key.u = true;
                break;
            case SDL_SCANCODE_I: key.i = true;
                break;
            case SDL_SCANCODE_O: key.o = true;
                break;
            case SDL_SCANCODE_Q: key.q = true;
                break;


            case SDL_SCANCODE_UP:	 key.up    = true;
                break;
            case SDL_SCANCODE_DOWN:  key.down  = true;
                break;
            case SDL_SCANCODE_LEFT:  key.left  = true;
                break;
            case SDL_SCANCODE_RIGHT: key.right = true;
                break;

            case SDL_SCANCODE_KP_4: key.n4 = true;
                break;
            case SDL_SCANCODE_KP_5: key.n5 = true;
                break;
            case SDL_SCANCODE_KP_6: key.n6 = true;
                break;
            case SDL_SCANCODE_KP_2: key.n2 = true;
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W: key.w = false;
                break;
            case SDL_SCANCODE_S: key.s = false;
                break;
            case SDL_SCANCODE_A: key.a = false;
                break;
            case SDL_SCANCODE_D: key.d = false;
                break;

            case SDL_SCANCODE_U: key.u = false;
                break;
            case SDL_SCANCODE_I: key.i = false;
                break;
            case SDL_SCANCODE_O: key.o = false;
                break;
            case SDL_SCANCODE_Q: key.q = false;
                break;


            case SDL_SCANCODE_UP:	 key.up    = false;
                break;
            case SDL_SCANCODE_DOWN:  key.down  = false;
                break;
            case SDL_SCANCODE_LEFT:  key.left  = false;
                break;
            case SDL_SCANCODE_RIGHT: key.right = false;
                break;

            case SDL_SCANCODE_KP_4: key.n4 = false;
                break;
            case SDL_SCANCODE_KP_5: key.n5 = false;
                break;
            case SDL_SCANCODE_KP_6: key.n6 = false;
                break;
            case SDL_SCANCODE_KP_2: key.n2 = false;
                break;
            }
            break;
        }
    }
}

void updateBattle(Battle& battle, Game& game) {

    updateBattleKey(battle.run, battle.event, battle.key, game);
    
    updatePlayers(*battle.player1, *battle.player2, battle.key);
    updateInterface(battle.interface, battle.player1->health, battle.player1->maxHealth,
                                      battle.player2->health, battle.player2->maxHealth);

    if (!battle.player1->health || !battle.player2->health) {
        battle.run = game.run = false;
    }
}

void drawBattle(Battle& battle) {
    
    drawArena(battle.arena);

    drawPlayer(*battle.player1, battle.player1->curanimation);
    drawPlayer(*battle.player2, battle.player2->curanimation);
    drawInterface(battle.interface);

    SDL_RenderPresent(RENDER);
    SDL_Delay(1000 / 60);
}

void battle(Game& game) {

    if (game.status != GAME_BATTLE) return;

    Battle battle;
    initBattle(battle);

    playMusic(battle.music);
    while (battle.run) {
        
        updateBattle(battle, game);
        drawBattle(battle);
    }

    deInitBattle(battle);
}