#include"common.h"
#include "gfx.h"

SDL_Texture *loadImage(char *filename)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *img = IMG_Load(filename);
    if(!img)
    {
        printf("Image failed to load: %s\n", IMG_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, img);
    return texture;
}

void blitImage(SDL_Texture *image, int x, int y, int w, int h)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;

    SDL_RenderCopy(renderer, image, NULL, &destRect);
}

void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect)
{
    SDL_Rect srcRect;
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;

    SDL_RenderCopy(renderer, image, &srcRect, &destRect);
}

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

void drawAnimatedLine(LineStruct *L, int currentTicks)
{
    int drawX = L->x;
    for(int i = 0; i < L->currentFrame; i++)
    {
        char c = L->string[i];
        drawLetter(c, drawX, L->y, L->s);
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * 4); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * 4); // Minus two for distancing...kerning(?)
    }
    int deltaTicks = currentTicks - L->lastTick;
    if(deltaTicks > L->delay)
    {
        L->currentFrame++;
        if(L->currentFrame > L->length)
            L->currentFrame = L->length; // prevent out of bounds
        L->lastTick = currentTicks;
    }
}