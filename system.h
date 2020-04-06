#ifndef SYSTEM_H
#define SYSTEM_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 16

SDL_Window *initSDL();
int initIMG();
void cleanup(SDL_Window *w, SDL_Renderer *r);
SDL_Rect initTile(int x, int y);

#endif