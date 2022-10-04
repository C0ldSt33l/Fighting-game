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
    bool run = true;

    int status = GAME_MENU;
};

void processGame(Game& game);