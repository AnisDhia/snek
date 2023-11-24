//
// Created by Anis on 11/23/2023.
//

#ifndef SNEK_MAP_H
#define SNEK_MAP_H

#include <SDL.h>

class Map {
public:
    //snake map
    Map();

    ~Map();

    void RenderMap(SDL_Renderer *renderer, int screenHeight, int screenWidth);

private:
    int screenHeight;
    int screenWidth;

};


#endif //SNEK_MAP_H
