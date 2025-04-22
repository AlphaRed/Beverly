#ifndef GFX_H
#define GFX_H

#define FONT_WIDTH 8
#define MAX_LEN 40

extern Client_t client;
extern SDL_Texture *font;
extern SDL_FRect fontTiles[FONT_NUM];
extern Sprite_t sceneResources[MAX_SCENES][MAX_SPRITES];

SDL_Texture *loadTexture(char* filename);
void blitTile(Sprite_t *spr, int tileNum, float x, float y, float w, float h);
void blitSprite(Sprite_t *spr);
void drawWindow(Sprite_t* spr);
DrawList_t* addSprite(DrawList_t* head, int data, Sprite_t* sprite);
void renderDrawList();
// To review the below functions...may not need them all
void drawChar(Sprite_t *s, char c, int x, int y);
void drawLine(String_t *str, Sprite_t *s);
void drawCursor(Sprite_t* s);
void drawLetter(char c, int x, int y, int s);
void setupFontTiles(SDL_FRect f[], int num);
void drawFPS(int fps);
// these are probably fine but will review regardless
int removeSprite(DrawList_t *head, int data);
void printSprites();
void drawCursorNew(Sprite_t *s);
int drawRow(String_t *str, Sprite_t spr);

#endif