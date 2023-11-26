//
// Created by Anis on 11/10/2023.
//

#pragma once

#include <SDL.h>
#include <iostream>

typedef struct {
    SDL_Texture *texture;
    SDL_Rect destRect;
} Text;

// texts id enum
enum {
    HomeTitle,
    HomeSubTitle,
    GameOverTitle,
    GameOverSubTitle,
    GamePausedTitle,
    Score
} TextId;


class Game {
public:
    int screenWidth;
    int screenHeight;
    bool gamePaused = false;
    bool gameOver = false;
    Text *texts[sizeof(TextId) + 1] = {nullptr};

    Game(
            const char *title, // title of the window
            int xPos,  // x position of the window
            int yPos,  // y position of the window
            int screenWidth,  // width of the window
            int screenHeight,  // height of the window
            bool fullscreen  // fullscreen or not
    );

    ~Game();

    void init(
            const char *title, // title of the window
            int xPos,  // x position of the window
            int yPos,  // y position of the window
            int screenWidth,  // width of the window
            int screenHeight,  // height of the window
            bool fullscreen  // fullscreen or not
    );

    void handleEvents(); // handle user input
    void update(); // update all objects
    void render(); // render changes to the display
    void clean(); // free memory
    bool Running() { return isRunning; } // check if game is running

    static SDL_Renderer *renderer;
    static SDL_Event event;

private:
    bool isRunning;
    SDL_Window *window;
};

