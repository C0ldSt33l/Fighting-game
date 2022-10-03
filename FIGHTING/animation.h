#pragma once

#include<stdio.h>

#include"texture.h"
#include"player.h"
#include"box.h"


// ANIMATION CONFING
#define ANIMATION_COUNT  15
#define ANIMATION_TIME   1000 / 8

enum AnimationType {
    ANIMATION_NONE = -1,
    ANIMATION_NEUTRAL,

    ANIMATION_WALK,
    //ANIMATION_WALK_FORWARD,
    //ANIMATION_WALK_BACK,
    ANIMATION_CROUCH,
    //ANIMATION_JUMP,
    
    //ANIMATION_CROUCH_BLOCK,
    //ANIMATION_STAND_BLOCK,
    //ANIMATION_JUMP_BLOCK,

    ANIMATION_ATTACK_A,
    ANIMATION_ATTACK_B,
    ANIMATION_ATTACK_C,

    ANIMATION_CROUCH_ATTACK_A,
    ANIMATION_CROUCH_ATTACK_B,
    ANIMATION_CROUCH_ATTACK_C,
    
    ANIMATION_JUMP_ATTACK_A,
    ANIMATION_JUMP_ATTACK_B,
    ANIMATION_JUMP_ATTACK_C,

    ANIMATION_SPECIAL_ATTACK_A,
    ANIMATION_SPECIAL_ATTACK_B,
    ANIMATION_SPECIAL_ATTACK_C

    //ANIMATION_TAKE_DAMAGE,
    //ANIMATION_CROUCH_TAKE_DAMAGE,
    //ANIMATION_JUMP_TAKE_DAMAGE,
};

extern const char ANIMATION_TYPE[ANIMATION_COUNT][16];


// naoto's framedata
extern int NAOTO_FRAME_COUNT[ANIMATION_COUNT];

extern const char NAOTO_PATH[ANIMATION_COUNT][60];

//const SDL_Rect HURTBOX[ANIMATION_COUNT] = {
//    { 0, 15, 199, 390 },
//    
//    { 0, 15, 220, 389 },
//    { 0, 15, 176, 242 },
//    
//    { 0,  30, 311, 380 },
//    { 0, -15, 367, 471 },
//    { 0,  20, 419, 370 },
//    
//    { 0,  20, 347, 209 },
//    { 0, -15, 281, 436 },
//    { 0,  10, 465, 287 },
//
//    { 0, 10, 293, 249 },
//    { 0,  0, 335, 348 },
//    { 0, 10, 487, 260 },
//
//    { 0,  0, 357, 382 },
//    { 0, 10, 379, 385 },
//    { 0,  0, 361, 393 }
//};

//const SDL_Rect HITBOX[ANIMATION_COUNT] = {
//    { 0, 0, 0, 0 },
//
//    { 0, 0, 0, 0 },
//    { 0, 0, 0, 0 },
//
//    { 140, 100, 155, 100 },
//    { 190,   0, 165, 200 },
//    { 190,  60, 215, 150 },
//
//    { 130, 120, 200, 100 },
//    { 210,   0,  50, 230 },
//    { 210, 170, 240, 110 },
//    
//    { 210, 100,  70, 145 },
//    { 140, 100, 180, 235 },
//    { 230, 120, 245, 135 },
//    
//    { 180,  10, 165, 295 },
//    { 180, 150, 185, 100 },
//    { 180, 150, 165,  80 }
//};


// STRUCTS
struct PlayerKey;
struct Status;

struct Animation {
    Texture texture;

    int framecount = -1;
    int speed = -1;
};

struct Action {
    Animation animation;

    Box box;

    int damage = -1;
};


// FUNCTIONS
Animation createAnimation(const char* file, FILE* dataFile);
Action* initAction(const char* name, FILE* dataFile);

void changeAnimation(Status& status, PlayerKey& key, SDL_Rect& srcrect, int& curFrame, int& curAnimation, bool& isPlaying);
void changeAnimationFrame(bool& isPlaying, int& curframe, int& time, int move, Animation& animation);
