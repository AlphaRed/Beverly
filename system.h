#ifndef SYSTEM_H
#define SYSTEM_H

SDL_Window *initSDL();
int initIMG();
int initTTF();
void cleanup(SDL_Window *w);
SDL_Rect initTile(int x, int y, int w, int h);
int calculateFPS(int currentTicks);

// to be moved elsewhere
FILE *openTextFile(char *filename);
int loadTextFile(FILE *f, TextStruct *t); 
void closeTextFile(FILE *f);

#endif