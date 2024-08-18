#include "common.h"
#include "gfx.h"

SDL_Texture *loadImage(char *filename) {
    SDL_Texture *tex = NULL;
    SDL_Surface *img = IMG_Load(filename);
    if(!img) {
        printf("Image failed to load: %s\n", IMG_GetError());
        return NULL;
    }
    tex = SDL_CreateTextureFromSurface(client.renderer, img);
    return tex;
}

void blitSprite(Sprite_t *s) {
    SDL_Rect srcRect, destRect;
    srcRect.x = (s->frame % s->cols) * s->w;
    srcRect.y = (s->frame / s->cols) * s->h;
    srcRect.w = s->w;
    srcRect.h = s->h;

    /* in case of fire
    printf("x: %d\n", srcRect.x);
    printf("y: %d\n", srcRect.y);
    printf("w: %d\n", srcRect.w);
    printf("h: %d\n", srcRect.h);
    */

    if(s->scale == 0) // full screen blit
        SDL_RenderCopy(client.renderer, s->img, &srcRect, NULL);
    else {
        destRect.x = s->x;
        destRect.y = s->y;
        destRect.w = s->w * s->scale;
        destRect.h = s->h * s->scale;
        SDL_RenderCopy(client.renderer, s->img, &srcRect, &destRect);
    }
}

void drawChar(Sprite_t *s, char c, int x, int y) { // rename later? really small function
    s->frame = c - 32;
    s->x = x;
    s->y = y;
    blitSprite(s);
}

void drawLine(String_t *str, Sprite_t *s, int currentTicks) {
    int drawX = 5; // start in a little
    for(int i = 0; i < str->index; i++)
    {
        char c = str->data[i];
        drawChar(s, c, drawX, str->y); // not sure we need a separate function?
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * s->scale); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * s->scale); // Minus two for distancing...kerning(?)            
    }
    int deltaTicks = currentTicks - str->lastTick;
    if(deltaTicks > 200) // delay hardcoded for now
    {
        str->index++;
        if(str->index > str->len)
            str->index = str->len; // prevent out of bounds
        str->lastTick = currentTicks;
        /*
        C->x += ((FONT_WIDTH - 2) * L->s);
        if(C->x > drawX)
            C->x = drawX;
        */
    }
}

// might not be needed anymore...to remove from drawletter and drawmap(?)
void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect) {
    SDL_Rect srcRect;
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;

    SDL_RenderCopy(client.renderer, image, &srcRect, &destRect);
}

// delete later?
void drawLetter(char c, int x, int y, int s)
{
    //int x = ((c - 32) % 8) * 8; // ASCII starts at char = 32, font width = 8px
    //int y = ((c - 32) / 16) * 12; // ASCII starts at char = 32, num of chars in width = 16, font height = 12px

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 8 * s;
    destRect.h = 12 * s;
    
    int fontIndex = c - 32; // ASCII starts at character #32
    blitTile(font, fontTiles[fontIndex].x, fontTiles[fontIndex].y, fontTiles[fontIndex].w, fontTiles[fontIndex].h, destRect);
}

// delete later?
void setupFontTiles(SDL_Rect f[], int num)
{
    for(int i = 0; i < num; i++)
    {
        f[i].x = (i % 16) * 8;
        f[i].y = (i / 16) * 12;
        f[i].w = 8;
        f[i].h = 12;
    }
}

// delete later?
void drawString(char *string, int y)
{
    // only draw a string max length of 40 characters! (1,280 res width / (8 * 4) don't forget the upscale of 4x
    // technically can be drawn closer due to the way I've drawn the pixel art!
    int x = 0;
    int len = strlen(string);
    if(len > MAX_LEN)
        len = MAX_LEN; // max out at 40

    for(int i = 0; i < len; i++)
    {
        drawLetter(string[i], x, y, 4);
        if(string[i] == 'i')
            x += ((FONT_WIDTH - 4) * 4); // more for i...maybe l?
        else
            x += ((FONT_WIDTH - 2) * 4); // Minus two for distancing...kerning(?)
    }
}

// To review...
void drawFPS(int fps)
{
    char c;
    int x;

    drawLetter('F', 1000, 0, 1);
    drawLetter('P', 1008, 0, 1);
    drawLetter('S', 1016, 0, 1);
    drawLetter(':', 1024, 0, 1);
    drawLetter(' ', 1032, 0, 1);

    if(fps > 1000)
        fps = 1000;
    
    for(int i = 0; i < 4; i++)
    {
        c = (fps % 10) + 48; // need 48 to convert to ASCII numbers
        fps = fps / 10;
        x = 1064 - (i * 8);
        drawLetter(c, x, 0, 1);
    }   
}

