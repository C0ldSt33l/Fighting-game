#include<stdio.h>

#include"file.h"
#include"player.h"
#include"animation.h"

void writePlayerInFile(Player& player, const char* filename) {

    FILE* file;
    if (fopen_s(&file, filename, "w")) {
        printf("Couldn't write in file: %s\n", filename);
        deInit(1);
    }

    fprintf_s(file, "%d", player.maxHealth);

    for (int i = 0; i < ANIMATION_COUNT; i++) {
        Action action = player.action[i];
        fprintf_s(file, "\n%2d  %3d  %3d %3d %3d %3d   %3d %3d %3d %3d   %3d",
            action.animation.framecount, action.animation.speed,
            
            action.box.hurtbox.x, action.box.hurtbox.y, action.box.hurtbox.w, action.box.hurtbox.h,
            action.box.hitbox.x,  action.box.hitbox.y,  action.box.hitbox.w,  action.box.hitbox.h,

            action.damage);
    }

    fclose(file);
}