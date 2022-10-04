#include<stdio.h>

#include"player.h"
#include"animation.h"
#include"box.h"
#include"battle.h"


const char character[PLAYER_COUNT][12] = {
    "hakuman",
    "kagura"
    "naoto",
    "tager",
};


void setPlayerRect(SDL_Rect& dstrect, const SDL_Rect& srcrect, int side) {

    dstrect = srcrect;
    dstrect.x = side > SIDE_NONE ? 0 : WINDOW_WIDTH - dstrect.w;
    dstrect.y = BOARD.h - dstrect.h;
}

void initPlayer(Player& player, const char* name, int side) {

    char dataPath[100];
    sprintf_s(dataPath, 100, "%s%s%s", CHARACTER_DATA_PATH, name, ".txt");
    FILE* file;
    if (fopen_s(&file, dataPath, "r")) {
        printf("couldn't open file: %s\n", dataPath);
        exit(1);
    }

    fscanf_s(file, "%d", &player.maxHealth);
    player.health = player.maxHealth;

    player.action = initAction(name, file);
    fclose(file);
    
    player.curframe = 0;
    int i = ANIMATION_NEUTRAL;
    player.curanimation = i;
    player.isPlaying = true;

    
    setPlayerRect(player.dstrect, player.action[i].animation.texture.dstrect, side);
    setPlayerBoxes(player.box, side, player.action[i].box, player.dstrect);


    player.damage    = 0;
    player.canAttack = true;

    player.status.attack = player.status.move = PLAYER_NEUTRAL;

    player.speed.x = PLAYER_SPEED;
    player.speed.y = 1.5f * PLAYER_SPEED;
    
    player.angle = -90;
    player.side = side;

    player.time = SDL_GetTicks();

}

void deInitPlayer(Player& player) {

    for (int i = 0; i < ANIMATION_COUNT; i++) {
        SDL_DestroyTexture(player.action[i].animation.texture.text);
        player.action[i].animation.texture.text = nullptr;
        player.action[i].animation.framecount = player.action[i].animation.speed = 0;
        player.action[i].animation.texture.dstrect = { 0, 0, 0, 0 };
    }
    free(player.action);
    player.action = nullptr;

    player.dstrect = player.box.hitbox = player.box.hurtbox = { 0, 0, 0, 0 };

    player.status.attack = player.status.move = PLAYER_NONE;

    player.speed = { 0, 0 };
    player.angle = -90;
    player.side = SIDE_NONE;

    player.health = player.maxHealth = -1;

    player.time = -1;
}

void setJump(PlayerKey& key, int& angle, const SDL_Rect& dstrect) {
    
    if (dstrect.y == BOARD.h - dstrect.h) {
        angle = 90;
        if      (key.forward && !key.back)  angle -= PLAYER_ANGEL_CHANGING;
        else if (!key.forward && key.back)  angle += PLAYER_ANGEL_CHANGING;
    }

    if (dstrect.y <= WINDOW_HEIGHT / 3) {
        angle = -angle;
    }
}

void updatePlayerKeystatus(PlayerKey& playerKey, int side, const BattleKey& battleKey) {

    if (side == SIDE_LEFT) {
        playerKey.up      = battleKey.w;
        playerKey.down    = battleKey.s;
        playerKey.back    = battleKey.a;
        playerKey.forward = battleKey.d;

        playerKey.hitA  = battleKey.u;
        playerKey.hitB  = battleKey.i;
        playerKey.hitC  = battleKey.o;
        playerKey.block = battleKey.q;

        playerKey.taunt = battleKey.e;
    }
    else {
        playerKey.up      = battleKey.up;
        playerKey.down    = battleKey.down;
        playerKey.back    = battleKey.right;
        playerKey.forward = battleKey.left;

        playerKey.hitA  = battleKey.n4;
        playerKey.hitB  = battleKey.n5;
        playerKey.hitC  = battleKey.n6;
        playerKey.block = battleKey.n2;

        playerKey.taunt = battleKey.n8;
    }
}

