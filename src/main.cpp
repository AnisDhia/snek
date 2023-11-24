
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {
    const int FPS = 30;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Snek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while (game->Running()) {
        frameStart = SDL_GetTicks();


        game->handleEvents();
        if (!game->gamePaused)
            game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    delete game;
    return 0;
}
//