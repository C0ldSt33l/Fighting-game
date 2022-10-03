#include<stdio.h>
#include<string>

#include"player.h"
#include"sound.h"
#include"interface.h"
#include"battle.h"
#include"menu.h"
#include"selector.h"


int main(int argc, char* argv[]) {

    init();

    Game game;

    while (game.run) {

        menu(game);
        battle(game);
    }

    deInit(0);
    return 0;
}