#include"common.h"
#include "gfx.h"

SDL_Texture *loadImage(char *filename)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *img = IMG_Load(filename);
    if(!img)
    {
        printf("Image failed to load: %s\n", IMG_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, img);
    return texture;
}

void blitImage(SDL_Texture *image, int x, int y, int w, int h)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;

    SDL_RenderCopy(renderer, image, NULL, &destRect);
}

void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect)
{
    SDL_Rect srcRect;
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;

    SDL_RenderCopy(renderer, image, &srcRect, &destRect);
}

void drawLetter(char c, SDL_Rect destRect)
{
    //int x = ((c - 32) % 8) * 8; // ASCII starts at char = 32, font width = 8px
    //int y = ((c - 32) / 16) * 12; // ASCII starts at char = 32, num of chars in width = 16, font height = 12px
    
    int fontIndex = c - 32; // ASCII starts at character #32
    blitTile(font, fontTiles[fontIndex].x, fontTiles[fontIndex].y, fontTiles[fontIndex].w, fontTiles[fontIndex].h, destRect);
}

void setupFontTiles(SDL_Rect f[], int num)
{
    for(int i = 0; i < num; i++)
    {
        f[i].x = (i % 8) * 8;
        f[i].y = (i / 16) * 12;
        f[i].w = 8;
        f[i].h = 12;
    }
}