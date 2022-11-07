#include<stdio.h>

#include"selector.h"
#include"window.h"
#include"texture.h"
#include"player.h"
#include"font.h"
#include"menu.h"

const char iconName[CHARACTER_COUNT][39] = {
    "files/assets/sprites/icons/naoto.png",
    "files/assets/sprites/icons/tager.png",
    "files/assets/sprites/icons/hakumen.png",
    "files/assets/sprites/icons/kagura.png"
};


void setIcons(Icon* array) {

    array->active = true;
    for (int i = 0; i < 4; i++) {
        array[i].texture = createTexture(iconName[i]);
        array[i].texture.dstrect.w = array[i].texture.dstrect.h *= 1.5f;
        array[i].texture.dstrect.x = WINDOW_WIDTH / 4 + ICON_DISTANCE * i;
        array[i].texture.dstrect.y = WINDOW_HEIGHT / 4;
    }
}

void initSelector(Selector& selector) {

    selector.icon = (Icon*)malloc(sizeof(Icon) * CHARACTER_COUNT);
    if (!selector.icon) {
        printf("Memory allocate error for selector.icon\n");
        deInit(1);
    }
    setIcons(selector.icon);

    selector.run = true;
    selector.status = SELECT_CHARACTER_1;
    
    selector.font = loadFont(MENU_FONT, SELECTOR_FONT_SIZE);

    selector;
}

void destroyIcons(Icon* array) {

    for (int i = 0; i < CHARACTER_COUNT; i++) {
        SDL_DestroyTexture(array[i].texture.text);
    }

    free(array);
}

void deInitSelector(Selector& selector) {

    destroyIcons(selector.icon);
}

void updateSelector(Selector& selector) {


}

void drawIcon(Icon& icon) {

    SDL_RenderCopy(RENDER, icon.texture.text, NULL, &icon.texture.dstrect);
}

void drawIcons(Icon* array) {

    for (int i = 0; i < CHARACTER_COUNT; i++) {

        drawIcon(array[i]);
    }
}

void drawSelector(const Selector selector) {
     
    drawIcons(selector.icon);
    
    SDL_RenderPresent(RENDER);
    SDL_Delay(WINDOW_DELAY);
}

void selector(Game& game) {

    Selector selector;
    initSelector(selector);

    while (selector.run) {

        updateSelector(selector);
        drawSelector(selector);
    }

    deInitSelector(selector);
}