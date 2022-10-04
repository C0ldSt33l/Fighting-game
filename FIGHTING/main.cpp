#include"window.h"
#include"game.h"

int main(int argc, char* argv[]) {

    init();

    Game game;
    while (game.run) {
        processGame(game);
    }

    deInit(0);
    return 0;
}