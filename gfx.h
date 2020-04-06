#ifndef GFX_H
#define GFX_H

SDL_Texture *loadImage(char *filename, SDL_Renderer *r);
void blitImage(SDL_Texture *image, SDL_Renderer *dest, int x, int y, int w, int h);
void blitTile(SDL_Texture *image, SDL_Renderer *dest, SDL_Rect tile, int x, int y, int w, int h);

#endif