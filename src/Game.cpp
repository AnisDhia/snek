//
// Created by Anis on 11/10/2023.
//

#include "Game.h"
#include "Snake.h"
#include "SDL_ttf.h"


SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game() {}

Game::~Game() {}

int cnt = 0;
Snake *snek;

void Game::init(const char *title, int xpos, int ypos, int screenWidth, int screenHeight, bool fullscreen) {
    this->screenHeight = screenWidth;
    this->screenWidth = screenHeight;

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, screenWidth, screenHeight, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    snek = new Snake(
            screenWidth / 2,
            screenHeight / 2,
            0,
            10
    );

}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    snek->changeDirection(0);
                    std::cout << "UP" << std::endl;
                    break;
                case SDLK_s:
                    snek->changeDirection(1);
                    std::cout << "DOWN" << std::endl;
                    break;
                case SDLK_a:
                    snek->changeDirection(2);
                    std::cout << "LEFT" << std::endl;
                    break;
                case SDLK_d:
                    snek->changeDirection(3);
                    std::cout << "RIGHT" << std::endl;
                    break;
                case SDLK_SPACE:
                    snek->addTail();
                    std::cout << "ADDED TAIL: " << snek->getNTail() << std::endl;
                    break;
                case SDLK_p:
                    gamePaused = !gamePaused;
                    break;
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                default:
                    break;
            }

        default:
            break;
    }
}

void Game::update() {
    snek->update(screenHeight, screenWidth);
}

void Game::render() {
    SDL_RenderClear(renderer);

    // This is where we would add stuff to render
    snek->render();

    TTF_Font *font = TTF_OpenFont("assets/ThaleahFat.ttf", 25);
    SDL_Color color = {0, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, std::to_string(snek->getNTail()).c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {0, 0, 100, 100};
    SDL_RenderCopy(renderer, texture, NULL, &rect);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}