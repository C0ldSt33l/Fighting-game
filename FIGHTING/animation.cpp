#include<stdio.h>

#include"animation.h"
#include"texture.h"
#include"player.h"


const char ANIMATION_TYPE[ANIMATION_COUNT][16] = {
    "neutral",

    "walk",
    //"walk forward",
    //"walk back",
    "crouch",

    //"stand block",
    //"crouch block",
    //"jump block",

    "normal a",
    "normal b",
    "normal c",

    "crouch normal a",
    "crouch normal b",
    "crouch normal c",

    "jump normal a",
    "jump normal b",
    "jump normal c",

    "special a",
    "special b",
    "special c"

    //"stand take damage",
    //"crouch take damage",
    //"jump take damage",
};


Animation createAnimation(const char* file, FILE* dataFile) {
    
    Animation animation;

    fscanf_s(dataFile, "%d", &animation.framecount);
    fscanf_s(dataFile, "%d", &animation.speed);

    animation.texture = createTexture(file);
    animation.texture.dstrect.w /= animation.framecount;

    return animation;
}

Action* initAction(const char* name, FILE* dataFile) {

    Action* action = (Action*)malloc(sizeof(Action) * ANIMATION_COUNT);
    if (!action) {
        printf("Memory allocate error for player.action\n");
        deInit(1);
    }

    char fullpath[100];

    for (int i = 0; i < ANIMATION_COUNT; i++) {
        sprintf_s(fullpath, 100, "%s%s/%s%s", CHARACTER_ANIMATION_PATH, name, ANIMATION_TYPE[i], ".png");
        action[i].animation = createAnimation(fullpath, dataFile);
        
        SDL_Rect rect;
        fscanf_s(dataFile, "%d%d%d%d", &rect.x, &rect.y, &rect.w, &rect.h);
        action[i].box.hurtbox = rect;
        fscanf_s(dataFile, "%d%d%d%d", &rect.x, &rect.y, &rect.w, &rect.h);
        action[i].box.hitbox = rect;

        fscanf_s(dataFile, "%d", &action[i].damage);
    }

    return action;
}

void changeAnimation(Status& status, PlayerKey& key, SDL_Rect& srcrect, int& curFrame, int& curAnimation, bool& isPlaying) {

    curFrame = 0;
    srcrect.x = srcrect.y = 0;
    isPlaying = true;

    if (status.attack) {
        switch (status.attack) {
        case PLAYER_ATTACKING:
            switch (status.move) {
            case PLAYER_NEUTRAL:
                if      (key.hitA) curAnimation = ANIMATION_ATTACK_A;
                else if (key.hitB) curAnimation = ANIMATION_ATTACK_B;
                else			   curAnimation = ANIMATION_ATTACK_C;
                break;

            case PLAYER_WALKING:
                if (key.forward) {
                    if      (key.hitA) curAnimation = ANIMATION_SPECIAL_ATTACK_A;
                    else if (key.hitB) curAnimation = ANIMATION_SPECIAL_ATTACK_B;
                    else			   curAnimation = ANIMATION_SPECIAL_ATTACK_C;
                }
                break;

            case PLAYER_CROUCHING:
                if      (key.hitA) curAnimation = ANIMATION_CROUCH_ATTACK_A;
                else if (key.hitB) curAnimation = ANIMATION_CROUCH_ATTACK_B;
                else			   curAnimation = ANIMATION_CROUCH_ATTACK_C;
                break;

            case PLAYER_JUMPING:
                if      (key.hitA) curAnimation = ANIMATION_JUMP_ATTACK_A;
                else if (key.hitB) curAnimation = ANIMATION_JUMP_ATTACK_B;
                else			   curAnimation = ANIMATION_JUMP_ATTACK_C;
                break;
            }
            break;


        /*case PLAYER_BLOCKING:
            switch (status.move) {
            case PLAYER_NEUTRAL:   curanimation = ANIMATION_STAND_BLOCK;
                break;
            case PLAYER_CROUCHING: curanimation = ANIMATION_CROUCH_BLOCK;
                break;
            case PLAYER_JUMPING:   curanimation = ANIMATION_JUMP_BLOCK;
                break;
            }*/
        }
    }
    else {
        switch (status.move) {
        case PLAYER_JUMPING:   //curanimation = ANIMATION_JUMP;
        case PLAYER_NEUTRAL:   curAnimation = ANIMATION_NEUTRAL;
            break;
        case PLAYER_WALKING:   curAnimation = ANIMATION_WALK;
            //curanimation = key.forward ? ANIMATION_WALK_FORWARD : ANIMATION_WALK_BACK;
            break;
        case PLAYER_CROUCHING: curAnimation = ANIMATION_CROUCH;
            break;
        }
    }
}

void changeAnimationFrame(bool& isPlaying, int& curframe, int& time, int move, Animation& animation) {

    //if (!isPlaying) return;
    
    static int newtime;
    newtime = SDL_GetTicks();

    if (newtime - time >= animation.speed) {
        curframe = (curframe + 1) % animation.framecount;
        animation.texture.dstrect.x = curframe * animation.texture.dstrect.w;
        time = newtime;
    }

    /*if (move == PLAYER_JUMPING && curframe == animation.framecount - 1) {
        isPlaying = false;
    }*/
}