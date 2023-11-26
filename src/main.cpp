
#include <thread>
#include "Game.h"

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 800

Game *game = nullptr;
const int FPS = 20;
const int frameDelay = 1000 / FPS;

void updateAndRenderHandler() {
    Uint32 frameStart;
    int frameTime;

    while (game->Running()) {
        frameStart = SDL_GetTicks();

        if (!game->gamePaused)
            game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

int main(int argc, char *argv[]) {
    game = new Game("Snek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    std::thread renderThread(updateAndRenderHandler);

    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    while (game->Running()) {
        game->handleEvents();
    }

    renderThread.join();

    game->clean();
    delete game;
    return 0;
}
