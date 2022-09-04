#include"animation.h"
#include"texture.h"


// naoto's framedata
int NAOTO_FRAME_COUNT[ANIMATION_COUNT] = {
	9,
	10, 8, //9, 
	8, 9, 10,
	5, 10, 12,
	14, 15, 18
	//9, 9, 9
};

const char NAOTO_PATH[ANIMATION_COUNT][60] = {
	"files/assets/sprites/characters/naoto/neutral.png",

	"files/assets/sprites/characters/naoto/walk.png",
	"files/assets/sprites/characters/naoto/crouch.png",

	"files/assets/sprites/characters/naoto/normal a.png",
	"files/assets/sprites/characters/naoto/normal b.png",
	"files/assets/sprites/characters/naoto/normal c.png",

	"files/assets/sprites/characters/naoto/crouch normal a.png",
	"files/assets/sprites/characters/naoto/crouch normal b.png",
	"files/assets/sprites/characters/naoto/crouch normal c.png",

	"files/assets/sprites/characters/naoto/special a.png",
	"files/assets/sprites/characters/naoto/special b.png",
	"files/assets/sprites/characters/naoto/special c.png"
};


Animation createAnimation(const char* file, int framecount) {

	Animation animation;

	animation.texture = createTexture(file);
	animation.texture.dstrect.w /= framecount;
	
	animation.framecount = framecount;

	animation.speed = ANIMATION_TIME;

	return animation;
}

void initAnimation(Animation* array) {

	for (int i = 0; i < ANIMATION_COUNT; i++) {
		array[i] = createAnimation(NAOTO_PATH[i], NAOTO_FRAME_COUNT[i]);
	}
}

void changeAnimation(Status& status, Key& key, SDL_Rect& srcrect, int* curframe, int* curanimation) {

	*curframe = 0;
	srcrect.x = srcrect.y = 0;

	if (status.attack == PLAYER_ATTACKING) {
		switch (status.move) {
		case PLAYER_NEUTRAL:
			if		(key.hitA) *curanimation = ANIMATION_ATTACK_A;
			else if (key.hitB) *curanimation = ANIMATION_ATTACK_B;
			else			   *curanimation = ANIMATION_ATTACK_C;
			break;

		case PLAYER_WALKING:
			if (key.forward) {
				if		(key.hitA) *curanimation = ANIMATION_SPECIAL_ATTACK_A;
				else if (key.hitB) *curanimation = ANIMATION_SPECIAL_ATTACK_B;
				else			   *curanimation = ANIMATION_SPECIAL_ATTACK_C;
			}
			break;

		case PLAYER_CROUCHING:
			if		(key.hitA) *curanimation = ANIMATION_CROUCH_ATTACK_A;
			else if (key.hitB) *curanimation = ANIMATION_CROUCH_ATTACK_B;
			else			   *curanimation = ANIMATION_CROUCH_ATTACK_C;
			break;

		/*case PLAYER_JUMPING:
			if		(key.hitA) return ANIMATION_ATTACK_A;
			else if (key.hitB) return ANIMATION_ATTACK_B;
			else			   return ANIMATION_ATTACK_C;
			break;*/

		default:
			break;
		}
	}
	else {
		switch (status.move) {
		case PLAYER_NEUTRAL:   *curanimation = ANIMATION_NEUTRAL;
			break;
		case PLAYER_WALKING:   *curanimation = ANIMATION_WALK;
			break;
		case PLAYER_CROUCHING: *curanimation = ANIMATION_CROUCH;
			break;
		//case PLAYER_JUMPING:
		//	break;
		}
	}
}

void changeAnimationFrame(int* curframe, int* time, SDL_Rect& srcrect, int speed, int framecount) {

	int newtime = SDL_GetTicks();
	if (newtime - *time >= speed) {
		
		*curframe = (*curframe + 1) % framecount;
		srcrect.x = *curframe * srcrect.w;
		*time = newtime;
	}
}