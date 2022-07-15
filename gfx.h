#ifndef GFX_H
#define GFX_H

#define FONT_WIDTH 8
#define MAX_LEN 40

extern SDL_Renderer *renderer;

SDL_Texture *loadImage(char *filename);
void blitImage(SDL_Texture *image, int x, int y, int w, int h, int s);
void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect);
void drawLetter(char c, int x, int y, int s);
void setupFontTiles(SDL_Rect f[], int num);
void drawString(char *string, int y);
void drawFPS(int fps);
void drawAnimatedLine(LineStruct *L, int currentTicks, CursorStruct *C);
void drawCursor(CursorStruct *C, int currentTicks);
void drawParagraph(TextStruct *T, int currentTicks, CursorStruct *C);
void drawTile(SDL_Texture *t, int index, int x, int y, int s);
void drawMap(SDL_Texture *map, int offsetX, int offsetY);
void drawMapCursor(int x, int y, int offsetX, int offsetY, SDL_Texture *img);
void checkFocus(int cx, int cy, Camera_t *c);

#endif