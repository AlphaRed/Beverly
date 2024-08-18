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
void drawLine(String_t *str, Sprite_t *s);
void drawCursor(Sprite_t *s);
// To review the below functions...may not need them all
void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect);
void drawLetter(char c, int x, int y, int s);
void setupFontTiles(SDL_Rect f[], int num);
void drawFPS(int fps);
void drawTile(SDL_Texture *t, int index, int x, int y, int s);
void drawMap(SDL_Texture *map, int offsetX, int offsetY);
void checkFocus(int cx, int cy, Camera_t *c);

DrawList_t *addSprite(DrawList_t *head, int data, SDL_Texture *i, SDL_Rect sr, SDL_Rect dr);
int removeSprite(DrawList_t *head, int data);
void printSprites();
void renderDrawList();

#endif