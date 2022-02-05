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
#define MAX_FPS 60

typedef struct
{
    int x;
    int y;
    int s;
    char c1;
    char c2;
    int currentFrame;
    int delay;
    int lastTick;
} CursorStruct;

typedef struct
{
    int x;
    int y;
    int s;
    char *string;
    int length;
    int currentFrame;
    int delay;
    int lastTick;
} LineStruct;

SDL_Renderer *renderer; // some things were meant to be global
SDL_Texture *font;
SDL_Rect fontTiles[FONT_NUM];

#endif