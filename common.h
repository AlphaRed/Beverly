#ifndef COMMON_H
#define COMMON_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define TILE_WIDTH      16
#define TILE_HEIGHT     16
#define FONT_NUM 200
#define MAX_FPS 60
#define MAX_CHARS 80 // equals 1280 / 8px / 2 scale

typedef enum {MENU, GAME} Gamestate;

typedef struct DrawList_t {
    int id; // might use as an identifier!
    SDL_Texture *img;
    SDL_FRect srcRect;
    SDL_FRect destRect;
    struct DrawList_t *next;
} DrawList_t;

typedef struct Client_t { // For all things client!
    SDL_Window *window;
    SDL_Renderer *renderer;
    Gamestate gamestate;
    int currentTicks;
    int prevTicks;
    int drawX;
    int drawY;
    DrawList_t *DLhead; // basically the scene?
    char stringBuffer[MAX_CHARS]; // for now?
} Client_t;

typedef struct Sprite_t { // add to it as you go...
    int x; // for now, change to vec2 later on?
    int y;
    int w;
    int h;
    int scale;
    int frame;
    int cols;
    int lastTick; // used only for cursor...so far...
    SDL_Texture *img;
} Sprite_t;

typedef struct String_t {
    char data[MAX_CHARS];
    int len;
    int y;
    int index;
    int lastTick;
} String_t;

#endif