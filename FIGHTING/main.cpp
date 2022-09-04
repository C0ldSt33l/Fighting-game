#include<stdio.h>
#include<string>

#include"player.h"
#include"sound.h"

struct Common {
	bool run = true;

	int fps = 1000 / FRAME_COUNT;

	int time = SDL_GetTicks();
};

void handleEvents(SDL_Event& event, Common& common, Key& key) {

	while (SDL_PollEvent(&event)) {	
		switch (event.type) {
		case SDL_QUIT: common.run = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_P:
			case SDL_SCANCODE_RETURN:
			case SDL_SCANCODE_ESCAPE: common.run = false;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		updateKeyStatus(key, event);
	}
}

void draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect) {

	SDL_SetRenderDrawColor(RENDER, 255, 255, 255, 255);
	SDL_RenderClear(RENDER);

	SDL_RenderCopyEx(RENDER, texture, srcrect, dstrect, 0, 0, SDL_FLIP_NONE);
}

int main(int argc, char* argv[]) {
	
	init();

	Common common;
	SDL_Event event;
	
	Player player;
	initPlayer(player);

	while (common.run) {
		handleEvents(event, common, player.key);
	
		#pragma region BATTLE LOGIC
		updatePlayer(player);
		returnInBoard(player.dstrect);

		#pragma region Animation
		//printf("curframe: %d\n", player.curframe);

		#pragma endregion
		
		draw(player.animation[player.curanimation].texture.text, &player.animation[player.curanimation].texture.dstrect, &player.dstrect);
		SDL_RenderPresent(RENDER);
		SDL_Delay(common.fps);
	}

	deInitPlayer(player);

	deInit(0);
	return 0;
}