void updatePlayerStatus(PlayerKey& key, Status& status, SDL_Rect& dstrect, int& angle ,int curframe, int framecount, bool& canAttack) {

    bool isAttacking = key.hitA || key.hitB || key.hitC;
    
    switch (status.attack) {
    case PLAYER_NEUTRAL: {
        bool canTaunt = status.move == PLAYER_CROUCHING || status.move == PLAYER_NEUTRAL;
        if (isAttacking) { status.attack = PLAYER_ATTACKING; }
        else if (key.block && !isAttacking) { status.attack = PLAYER_BLOCKING; }
        else if (key.taunt && canTaunt) { status.attack = PLAYER_TAUNTING; }
        break;
    }

    case PLAYER_ATTACKING:
        if (curframe == framecount - 1 || dstrect.y + dstrect.h > BOARD.h) { 
            status.attack = PLAYER_NEUTRAL;
            canAttack = true;
        }
        break;

    case PLAYER_BLOCKING:
        if (!key.block) status.attack = PLAYER_NEUTRAL;
        break;

    case PLAYER_TAUNTING:
       if (curframe == framecount - 1) { status.attack = PLAYER_NEUTRAL; }
       break;
    }

    if (status.attack != PLAYER_ATTACKING && status.attack != PLAYER_TAUNTING) {
        
        bool isWalking = key.forward && !key.back || !key.forward && key.back;
        switch (status.move) {
        case PLAYER_NEUTRAL:
            if		(key.up && !key.down)                    { status.move = PLAYER_JUMPING; }
            else if (!key.up && key.down)                    { status.move = PLAYER_CROUCHING; }
            else if (!key.block && isWalking && key.forward) { status.move = PLAYER_WALKING_FORWARD; }
            else if (!key.block && isWalking && key.back)    { status.move = PLAYER_WALKING_BACK; }
            break;

        case PLAYER_WALKING_FORWARD:
            if      (key.up && !key.down)     { status.move = PLAYER_JUMPING; }
            else if (!key.up && key.down)     { status.move = PLAYER_CROUCHING; }
            else if (!isWalking || key.block) { status.move = PLAYER_NEUTRAL; }
            else if (isWalking && key.back)   { status.move = PLAYER_WALKING_BACK; }
            break;

        case PLAYER_WALKING_BACK:
            if      (key.up && !key.down)      { status.move = PLAYER_JUMPING; }
            else if (!key.up && key.down)      { status.move = PLAYER_CROUCHING; }
            else if (!isWalking || key.block)  { status.move = PLAYER_NEUTRAL; }
            else if (isWalking && key.forward) { status.move = PLAYER_WALKING_FORWARD; }
            break;

        case PLAYER_JUMPING:
            if (dstrect.y + dstrect.h >= BOARD.h) status.move = PLAYER_NEUTRAL; 
            break;

        case PLAYER_CROUCHING:
            if (!key.down) { status.move = PLAYER_NEUTRAL; }
            break;
        }
    }
}

bool isInBoard(const SDL_Rect& dstrect) {

    return dstrect.x >= 0 && dstrect.x + dstrect.w <= BOARD.w;
}

void returnInBoard(SDL_Rect& dstrect) {

    if (isInBoard(dstrect)) return;

    dstrect.x = dstrect.x < 0 ? 0 : WINDOW_WIDTH - dstrect.w;

}

void walk(SDL_Rect& dstrect, PlayerKey& key, const Status& status, int speedx, int side) {

    if (status.move != PLAYER_WALKING_FORWARD && status.move != PLAYER_WALKING_BACK ||
        status.attack == PLAYER_BLOCKING) return;

    static int offset;
    offset = speedx * side;

    if (key.forward) { dstrect.x += offset; }
    if (key.back)    { dstrect.x -= offset; }

    returnInBoard(dstrect);
}

void jump(SDL_Rect& dstrect, int& angle, int move, int speedx, int speedy, PlayerKey& key, int side) {

    if (move != PLAYER_JUMPING) return;

    setJump(key, angle, dstrect);

    static float offsetx, offsety;
    offsetx = speedx * cos(angle * M_PI / 180) * side;
    offsety = speedy * sin(angle * M_PI / 180);

    dstrect.y -= offsety;
    dstrect.x += offsetx;

    returnInBoard(dstrect);
}

