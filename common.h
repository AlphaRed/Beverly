#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280 // keep it 16:9
#define SCREEN_HEIGHT 720
#define TILE_SIZE 32
#define TILE_SCALE 2
#define FONT_NUM 200

typedef struct
{
    int x;
    int y;
    SDL_Rect sprite;
    int draw;
} ShipStruct;

SDL_Renderer *renderer; // some things were meant to be global
SDL_Texture *font;
SDL_Rect fontTiles[FONT_NUM];

#endif