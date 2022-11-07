#pragma once

#include"window.h"
#include"texture.h"
#include"animation.h"
#include"box.h"
#include"battle.h"


// PLAYER CONFIG
#define PLAYER_SPEED WINDOW_WIDTH / 3 / WINDOW_FRAME_COUNT

#define PLAYER_ANGEL		  90
#define PLAYER_ANGEL_CHANGING 45

#define INTERSECTION_MAX_WIDTH 100

#define CHARACTER_COUNT 6

#define CHARACTER_ANIMATION_PATH "files/assets/sprites/characters/"
#define CHARACTER_DATA_PATH      "files/data/"

enum PlayerStatus {
    PLAYER_NONE = -1,
    
    PLAYER_NEUTRAL,
    PLAYER_JUMPING,
    PLAYER_CROUCHING,

    PLAYER_WALKING_FORWARD,
    PLAYER_WALKING_BACK,

    PLAYER_ATTACKING,
    PLAYER_BLOCKING,
    PLAYER_TAUNTING,
    //PLAYER_TAKING_DAMAGE

};

enum PlayerSide {
    SIDE_NONE  =  0,
    SIDE_RIGHT = -1,
    SIDE_LEFT  =  1
};

enum AttackDirection {
    ATTACK_LOW  = 1,
    ATTACK_MID,
    ATTACK_HIGH,
};

extern const char character[CHARACTER_COUNT][12];


// STRUCTS
struct BattleKey;
struct Action;

struct PlayerKey {
    bool up      = false,
         down    = false,
         forward = false,
         back    = false;

    bool hitA  = false,
         hitB  = false,
         hitC  = false,
         block = false;

    bool taunt = false;
};

struct Status {
    int move   = PLAYER_NONE,
        attack = PLAYER_NONE;
};

struct Player {
    Action* action;
    
    int  curframe     = -1;
    int  curanimation = -1;
    bool isPlaying    = false;

    SDL_Rect dstrect;
    Box box;
    
    SDL_Point speed;
    
    int	angle  = 0;

    int side = SIDE_NONE;

    PlayerKey key;
    Status status;

    int maxHealth = -1,
        health    = -1;

    int  damage    = -1;
    bool canAttack = false;

    int time = 0;
};


// FUNCTIONS
void setPlayerRect(SDL_Rect& dstrect, const SDL_Rect& srcrect, int side);
Player* initPlayer(const char* name, int side);
void deInitPlayer(Player& player);

void updatePlayerKeystatus(PlayerKey& playerKey, int side, const BattleKey& battleKey);
void updatePlayerStatus(PlayerKey& key, Status& status, SDL_Rect& dstrect, int& angle, int curframe, int framecount, bool& canAttack);
void updatePlayerHP(Player& player1, Player& player2);
void updatePlayerAnimation(Player& player, int& move, int& attack);
void updatePlayer(Player& player, BattleKey& key);

void decreasePlayerHP(int& health, int damage);

void walk(SDL_Rect& dstrect, PlayerKey& key, const Status& status, int speedx, int side);

void setJumpAngle(PlayerKey& key, int& angle, const SDL_Rect& dstrect);
void jump(SDL_Rect& dstrect, int& angle, int move, int speedx, int speedy, PlayerKey& key, int side);

void updatePlayers(Player& player1, Player& player2, BattleKey& key);

void movePlayers(Player& player1, Player& player2);

bool isInBoard(const SDL_Rect& dstrect);
void returnInBoard(SDL_Rect& dstrect);

void drawPlayer(const Player& player, int i);
