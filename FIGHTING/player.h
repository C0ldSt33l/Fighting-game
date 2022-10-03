#pragma once

#include"window.h"
#include"texture.h"
#include"animation.h"
#include"box.h"
#include"battle.h"

//     TASKS:
// * add block


// PLAYER CONFIG
#define PLAYER_SPEED WINDOW_WIDTH / 3 / WINDOW_FRAME_COUNT

#define PLAYER_ANGEL		  90
#define PLAYER_ANGEL_CHANGING 45

#define INTERSECTION_MAX_WIDTH 100

#define PLAYER_COUNT 4

#define CHARACTER_ANIMATION_PATH "files/assets/sprites/characters/"
#define CHARACTER_DATA_PATH      "files/data/"

enum PlayerStatus {
    PLAYER_NONE = -1,
    PLAYER_NEUTRAL,

    PLAYER_WALKING,
    PLAYER_JUMPING,
    PLAYER_CROUCHING,

    PLAYER_ATTACKING,
    PLAYER_BLOCKING,
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

extern const char character[PLAYER_COUNT][12];


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
    
    int	angel  = 0;

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
void initPlayer(Player& player, const char* name, int side);
void deInitPlayer(Player& player);

void updatePlayerKeystatus(PlayerKey& playerKey, int side, const BattleKey& battleKey);
void updatePlayerStatus(PlayerKey& key, Status& status, SDL_Rect& dstrect, int& angel, int curframe, int framecount, bool& canAttack);
void updatePlayerHP(Player& player1, Player& player2);
void updatePlayerAnimation(Player& player);

void decreasePlayerHP(int& health, int damage);

void updatePlayer(Player& player, BattleKey& key);
void updatePlayers(Player& player1, Player& player2, BattleKey& key);

bool isInBoard(const SDL_Rect& dstrect);
void returnInBoard(SDL_Rect& dstrect);

void walk(SDL_Rect& dstrect, PlayerKey& key, int move, int speedx, int side);

void setJump(PlayerKey& key, int& angel, const SDL_Rect& dstrect);
void jump(SDL_Rect& dstrect, int& angel, int move, int speedx, int speedy, PlayerKey& key, int side);

void movePlayers(Player& player1, Player& player2);

void drawPlayer(const Player& player, int i);
