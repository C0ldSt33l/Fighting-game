#include"interface.h"

void initInterface(Interface& interface) {

    interface.health1.y = interface.health2.y = WINDOW_HEIGHT / 10;
    interface.health1.h = interface.health2.h = WINDOW_HEIGHT / 20;
    
    interface.health1.w =  HEALTH_RECT_WIDTH;
    interface.health2.w = -HEALTH_RECT_WIDTH;
    
    interface.health1.x = WINDOW_WIDTH / 15;
    interface.health2.x = WINDOW_WIDTH - WINDOW_WIDTH / 15;
    
    //interface.meter1.y = interface.meter2.y = WINDOW_HEIGHT / 10 * 9;
    //interface.meter1.w = interface.meter2.w = WINDOW_WIDTH / 3;
    //interface.meter1.h = interface.meter2.h = WINDOW_HEIGHT / 20;

    interface.time = 90;
}

void deInitInterface(Interface& interface) {

    interface.health1.w = interface.health1.h = 0;
    interface.health2.w = interface.health2.h = 0;

    interface.meter1.w = interface.meter1.h = 0;
    interface.meter2.w = interface.meter2.h = 0;

    interface.time = 0;
    SDL_DestroyTexture(interface.timer.text);
    interface.timer.dstrect.w = interface.timer.dstrect.h = 0;
}

SDL_Rect createOutline(SDL_Rect rect) {

    SDL_Rect outline;

    outline.x = rect.x - 1;
    outline.y = rect.y - 1;
    outline.w = rect.w + 2;
    outline.h = rect.h + 2;

    return outline;
}

void updateHealth(SDL_Rect& rect, int playerHealth, int maxPlayerHealth) {

    if (playerHealth <= 0) {
        rect.w = 0;
        return;
    }
    int health = playerHealth;

    float persent = (float)(playerHealth * 100) / maxPlayerHealth / 100;
    int negative = rect.w < 0 ? -1 : 1;
    
    rect.w = persent * HEALTH_RECT_WIDTH * negative;
}

void updateInterface(Interface& interface, int health1, int maxHealth1, int health2, int maxHealth2) {

    updateHealth(interface.health1, health1, maxHealth1);
    updateHealth(interface.health2, health2, maxHealth2);
}

void drawInterface(const Interface& interface) {

    SDL_SetRenderDrawColor(RENDER, 255, 0, 0, 0);
    SDL_RenderFillRect(RENDER, &interface.health1);
    SDL_RenderFillRect(RENDER, &interface.health2);

    static SDL_Rect
        outline1 = createOutline(interface.health1),
        outline2 = createOutline(interface.health2);

    SDL_SetRenderDrawColor(RENDER, 0, 0, 0, 0);
    SDL_RenderDrawRect(RENDER, &outline1);
    SDL_RenderDrawRect(RENDER, &outline2);
}