void decreasePlayerHP(int& health, int damage) {
    if (!health) return;

    health = health - damage > 0 ? health - damage : 0;
}

void updatePlayerHP(Player& player1, Player& player2) {

    if (SDL_HasIntersection(&player1.box.hurtbox, &player2.box.hitbox) && player2.canAttack) {
        float multiply = player1.status.attack == PLAYER_BLOCKING ? 0.5 : 1;
        decreasePlayerHP(player1.health, player2.damage * multiply);
        player2.canAttack = false;
    }
}

void updatePlayerAnimation(Player& player) {

    static int move, attack;
    move = player.status.move;
    attack = player.status.attack;

    updatePlayerStatus(player.key, player.status, player.dstrect, player.angle, player.curframe, player.action[player.curanimation].animation.framecount, player.canAttack);
    if (move != player.status.move || attack != player.status.attack) {
        changeAnimation(player.status, player.key, player.action[player.curanimation].animation.texture.dstrect, player.curframe, player.curanimation, player.isPlaying);

        int i = player.curanimation;
        player.dstrect.h = player.action[i].animation.texture.dstrect.h;
        player.dstrect.w = player.action[i].animation.texture.dstrect.w;
        if (player.status.move != PLAYER_JUMPING) {
            player.dstrect.y = BOARD.h - player.dstrect.h;
        }

        player.damage = player.action[i].damage;

        setPlayerBox(player.box.hitbox, player.side, player.action[i].box.hitbox, player.dstrect);
        setPlayerBox(player.box.hurtbox, player.side, player.action[i].box.hurtbox, player.dstrect);
    }

    int i = player.curanimation;
    changeAnimationFrame(player.isPlaying, player.curframe, player.time, player.status.move, player.action[i].animation);
}

void updatePlayer(Player& player, BattleKey& key) {
    
    updatePlayerKeystatus(player.key, player.side, key);
    updatePlayerAnimation(player);
    
    setPlayerBoxCoords(player.box.hitbox, player.side, player.action[player.curanimation].box.hitbox, player.dstrect);
    setPlayerBoxCoords(player.box.hurtbox, player.side, player.action[player.curanimation].box.hurtbox, player.dstrect);
}

void movePlayers(Player& player1, Player& player2) {

    static int speedX1, speedX2;
    speedX1 = player1.speed.x;
    speedX2 = player2.speed.x;

    static SDL_Rect intersection;
    SDL_IntersectRect(&player1.dstrect, &player2.dstrect, &intersection);
    if (intersection.w >= INTERSECTION_MAX_WIDTH) {
        if (player1.key.forward || player1.status.move == PLAYER_JUMPING)
            speedX1 = 0;
        if (player2.key.forward || player2.status.move == PLAYER_JUMPING)
            speedX2 = 0;
    }

    walk(player1.dstrect, player1.key, player1.status, speedX1, player1.side);
    walk(player2.dstrect, player2.key, player2.status, speedX2, player2.side);

    jump(player1.dstrect, player1.angle, player1.status.move, speedX1, player1.speed.y, player1.key, player1.side);
    jump(player2.dstrect, player2.angle, player2.status.move, speedX2, player2.speed.y, player2.key, player2.side);
}

void updatePlayers(Player& player1, Player& player2, BattleKey& key) {

    updatePlayer(player1, key);
    updatePlayer(player2, key);

    movePlayers(player1, player2);

    updatePlayerHP(player1, player2);
    updatePlayerHP(player2, player1);
}

void drawPlayer(const Player& player, int i) {
    
    static SDL_RendererFlip flip;
    flip = player.side == SIDE_LEFT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(RENDER, player.action[i].animation.texture.text, &player.action[i].animation.texture.dstrect, &player.dstrect, 0, 0, flip);

    drawHitbox(player.box.hitbox);
    drawHurtbox(player.box.hurtbox);
}