#include<stdio.h>

#include"arena.h"
#include"texture.h"
#include"selector.h"

Texture* initArena(int number) {

	Texture* arena = (Texture*)malloc(sizeof(Texture));
	if (!arena) {
		printf("Memory allocate error for battle.arena\n");
		deInit(1);
	}

	char path[100];

	sprintf_s(path, "%sarena %d/part a.png", ARENA_PATH, number);
	arena[0] = createTexture(path);
	//sprintf_s(path, "%sarena %d/part b.png", ARENA_PATH, number);
	//arena[1] = createTexture(path);
	//sprintf_s(path, "%sarena %d/part c.png", ARENA_PATH, number);
	//arena[2] = createTexture(path);

	return arena;
}

void deInitArena(Texture* arena) {

	for (int i = 0; i < 1; i++) {
		SDL_DestroyTexture(arena[i].text);
	}
	free(arena);
}

void drawArena(const Texture* arena) {

	for (int i = 0; i < 1; i++) {

		SDL_RenderCopy(RENDER, arena[i].text, nullptr, nullptr);
		//SDL_RenderCopy(RENDER, arena[i].text, nullptr, nullptr);
	}
}