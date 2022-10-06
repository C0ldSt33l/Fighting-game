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

SDL_Texture* changeButtonTexture(SDL_Texture* texture, TTF_Font* font, int number, SDL_Color color) {

    SDL_DestroyTexture(texture);
    
    SDL_Surface* surface = loadText(font, MENU_OPTIONS[number], color);
    texture = SDL_CreateTextureFromSurface(RENDER, surface);

    SDL_FreeSurface(surface);

    return texture;
}

void changeActiveButton(Menu& menu) {

    if (!menu.key.up && !menu.key.down) return;
    static int curTime;
    curTime = SDL_GetTicks();
    
    if (curTime - menu.ticks < 200) return;
    menu.ticks = curTime;
    
    static int offset;
    if (menu.key.up)   offset = -1;
    if (menu.key.down) offset =  1;

    menu.button[menu.status].text = changeButtonTexture(menu.button[menu.status].text, menu.font, menu.status, BUTTON_COLOR);

    menu.status += offset;
    menu.status = menu.status < 0 ? MENU_BUTTON_COUNT - 1 : menu.status;
    
    menu.button[menu.status].text = changeButtonTexture(menu.button[menu.status].text, menu.font, menu.status, ACTIVE_BUTTON_COLOR);
}

void initMenu(Menu& menu) {
    
    menu.run = true;
    menu.status = MENU_START;

    menu.music = loadMusic(MENU_MUSIC);
    menu.font = loadFont(MENU_FONT, getFontSize(WINDOW_WIDTH));

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
   
    menu.music = nullptr;
    menu.font  = nullptr;
    
    menu.key = { false, false, false };
    menu.ticks = 0;
}

void updateMeneKeyStatus(MenuKey& key) {

    static const Uint8* state = SDL_GetKeyboardState(nullptr);

    key.up   = state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP];
    key.down = state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN];

    key.accept = state[SDL_SCANCODE_U] || state[SDL_SCANCODE_KP_4] ||
                 state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE] ||
                 state[SDL_SCANCODE_J];
}

void updateMenuStatus(Menu& menu, Game& game) {

    if (menu.key.accept) {
        switch (menu.status) {
        case MENU_START:
            menu.run = false;
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

void updateMenu(Menu& menu, Game& game) {

    updateMeneKeyStatus(menu.key);
    updateMenuStatus(menu, game);
    changeActiveButton(menu);
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