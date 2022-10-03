#include<stdio.h>
#include"sound.h"

#include"menu.h"
#include"font.h"
#include"sound.h"
#include"game.h"


SDL_Color ACTIVE_BUTTON_COLOR = { 255, 0, 0, 255 };
SDL_Color BUTTON_COLOR		  = { 0, 0, 0, 255 };

const char MENU_OPTIONS[MENU_BUTTON_COUNT][9] = { "start", "settings", "about", "exit" };


void setButtonCoords(Texture& button, int number) {

    button.dstrect.x = (WINDOW_WIDTH - button.dstrect.w) / 2;
    button.dstrect.y = MENU_BUTTON_START_Y + MENU_BUTTON_DISTANCE * number;
}

void setButtons(Texture* array, TTF_Font* font) {

    array[0] = createText(font, MENU_OPTIONS[0], ACTIVE_BUTTON_COLOR);
    setButtonCoords(array[0], 0);
    for (int i = 1; i < MENU_BUTTON_COUNT; i++) {
        
        array[i] = createText(font, MENU_OPTIONS[i], BUTTON_COLOR);
        setButtonCoords(array[i], i);
    }

    
}

void drawButton(const Texture& button) {

    SDL_RenderCopy(RENDER, button.text, NULL, &button.dstrect);
}

void drawButtons(const Texture* array) {

    for (int i = 0; i < MENU_BUTTON_COUNT; i++) {
        SDL_RenderCopy(RENDER, array[i].text, NULL, &array[i].dstrect);
    }
}

void changeActiveButton(Menu& menu) {

    if (!menu.keyState[SDL_SCANCODE_W] && !menu.keyState[SDL_SCANCODE_S]) return;
    
    static int curTime;
    curTime = SDL_GetTicks();
    
    if (curTime - menu.ticks < 200) return;
    menu.ticks = curTime;
    
    static int offset, i = menu.status;
    if (menu.keyState[SDL_SCANCODE_W]) offset = -1;
    if (menu.keyState[SDL_SCANCODE_S]) offset = 1;

    SDL_DestroyTexture(menu.button[i].text);
    SDL_Surface* surface = loadText(menu.font, MENU_OPTIONS[i], BUTTON_COLOR);
    menu.button[i].text = SDL_CreateTextureFromSurface(RENDER, surface);
    SDL_FreeSurface(surface);

    menu.status = i = i + offset < 0 ? MENU_BUTTON_COUNT - 1 : abs(i + offset) % MENU_BUTTON_COUNT;

    SDL_DestroyTexture(menu.button[i].text);
    surface = loadText(menu.font, MENU_OPTIONS[i], ACTIVE_BUTTON_COLOR);
    menu.button[i].text = SDL_CreateTextureFromSurface(RENDER, surface);
    SDL_FreeSurface(surface);
}

void initMenu(Menu& menu) {
    
    menu.run = true;
    menu.status = MENU_START;
    menu.music = loadMusic(MENU_MUSIC);
    menu.font = loadFont(MENU_FONT, getFontSize(WINDOW_WIDTH));
    menu.keyState = SDL_GetKeyboardState(NULL);
    menu.ticks = SDL_GetTicks();

    setButtons(menu.button, menu.font);
}

void deInitMenu(Menu& menu) {
    
    for (int i = 0; i < MENU_BUTTON_COUNT; i++) {
        
        SDL_DestroyTexture(menu.button[i].text);
        menu.button[i].text = NULL;
        menu.button[i].dstrect = { 0, 0, 0, 0 };
    }

    Mix_HaltMusic();
    Mix_FreeMusic(menu.music);
    TTF_CloseFont(menu.font);

    menu.run = false;
    menu.status = MENU_NONE;
    menu.music = NULL;
    menu.font = NULL;
    menu.keyState = NULL;
    menu.ticks = 0;
}

void updateMenu(Menu& menu, Game& game) {

    changeActiveButton(menu);
    if (menu.keyState[SDL_SCANCODE_RETURN] || menu.keyState[SDL_SCANCODE_J]) {
        switch (menu.status) {
        case MENU_START: menu.run = false;
                         game.status = GAME_BATTLE;
            break;

        case MENU_SETTINGS:
            break;
        case MENU_ABOUT:
            break;
        case MENU_EXIT: menu.run = false;
                        game.run = false;
            break;
        }
    }
}

void drawMenu(const Menu& menu) {

    SDL_SetRenderDrawColor(RENDER, 255, 255, 255, 255);
    SDL_RenderClear(RENDER);

    drawButtons(menu.button);

    SDL_RenderPresent(RENDER);
    SDL_Delay(1000 / 60);
}

void menu(Game& game) {

    if (game.status != GAME_MENU) return;

    Menu menu;
    initMenu(menu);

    Mix_PlayMusic(menu.music, -1);
    while (menu.run) {
        while (SDL_PollEvent(&menu.event)) {
            switch (menu.event.type)
            {
            case SDL_QUIT: menu.run = false;
                break;
            }
        }

        updateMenu(menu, game);

        drawMenu(menu);
    }

    deInitMenu(menu);
}