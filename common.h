#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1280 // keep it 16:9
#define SCREEN_HEIGHT 720
#define TILE_SIZE 32
#define TILE_SCALE 2
#define FONT_NUM 200
#define MAX_FPS 60
#define MAX_CHARS 30
#define MAX_MAP_SIZE 10

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

typedef struct
{
    //int x;
    //int y;
    ///int s;
    char string1[MAX_CHARS];
    char string2[MAX_CHARS];
    int string1Len;
    int string2Len;
    //int length;
    int currentLetter;
    //int delay;
    int lastTick;
} TextStruct;

SDL_Renderer *renderer; // some things were meant to be global
SDL_Texture *font;
SDL_Rect fontTiles[FONT_NUM];

int levelMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int cameraOffsetX;
int cameraOffsetY;

#endif