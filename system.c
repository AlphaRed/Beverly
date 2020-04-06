#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "system.h"

SDL_Window *initSDL()
{
    SDL_Window *w = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        w = NULL;
    }
    else
    {
        w = SDL_CreateWindow("Beverley", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }
    return w;
}

int initIMG()
{
    if(IMG_Init(IMG_INIT_PNG) < 0)
    {
        printf("SDL_Image library failed to initialize: %s", IMG_GetError());
        return 1;
    }
    return 0;
}

void cleanup(SDL_Window *w, SDL_Renderer *r)
{
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    IMG_Quit();
    SDL_Quit();
}

SDL_Rect initTile(int x, int y)
{
    SDL_Rect tileRect;
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = TILE_SIZE;
    tileRect.h = TILE_SIZE;

    return tileRect;
}