//
// Created by Anis on 11/23/2023.
//

#include <SDL_rect.h>
#include "Snake.h"
#include "Game.h"

Snake::Snake(
        int x,
        int y,
        int direction,
        int speed
) : x(x), y(y), direction(direction), speed(speed) {}


Snake::~Snake() {}

void Snake::update(int screenWidth, int screenHeight) {
    if (x >= screenWidth) {
        x = 0;
    } else if (x < 0) {
        x = screenWidth;
    }
    if (y >= screenHeight) {
        y = 0;
    } else if (y < 0) {
        y = screenHeight;
    }

    for (int i = nTail - 1; i > 0; i--) {
        if (tailX[i] == x && tailY[i] == y) { // if snake eats itself then game over
            this->Die();
            break;
        }

        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = x;
    tailY[0] = y;

    switch (direction) {
        case 0:
            y -= speed;
            break;
        case 1:
            y += speed;
            break;
        case 2:
            x -= speed;
            break;
        case 3:
            x += speed;
            break;
        default:
            break;
    }
}

void Snake::render() {
    SDL_Rect rect = {x, y, 10, 10};
    SDL_SetRenderDrawColor(Game::renderer, 0, 100, 0, 255);
    SDL_RenderFillRect(Game::renderer, &rect);

    for (int i = 0; i < nTail; i++) {
        rect = {tailX[i], tailY[i], 10, 10};
        SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(Game::renderer, &rect);
    }
}

void Snake::changeDirection(int dir) {
    if (dir == 0 && direction != 1) {
        direction = dir;
    } else if (dir == 1 && direction != 0) {
        direction = dir;
    } else if (dir == 2 && direction != 3) {
        direction = dir;
    } else if (dir == 3 && direction != 2) {
        direction = dir;
    }
}

void Snake::addTail() {
    if (nTail == 0) {
        tailX[0] = x;
        tailY[0] = y;
    } else {
        tailX[nTail] = tailX[nTail - 1];
        tailY[nTail] = tailY[nTail - 1];
    }
    nTail++;
}

