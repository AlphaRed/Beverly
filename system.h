#ifndef SYSTEM_H
#define SYSTEM_H

extern SDL_Texture *font;

extern Client_t client;

int initSDL();
void cleanup();
SDL_Rect initTile(int x, int y, int w, int h);
int calculateFPS();
void loadResources();

#endif