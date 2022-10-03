#pragma once

#include"texture.h"


Texture* initArena(int number);
void deInitArena(Texture* arena);

void drawArena(const Texture* arena);