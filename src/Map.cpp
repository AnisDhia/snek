//
// Created by Anis on 11/23/2023.
//

#include "Map.h"

int nMapHeight = 20;
int nMapWidth = 20;
int nTileSize = 16;
int nBorderWidth = 4;
int nBorderHeight = 4;
int nBorderOffsetX = 10;
int nBorderOffsetY = 10;

int nScreenWidth = nMapWidth * nTileSize + nBorderWidth * 2 + nBorderOffsetX * 2;
int nScreenHeight = nMapHeight * nTileSize + nBorderHeight * 2 + nBorderOffsetY * 2;

//int map[nMapHeight][nMapWidth] = {0};