// delete later?
void drawAnimatedLine(LineStruct *L, int currentTicks, CursorStruct *C) {
    int drawX = L->x;
    for(int i = 0; i < L->currentFrame; i++)
    {
        char c = L->string[i];
        drawLetter(c, drawX, L->y, L->s);
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * L->s); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * L->s); // Minus two for distancing...kerning(?)            
    }
    int deltaTicks = currentTicks - L->lastTick;
    if(deltaTicks > L->delay)
    {
        L->currentFrame++;
        if(L->currentFrame > L->length)
            L->currentFrame = L->length; // prevent out of bounds
        L->lastTick = currentTicks;
        C->x += ((FONT_WIDTH - 2) * L->s);
        if(C->x > drawX)
            C->x = drawX;
    }
}

// TO DO: move with other text related functions to new file
void drawCursor(CursorStruct *C, int currentTicks) // TO DO: add a function for changing location of cursor
{
    char c;
    if(C->currentFrame == 1)
        c = C->c2;
    else
        c = C->c1;
    drawLetter(c, C->x, C->y, C->s);
    int deltaTicks = currentTicks - C->lastTick;
    if(deltaTicks > C->delay)
    {
        C->currentFrame++;
        if(C->currentFrame > 1)
            C->currentFrame = 0; // I think there's a better way to do this but whatever
        C->lastTick = currentTicks;
    }
}

// delete later?
void drawParagraph(TextStruct *T, int currentTicks, CursorStruct *C)
{
    int drawX = 10;
    int drawY = 10;
    int scale = 4;
    int delay = 450;

    for(int i = 0; i <= T->currentLetter; i++)
    {
        char c = T->string1[i];
        drawLetter(c, drawX, drawY, scale);
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * scale); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * scale); // Minus two for distancing...kerning(?)
    }
                 
    int deltaTicks = currentTicks - T->lastTick;
    if(deltaTicks > delay)
    {
        T->currentLetter++;
        if(T->currentLetter > T->string1Len)
            T->currentLetter = T->string1Len;
        T->lastTick = currentTicks;
        C->x += ((FONT_WIDTH - 2) * scale);
        if(C->x > drawX)
            C->x = drawX;
    }
}

// delete later?
void drawTile(SDL_Texture *t, int index, int x, int y, int s)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = TILE_SIZE * s;
    destRect.h = TILE_SIZE * s;
    
    blitTile(t, mapTiles[index].x, mapTiles[index].y, mapTiles[index].w, mapTiles[index].h, destRect);
}

// delete later?
void drawMap(SDL_Texture *map, int offsetX, int offsetY)
{
    for(int h = 0; h < MAX_MAP_HEIGHT; h++)
    {
        for(int i = 0; i < MAX_MAP_SIZE; i++)
        {
            for(int j = 0; j < MAX_MAP_SIZE; j++)
            {   
                if(heightMap[j][i] == h)
                {
                    if(levelMap[j][i] == 1) // need to make this more robust, but it works for now
                    {
                        int x = (j - i) * 64 + offsetX;
                        int y = (j + i) * 32 + offsetY - (TILE_SIZE * 2 * h);
                        drawTile(map, 1, x, y, 4);
                    }
                    if(levelMap[j][i] == 0)
                    {
                        int x = (j - i) * 64 + offsetX;
                        int y = (j + i) * 32 + offsetY - (TILE_SIZE * 2 * h);
                        drawTile(map, 0, x, y, 4);
                    }
                }          
            }
        }
    }
}

// delete later?
void checkFocus(int cx, int cy, Camera_t *c)
{
    int h = 0;
    int x = (cx - cy) * 64 + c->offsetX;
    int y = (cx + cy) * 32 + c->offsetY - (TILE_SIZE * 2 * h);
    int focusLeft = 300;
    int focusRight = SCREEN_WIDTH - focusLeft;
    int focusUp = 100;
    int focusDown = SCREEN_HEIGHT - focusUp;

    if(x < focusLeft) // check left
    {
        c->offsetX -= (x - focusLeft);
    }    
    else if(x > focusRight) // check right
    {
        c->offsetX -= (x - focusRight);
    }
    else if(y < focusUp) // check up
    {
        c->offsetY -= (y - focusUp);
    }
    else if(y > focusDown)
    {
        c->offsetY -= (y - focusDown);
    }
    else
        return;        
}

// delete later?
void drawMenu() {
    drawString("Please enter your terminal number", 100);
}