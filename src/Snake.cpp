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
    tailX[0] = x;
    tailY[0] = y;
    for (int i = nTail - 1; i > 0; i--) {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }

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
    if (x > screenWidth) {
        x = 0;
    } else if (x < 0) {
        x = screenWidth;
    }

    if (y > screenHeight) {
        y = 0;
    } else if (y < 0) {
        y = screenHeight;
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
    direction = dir;
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

