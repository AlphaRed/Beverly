#ifndef GFX_H
#define GFX_H

#define FONT_WIDTH 8
#define MAX_LEN 40

SDL_Texture *loadImage(char *filename);
void blitImage(SDL_Texture *image, int x, int y, int w, int h);
void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect);
void drawLetter(char c, int x, int y, int s);
void setupFontTiles(SDL_Rect f[], int num);
void drawString(char *string, int y);
void drawFPS(int fps);

#endif