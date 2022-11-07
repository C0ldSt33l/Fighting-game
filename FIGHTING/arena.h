#pragma once

#include"texture.h"


#define ARENA_PATH      "files/assets/sprites/backgrounds/arenas/"

const char arenaName[4][10] = {

};


Texture* initArena(int number);
void deInitArena(Texture* arena);

void drawArena(const Texture* arena);