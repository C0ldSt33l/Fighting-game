#include"game.h"
#include"menu.h"
#include"battle.h"

void processGame(Game& game) {
	menu(game);
	battle(game);
}