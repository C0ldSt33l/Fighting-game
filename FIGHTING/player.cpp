#include<stdio.h>

#include"player.h"

void drawHitBox(const SDL_Rect& hitbox) {

	SDL_SetRenderDrawColor(RENDER, 255, 0, 0, 255);
	SDL_RenderDrawRect(RENDER, &hitbox);
	
	SDL_Rect rect = { 
		hitbox.x + 1, hitbox.y + 1, 
		hitbox.w - 2, hitbox.h - 2
	};
	SDL_SetRenderDrawColor(RENDER, 255, 0, 0, 125);
	SDL_RenderFillRect(RENDER, &hitbox);
}

void initPlayer(Player& player) {

	player.animation = (Animation*)malloc(sizeof(Animation) * ANIMATION_COUNT);
	if (!player.animation) {
		printf("Memory allocate error\n");
		deInit(1);
	}
	initAnimation(player.animation);
	
	player.curframe = 0;
	player.curanimation = ANIMATION_NEUTRAL;
	
	player.dstrect = player.animation[ANIMATION_NEUTRAL].texture.dstrect;
	player.dstrect.y = BOARD.h - player.dstrect.h;

	player.status.attack = player.status.move = PLAYER_NEUTRAL;

	player.speed.x = PLAYER_SPEED;
	player.speed.y = 1.5f * PLAYER_SPEED;
	player.direction = 90;

	player.health = 100;
	player.metre = 0;

	player.time = SDL_GetTicks();
}

void deInitPlayer(Player& player) {

	for (int i = 0; i < ANIMATION_COUNT; i++) {
		SDL_DestroyTexture(player.animation[i].texture.text);
	}
	free(player.animation);
	player.animation = NULL;

	player.dstrect = { 0, 0, 0, 0 };

	player.status.attack = player.status.move = PLAYER_NONE;

	player.speed = { 0, 0 };

	player.direction = 0;

	player.health = -1;
	player.metre = -1;

	player.time = -1;
}

void changeDirection(Key& key, int* direction, SDL_Rect& dstrect, int move) {

	if (move != PLAYER_JUMPING) { return; }
	
	int height = BOARD.h - dstrect.h;
	if (dstrect.y >= height) {
		*direction = 90;
	}
	if (dstrect.y == height) {
		
		if (key.forward && !key.back)
			*direction -= 45;
		if (!key.forward && key.back)
			*direction += 45;
	}
	if (dstrect.y <= WINDOW_HEIGHT / 3) {
		*direction = -90;
	}
}

