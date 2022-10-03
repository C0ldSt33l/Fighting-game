#pragma once

#include<SDL_mixer.h>


#define MUSIC_PATH "files/assets/sounds/music/"
#define CHUNK_PATH "files/assets/sounds/chunks/"

const char MUSIC_NAME[4][19] = {
	"GGXrd main menu",
	"GGXrd Ride of fire"
};

Mix_Music* loadMusic(const char* file);
void playMusic(Mix_Music* music);
//Mix_Music* changeMusic(MENU& menu, const char* file);
//Mix_Chunk* loadChuck(MENU& menu, const char* file);