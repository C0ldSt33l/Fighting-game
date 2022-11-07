#include"window.h"
#include"game.h"
#include"texture.h"
#include"font.h"
#include"menu.h"


int main(int argc, char* argv[]) {

    init();

    Game game;
    while (game.run) {
        processGame(game);
    }

    /*const char* about = "Course work on programming on the topic '2D fighting'\nwas performed by a student of BSTU group O - 21 - IVT - 2 - PO - B\nSychev Dmitry";
    Texture aboutText;
    SDL_Color color = { 255, 0, 0, 0 };
    aboutText = createText(loadFont(MENU_FONT, 70), about, color);
    centerText(aboutText.dstrect.x, aboutText.dstrect.w, WINDOW_WIDTH);
    centerText(aboutText.dstrect.y, aboutText.dstrect.h, WINDOW_HEIGHT);

    SDL_SetRenderDrawColor(RENDER, 255, 255, 255, 255);
    SDL_RenderClear(RENDER);
    SDL_RenderCopy(RENDER, aboutText.text, nullptr, &aboutText.dstrect);

    SDL_RenderPresent(RENDER);
    SDL_Delay(10'000);*/

    deInit(0);
    return 0;
}