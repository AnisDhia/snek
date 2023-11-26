//
// Created by Anis on 11/10/2023.
//

#include "Game.h"
#include "Snake.h"
#include "SDL_ttf.h"


#define GRID 10


TTF_Font *font;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

Text *createText(int x, int y, int w, int h, char *text);

void renderPauseScreen(int screenHeight, int screenWidth);

void renderGameOverScreen(int screenHeight, int screenWidth);

void renderScore(int screenHeight, int screenWidth, int score);

void renderKeys(int screenHeight, int screenWidth);

void spawnFood(int screenWidth, int screenHeight);

Game::Game(
        const char *title, // title of the window
        int xPos,  // x position of the window
        int yPos,  // y position of the window
        int screenWidth,  // width of the window
        int screenHeight,  // height of the window
        bool fullscreen  // fullscreen or not
) {
    init(title, xPos, yPos, screenWidth, screenHeight, fullscreen);
}

Game::~Game() {}


int cnt = 0;
Snake *snek;
Food food;

void Game::init(const char *title, int xpos, int ypos, int screenWidth, int screenHeight, bool fullscreen) {
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    std::cout << SDL_GetBasePath() << std::endl;


    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, screenWidth, screenHeight, flags);
        if (window) {
            std::cout << "Window created!: " << screenHeight << "x" << screenWidth << std::endl;
        }
        
        if (TTF_Init() < 0) {
            std::cout << "SDL_ttf could not be initialized SDL_ttf Error: " << TTF_GetError() << std::endl;
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

    if ((font = TTF_OpenFont("assets/ThaleahFat.ttf", 25)) == nullptr) {
        std::cout << "Font not found!" << std::endl;
    }

    snek = new Snake(
            screenWidth / 2,
            screenHeight / 2,
            0,
            10
    );


    spawnFood(screenWidth, screenHeight);

}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    snek->changeDirection(0);
                    std::cout << "UP" << std::endl;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    snek->changeDirection(1);
                    std::cout << "DOWN" << std::endl;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    snek->changeDirection(2);
                    std::cout << "LEFT" << std::endl;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    snek->changeDirection(3);
                    std::cout << "RIGHT" << std::endl;
                    break;
                case SDLK_SPACE:
                case SDLK_p:
                    gamePaused = !gamePaused;
                    break;
                case SDLK_r:
                    snek->reset();
                    gamePaused = false;
                    gameOver = false;
                    spawnFood(screenWidth, screenHeight);
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
    if (snek->isDead()) {
        gameOver = true;
        return;
    }
    if (gamePaused) {
        return;
    }

    snek->update(screenWidth, screenHeight);

    if (snek->getX() == food.x && snek->getY() == food.y) {
        snek->addTail();
        spawnFood(screenWidth, screenHeight);
        std::cout << "ADDED TAIL: " << snek->getNTail() << std::endl;
        std::cout << "FOOD: " << food.x << ", " << food.y << std::endl;
    }


}

void Game::render() {
    SDL_RenderClear(renderer);

    // This is where we would add stuff to render
    snek->render();
    // render food
    SDL_Rect rect = {food.x, food.y, 10, 10};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);


    if (snek->isDead()) {
        renderGameOverScreen(screenHeight, screenWidth);
    } else if (gamePaused) {
        renderPauseScreen(screenHeight, screenWidth);
    }
    renderScore(screenHeight, screenWidth, snek->getNTail());
    renderKeys(screenHeight, screenWidth);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}

void renderPauseScreen(int screenHeight, int screenWidth) {
    Text *title = createText(screenWidth / 2 - 125, screenHeight / 2 - 37, 250, 75, "Game Paused");
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);
}

void renderGameOverScreen(int screenHeight, int screenWidth) {
    Text *title = createText(screenWidth / 2 - 125, screenHeight / 2 - 37, 250, 75, "Game Over");
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);
}

void renderScore(int screenHeight, int screenWidth, int score) {
    char *scoreText = (char *) malloc(sizeof(char) * 10);
    sprintf(scoreText, "Score: %d", score);

    Text *title = createText(10, screenHeight - 50, 200, 50, scoreText);
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);
}

void renderKeys(int screenHeight, int screenWidth) {
    Text *title = createText(screenWidth - 550, screenHeight - 30, 100, 30, "WASD to move");
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);

    title = createText(screenWidth - 420, screenHeight - 30, 130, 30, "Space/P to pause");
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);

    title = createText(screenWidth - 250, screenHeight - 30, 100, 30, "R to restart");
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);

    title = createText(screenWidth - 120, screenHeight - 30, 100, 30, "ESC to quit");
    SDL_RenderCopy(Game::renderer, title->texture, nullptr, &title->destRect);
}

Text *createText(int x, int y, int w, int h, char *text) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_Rect rect = {x, y, w, h};
    Text *t = new Text;
    t->texture = texture;
    t->destRect = rect;
    return t;
}

void spawnFood(int screenWidth, int screenHeight) {
    food = {(rand() % (screenWidth / 10)) * 10, (rand() % (screenHeight / 10)) * 10};
    std::cout << "FOOD: " << food.x << ", " << food.y << std::endl;
}