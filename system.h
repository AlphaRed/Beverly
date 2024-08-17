#ifndef SYSTEM_H
#define SYSTEM_H

extern SDL_Texture *tiles;
extern SDL_Texture *font;

extern Client_t client;

int initSDL();
void cleanup();
SDL_Rect initTile(int x, int y, int w, int h);
int calculateFPS(int currentTicks);
void loadResources();

// to be moved elsewhere
FILE *openTextFile(char *filename);
int loadTextFile(FILE *f, TextStruct *t); 
void closeTextFile(FILE *f);

#endif