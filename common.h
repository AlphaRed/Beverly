#ifndef COMMON_H
#define COMMON_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH    1280 // keep it 16:9
#define SCREEN_HEIGHT   720
#define FONT_NUM 200
#define MAX_FPS 60
#define MAX_CHARS 80 // equals 1280 / 8px / 2 scale

typedef enum {MENU, GAME} Gamestate;

typedef struct DrawList_t {
    int id; // might use as an identifier!
    SDL_Texture *img;
    SDL_Rect srcRect;
    SDL_Rect destRect;
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
    DrawList_t *DLhead;
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