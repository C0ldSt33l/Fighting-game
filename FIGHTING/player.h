#pragma once

#include"texture.h"
#include"animation.h"


#define PLAYER_SPEED	WINDOW_WIDTH / 3 / FRAME_COUNT

#define PLAYER_ANGEL		  90
#define PLAYER_ANGEL_CHANGING 45


enum PlaerMoveStatus {
	PLAYER_NONE	   = -1,
	PLAYER_NEUTRAL,

	PLAYER_WALKING,
	PLAYER_JUMPING,
	PLAYER_CROUCHING,
	
	PLAYER_BLOCKING,
	PLAYER_ATTACKING
};


struct Animation;

struct Key {
	bool up		 = false,
		 down	 = false,
		 forward = false,
		 back	 = false,
		 
		 hitA = false,
		 hitB = false,
		 hitC = false;
};

struct Status {
	int attack = PLAYER_NONE,
		move   = PLAYER_NONE;
};

struct Player {
	
	Animation* animation = NULL;
	int curframe = -1;
	int curanimation = -1;

	SDL_Rect	   dstrect = { 0, 0, 0, 0 };
	SDL_Point	   speed = { 0, 0 };
	int			   direction = 0;
	
	Key			   key;
	Status		   status;
	
	int			   health	 = -1,
				   metre	 = -1;

	int time = -1;
};


void drawHitBox(const SDL_Rect& hitbox);

void changeDirection(Key& key, int* direction, SDL_Rect& dstrect, int move);

void updateKeyStatus(Key& key, SDL_Event& event);
void updatePlayerStatus(Key& key, Status& status, SDL_Rect& dstrect, int curframe, int framecount);
void updatePlayer(Player& player);

bool isInBoard(const SDL_Rect* dstrect);
void returnInBoard(SDL_Rect& dstrect);

void walk(SDL_Rect& dstrect, Key& key, int move, int speedx);
void jump(SDL_Rect& dstrect, int direction, int move, SDL_Point& speed);

void changeHP(Player& player1, Player& player2);

void initPlayer(Player& player);
void deInitPlayer(Player& player);
