#pragma once

#include"texture.h"
#include"player.h"


// Defines
#define ANIMATION_COUNT  12
#define ANIMATION_TIME   1000 / 8


// Enums
enum AnimationNum {
	ANIMATION_NONE = -1,
	ANIMATION_NEUTRAL,

	ANIMATION_WALK,
	ANIMATION_CROUCH,
	//ANIMATION_JUMP,

	ANIMATION_ATTACK_A,
	ANIMATION_ATTACK_B,
	ANIMATION_ATTACK_C,

	ANIMATION_CROUCH_ATTACK_A,
	ANIMATION_CROUCH_ATTACK_B,
	ANIMATION_CROUCH_ATTACK_C,

	ANIMATION_SPECIAL_ATTACK_A,
	ANIMATION_SPECIAL_ATTACK_B,
	ANIMATION_SPECIAL_ATTACK_C

	//ANIMATION_JUMP_ATTACK_A,
	//ANIMATION_JUMP_ATTACK_B,
	//ANIMATION_JUMP_ATTACK_C
};


// naoto's framedata
extern int NAOTO_FRAME_COUNT[ANIMATION_COUNT];

extern const char NAOTO_PATH[ANIMATION_COUNT][60];


// Structs
struct Key;
struct Status;

struct Animation {
	Texture texture;

	int framecount = -1;
	int speed      = -1;
};


// Functions
Animation createAnimation(const char* file, int framecount);

void initAnimation(Animation* array);

void changeAnimation(Status& status, Key& key, SDL_Rect& srcrect, int* curframe, int* curanimation);
void changeAnimationFrame(int* curframe, int* time, SDL_Rect& srcrect, int speed, int framecount);
