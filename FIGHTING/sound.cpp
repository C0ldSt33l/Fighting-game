#include<stdio.h>

#include"window.h"
#include"sound.h"

Mix_Music* loadMusic(const char* file) {
    Mix_Music* music = Mix_LoadMUS(file);
    if (!music) {
        printf("Couldn't load music: %s. Error: %s\n", file, SDL_GetError());
        deInit(1);
    }

    return music;
}

void playMusic(Mix_Music* music) {
    
    if (Mix_PlayingMusic()) return;
    
    Mix_PlayMusic(music, -1);
}

void changeMusic(Mix_Music* music) {

    Mix_HaltMusic();
    Mix_PlayMusic(music, -1);
}

//void playMusic(MENU& menu) {
//	if (Mix_PlayingMusic()) Mix_PlayMusic(menu.music, -1);
//}
//
//Mix_Music* changeMusic(const char* file) {
//	Mix_HaltMusic();
//	
//	return loadMusic(file);
//}
//
//Mix_Chunk* loadChuck(MENU& menu, const char* file);