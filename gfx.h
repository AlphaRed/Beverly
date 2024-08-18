#ifndef GFX_H
#define GFX_H

#define FONT_WIDTH 8
#define MAX_LEN 40

extern Client_t client;
extern SDL_Texture *font;
extern SDL_Rect fontTiles[FONT_NUM];
extern SDL_Rect mapTiles[TILE_NUM];
extern int levelMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
extern int heightMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

SDL_Texture *loadImage(char *filename);
void blitSprite(Sprite_t *s);
void drawChar(Sprite_t *s, char c, int x, int y);
void drawLine(String_t *str, Sprite_t *s, int currentTicks);
// To review the below functions...may not need them all
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
void checkFocus(int cx, int cy, Camera_t *c);
void drawMenu();

#endif