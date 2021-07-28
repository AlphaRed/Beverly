#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 32
#define TILE_SCALE 2

typedef struct
{
    int x;
    int y;
    SDL_Rect sprite;
    int draw;
} ShipStruct;

SDL_Renderer *renderer; // somethings were meant to be global
SDL_Texture *font;

#endif