void updateKeyStatus(Key& key, SDL_Event& event) {

	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_D:	  key.forward = true;
			break;
		case SDL_SCANCODE_A:	  key.back = true;
			break;
		case SDL_SCANCODE_W:	  key.up = true;
			break;
		case SDL_SCANCODE_S:	  key.down = true;
			break;

		case SDL_SCANCODE_U:      key.hitA = true;
			break;
		case SDL_SCANCODE_I:      key.hitB = true;
			break;
		case SDL_SCANCODE_O:      key.hitC = true;
			break;

		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_D:	  key.forward = false;
			break;
		case SDL_SCANCODE_A:	  key.back = false;
			break;
		case SDL_SCANCODE_W:	  key.up = false;
			break;
		case SDL_SCANCODE_S:	  key.down = false;
			break;

		case SDL_SCANCODE_U:      key.hitA = false;
			break;
		case SDL_SCANCODE_I:      key.hitB = false;
			break;
		case SDL_SCANCODE_O:      key.hitC = false;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void updatePlayerStatus(Key& key, Status& status, SDL_Rect& dstrect, int curframe, int framecount) {

	bool isAttacking = key.hitA || key.hitB || key.hitC;
	
	switch (status.attack) {
	case PLAYER_NEUTRAL:
		if		(isAttacking)			   { status.attack = PLAYER_ATTACKING; }
		else if (key.back && !isAttacking) { status.attack = PLAYER_BLOCKING; }
		break;

	case PLAYER_ATTACKING:
		if (curframe == framecount - 1) { status.attack = PLAYER_NEUTRAL; }
		break;

	case PLAYER_BLOCKING:
		if (!key.back) status.attack = PLAYER_NEUTRAL;
		break;

	default:
		break;
	}

	if (!isAttacking) {
		
		bool isWalking = key.forward || key.back;
		switch (status.move) {
		case PLAYER_NEUTRAL:
			if		(key.up && !key.down) { status.move = PLAYER_JUMPING; }
			else if (!key.up && key.down) { status.move = PLAYER_CROUCHING; }
			else if (isWalking)			  { status.move = PLAYER_WALKING; }
			break;

		case PLAYER_WALKING:
			if		(key.up && !key.down) { status.move = PLAYER_JUMPING; }
			else if (!key.up && key.down) { status.move = PLAYER_CROUCHING; }
			else if	(!isWalking)		  { status.move = PLAYER_NEUTRAL; }
			break;

		case PLAYER_JUMPING:
			if (dstrect.y == BOARD.h - dstrect.h) { status.move = PLAYER_NEUTRAL; }
			break;

		case PLAYER_CROUCHING:
			if (!key.down) { status.move = PLAYER_NEUTRAL; }
			break;
		}
	}
}

bool isInBoard(const SDL_Rect* dstrect) {

	SDL_Point point1, point2;
	point1 = { dstrect->x, dstrect->y };
	point2 = { point1.x + dstrect->w,
			   point1.y + dstrect->h };

	return SDL_PointInRect(&point1, &BOARD) && SDL_PointInRect(&point2, &BOARD);
}

void returnInBoard(SDL_Rect& dstrect) {

	if (isInBoard(&dstrect)) return;

	if (dstrect.x < 0)						  dstrect.x = 0;
	if (dstrect.x > WINDOW_WIDTH - dstrect.w) dstrect.x = WINDOW_WIDTH - dstrect.w;
	if (dstrect.y < 0)						  dstrect.y = 0;
	if (dstrect.y > BOARD.h - dstrect.h)	  dstrect.y = BOARD.h - dstrect.h;
}

void walk(SDL_Rect& dstrect, Key& key, int move, int speedx) {

	if (move != PLAYER_WALKING) return;

	if (key.forward && !key.back) {
		dstrect.x += speedx;
	}
	if (!key.forward && key.back) {
		dstrect.x -= speedx;
	}
}

void jump(SDL_Rect& dstrect, int direction, int move, SDL_Point& speed) {

	if (move != PLAYER_JUMPING) return;

	dstrect.x += speed.y * cos(direction * M_PI / 180);
	dstrect.y -= speed.y * sin(direction * M_PI / 180);
}

void changeHP(Player& player1, Player& player2) {

	if (player1.status.attack != PLAYER_ATTACKING && player2.status.attack != PLAYER_ATTACKING ||
		player1.status.attack == player2.status.attack) return;
}

void updatePlayer(Player& player) {

	int move   = player.status.move,
		attack = player.status.attack;
	updatePlayerStatus(player.key, player.status, player.dstrect, player.curframe, player.animation[player.curanimation].framecount);
	if (move != player.status.move || attack != player.status.attack) {
		changeAnimation(player.status, player.key, player.animation[player.curanimation].texture.dstrect, &player.curframe, &player.curanimation);

		player.dstrect.w = player.animation[player.curanimation].texture.dstrect.w;
		player.dstrect.h = player.animation[player.curanimation].texture.dstrect.h;
		player.dstrect.y = BOARD.h - player.dstrect.h;
	}
	
	changeAnimationFrame(&player.curframe, &player.time,
		player.animation[player.curanimation].texture.dstrect,
		player.animation[player.curanimation].speed,
		player.animation[player.curanimation].framecount);

	walk(player.dstrect, player.key, player.status.move, player.speed.x);
	
	changeDirection(player.key, &player.direction, player.dstrect, player.status.move);
	jump(player.dstrect, player.direction, player.status.move, player.speed);

	returnInBoard(player.dstrect);
}