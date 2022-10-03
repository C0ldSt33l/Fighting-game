#pragma once

enum GameStatus {
    GAME_MENU,
    GAME_SETTINGS,
    GAME_ABOUT_GAME,
    GAME_SELECTOR,
    GAME_BATTLE,
    GAME_EXIT
};

struct Game {
    int status = GAME_MENU;

    bool run = true;
};

void processGame(Game& game);