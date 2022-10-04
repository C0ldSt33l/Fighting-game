#pragma once

#include<stdio.h>

#include"texture.h"
#include"player.h"
#include"box.h"


// ANIMATION CONFING
#define ANIMATION_COUNT  17
#define ANIMATION_TIME   1000 / 8

enum AnimationType {
    ANIMATION_NONE = -1,
    ANIMATION_NEUTRAL,

    //ANIMATION_WALK,
    ANIMATION_WALK_FORWARD,
    ANIMATION_WALK_BACK,
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
    ANIMATION_SPECIAL_ATTACK_C,

    //ANIMATION_TAKE_DAMAGE,
    //ANIMATION_CROUCH_TAKE_DAMAGE,
    //ANIMATION_JUMP_TAKE_DAMAGE,
    
    ANIMATION_TAUNT,
};

extern const char ANIMATION_TYPE[ANIMATION_COUNT][16];


// naoto's framedata
extern int NAOTO_FRAME_COUNT[ANIMATION_COUNT];

extern const char NAOTO_PATH[ANIMATION_COUNT][60];


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
