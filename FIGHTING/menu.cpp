#include<stdio.h>

#include"sound.h"
#include"menu.h"
#include"font.h"
#include"sound.h"
#include"game.h"


// BUTTON CONFIG
SDL_Color ACTIVE_BUTTON_COLOR = { 255, 0, 0, 255 };
SDL_Color BUTTON_COLOR		  = { 150, 150, 150, 255 };

const char MENU_OPTIONS[MENU_BUTTON_COUNT][9] = { "start", "settings", "about", "exit" };

const SDL_Color MENU_ABOUT_TEXT_COLOR = { 255, 0, 0, 255 };

// FUNCTIONS
void setButtonCoords(SDL_Rect& rect, int number) {

    centerText(rect.x, rect.w, WINDOW_WIDTH);
    rect.y = MENU_BUTTON_START_Y + MENU_BUTTON_DISTANCE * number;
}

void setButtons(Texture* array, TTF_Font* font) {

    array[0] = createText(font, MENU_OPTIONS[0], ACTIVE_BUTTON_COLOR);
    setButtonCoords(array[0].dstrect, 0);
    for (int i = 1; i < MENU_BUTTON_COUNT; i++) {
        
        array[i] = createText(font, MENU_OPTIONS[i], BUTTON_COLOR);
        setButtonCoords(array[i].dstrect, i);
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

void changeActiveButton(MenuKey& key, Texture* array, int& activeButton, int& ticks, TTF_Font* font) {

    if (!key.up && !key.down) return;
    static int curTime;
    curTime = SDL_GetTicks();
    
    if (curTime - ticks < 200) return;
    ticks = curTime;
    
    static int offset;
    if (key.up)   offset = -1;
    if (key.down) offset =  1;

    array[activeButton].text = changeButtonTexture(array[activeButton].text, font, activeButton, BUTTON_COLOR);

    activeButton += offset;
    activeButton = activeButton < 0 ? MENU_BUTTON_COUNT - 1 : activeButton % MENU_BUTTON_COUNT;
    
    array[activeButton].text = changeButtonTexture(array[activeButton].text, font, activeButton, ACTIVE_BUTTON_COLOR);
}

void initMenu(Menu& menu) {
    
    menu.run = true;
    menu.status = MENU_MAIN_MENU;

    menu.font = loadFont(MENU_FONT, MENU_ABOUT_SIZE);
    menu.about = createText(menu.font, MENU_ABOUT_TEXT, MENU_ABOUT_TEXT_COLOR);
    centerText(menu.about.dstrect.x, menu.about.dstrect.w, WINDOW_WIDTH);
    centerText(menu.about.dstrect.y, menu.about.dstrect.h, WINDOW_HEIGHT);
    TTF_CloseFont(menu.font);

    menu.background = createSdlTexture(MENU_BACKGROUND);
    menu.font = loadFont(MENU_FONT, getFontSize(WINDOW_WIDTH));
    menu.music = loadMusic(MENU_MUSIC);

    setButtons(menu.button, menu.font);
    menu.activeButton = BUTTON_START;

    menu.ticks = SDL_GetTicks();
}

void deInitMenu(Menu& menu) {
    
    for (int i = 0; i < MENU_BUTTON_COUNT; i++) {
        
        SDL_DestroyTexture(menu.button[i].text);
        menu.button[i].text = NULL;
        menu.button[i].dstrect = { 0, 0, 0, 0 };
    }
    menu.activeButton = BUTTON_NONE;

    SDL_DestroyTexture(menu.about.text);

    Mix_HaltMusic();
    Mix_FreeMusic(menu.music);
    menu.music = nullptr;

    TTF_CloseFont(menu.font);
    menu.font  = nullptr;

    SDL_DestroyTexture(menu.background);

    menu.run = false;
    menu.status = MENU_NONE;
    
    menu.key = { false, false, false };
    menu.ticks = 0;
}

void updateMeneKeyStatus(MenuKey& key) {

    static SDL_Event event;
    while (!SDL_PollEvent(&event));

    static const Uint8* state = SDL_GetKeyboardState(nullptr);

    key.up   = state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP];
    key.down = state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN];

    key.accept = state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE];
    key.back   = state[SDL_SCANCODE_ESCAPE];
}

void updateMenuStatus(Menu& menu, Game& game) {

    if (menu.key.accept) {
        switch (menu.activeButton) {
        case BUTTON_START:
            menu.run = false;
            game.status = GAME_BATTLE;
            break;

        case BUTTON_SETTINGS:
            break;
        case BUTTON_ABOUT: menu.status = MENU_ABOUT;
            break;
        case BUTTON_EXIT:  menu.run = game.run = false;
            break;
        }
    }

    if (menu.status != MENU_MAIN_MENU && menu.key.back) menu.status = MENU_MAIN_MENU;
}

void updateMenu(Menu& menu, Game& game) {

    updateMeneKeyStatus(menu.key);
    updateMenuStatus(menu, game);
    changeActiveButton(menu.key, menu.button, menu.activeButton, menu.ticks, menu.font);
}

void drawMenu(const Menu& menu) {

    SDL_RenderCopy(RENDER, menu.background, nullptr, nullptr);

    switch (menu.status) {
    case MENU_MAIN_MENU: drawButtons(menu.button);
        break;
    case MENU_SETTINGS:
        break;
    case MENU_ABOUT: SDL_RenderCopy(RENDER, menu.about.text, nullptr, &menu.about.dstrect);
        break;
    }
    
    SDL_RenderPresent(RENDER);
    SDL_Delay(1000 / 60);
}

void menu(Game& game) {

    if (game.status != GAME_MENU) return;

    Menu menu;
    initMenu(menu);

    Mix_PlayMusic(menu.music, -1);
    while (menu.run) {
        updateMenu(menu, game);
        drawMenu(menu);
    }

    deInitMenu(menu);
}