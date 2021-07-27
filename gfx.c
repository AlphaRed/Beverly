#include"common.h"
#include "gfx.h"

SDL_Texture *loadImage(char *filename, SDL_Renderer *r)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *img = IMG_Load(filename);
    if(!img)
    {
        printf("Image failed to load: %s\n", IMG_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(r, img);
    return texture;
}

void blitImage(SDL_Texture *image, SDL_Renderer *dest, int x, int y, int w, int h)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;

    SDL_RenderCopy(dest, image, NULL, &destRect);
}

void blitTile(SDL_Texture *image, SDL_Renderer *dest, SDL_Rect tile, int x, int y, int w, int h)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;

    SDL_RenderCopy(dest, image, &tile, &destRect);
}

void drawShip(SDL_Texture *t, SDL_Renderer *r, ShipStruct s)
{
    if(s.draw == 0)
        blitTile(t, r, s.sprite, s.x, s.y, TILE_SIZE *2, TILE_SIZE *2);
}