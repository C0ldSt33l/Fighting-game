#pragma once

struct Box {
    SDL_Rect hitbox,
             hurtbox;
};


void setBoxCoords(SDL_Rect& box, int x, int y);
void setBoxSize(SDL_Rect& box, int w, int h);
void setBox(SDL_Rect& box, int x, int y, int w, int h);

void setPlayerBoxCoords(SDL_Rect& plrbox, int side, const SDL_Rect& box, const SDL_Rect& dstrect);
void setPlayerBoxSize(SDL_Rect& plrbox, int side, const SDL_Rect& box);
void setPlayerBox(SDL_Rect& plrbox, int side, const SDL_Rect& box, const SDL_Rect& dstrect);
void setPlayerBoxes(Box& plrboxes, int side, const Box& boxes, const SDL_Rect& dstrect);

void printBox(const SDL_Rect& box, const char* name);

void drawHitbox(const SDL_Rect& hitbox);
void drawHurtbox(const SDL_Rect& hurtbox);
void drawHitboxAndHurtbox(const SDL_Rect& hitbox, const SDL_Rect& hurtbox);