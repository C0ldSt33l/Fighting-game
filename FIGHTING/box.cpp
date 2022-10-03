#include<SDL.h>

#include"box.h"
#include"window.h"
#include"player.h"

void setBoxCoords(SDL_Rect& box, int x, int y) {

    box.x = x;
    box.y = y;
}

void setBoxSize(SDL_Rect& box, int w, int h) {

    box.w = w;
    box.h = h;
}

void setBox(SDL_Rect& box, int x, int y, int w, int h) {

    setBoxCoords(box, x, y);
    setBoxSize(box, w, h);
}

void setPlayerBoxCoords(SDL_Rect& plrbox, int side, const SDL_Rect& box, const SDL_Rect& dstrect) {
    
    plrbox.x = dstrect.x;
    plrbox.x += side > 0 ? box.x : dstrect.w - (box.x + box.w);
    
    plrbox.y = dstrect.y + box.y;
}

void setPlayerBoxSize(SDL_Rect& plrbox, int side, const SDL_Rect& box) {

    plrbox.w = box.w;
    plrbox.h = box.h;
}

void setPlayerBox(SDL_Rect& plrbox, int side, const SDL_Rect& box, const SDL_Rect& dstrect) {

    setPlayerBoxCoords(plrbox, side, box, dstrect);
    setPlayerBoxSize(plrbox, side, box);
}

void setPlayerBoxes(Box& plrboxes, int side, const Box& boxes, const SDL_Rect& dstrect) {

    setPlayerBox(plrboxes.hitbox, side, boxes.hitbox, dstrect);
    setPlayerBox(plrboxes.hurtbox, side, boxes.hurtbox, dstrect);
}

void printBox(const SDL_Rect& box, const char* name) {

    printf("%s\n", name);
    printf("x: %d\n", box.x);
    printf("y: %d\n", box.y);
    printf("w: %d\n", box.w);
    printf("h: %d\n\n", box.h);
}

void drawHitbox(const SDL_Rect& hitbox) {

    if (!hitbox.w) return;

    SDL_SetRenderDrawColor(RENDER, 255, 0, 0, 0);
    SDL_RenderDrawRect(RENDER, &hitbox);
}

void drawHurtbox(const SDL_Rect& hurtbox) {

    SDL_SetRenderDrawColor(RENDER, 0, 255, 0, 0);
    SDL_RenderDrawRect(RENDER, &hurtbox);
}

void drawHitboxAndHurtbox(const SDL_Rect& hitbox, const SDL_Rect& hurtbox) {

    drawHitbox(hitbox);
    drawHurtbox(hurtbox);
}