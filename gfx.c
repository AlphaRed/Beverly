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

void drawLetter(char c, SDL_Rect destRect)
{
    switch (c)
    {
    // NUMBERS
    case '0':
        blitTile(font, 0, 0, 8, 12, destRect);
        break;
    case '1':
        blitTile(font, 8, 0, 8, 12, destRect);
        break;
    case '2':
        blitTile(font, 16, 0, 8, 12, destRect);
        break;
    case '3':
        blitTile(font, 24, 0, 8, 12, destRect);
        break;
    case '4':
        blitTile(font, 32, 0, 8, 12, destRect);
        break;
    case '5':
        blitTile(font, 40, 0, 8, 12, destRect);
        break;
    case '6':
        blitTile(font, 48, 0, 8, 12, destRect);
        break;
    case '7':
        blitTile(font, 56, 0, 8, 12, destRect);
        break;
    case '8':
        blitTile(font, 64, 0, 8, 12, destRect);
        break;
    case '9':
        blitTile(font, 72, 0, 8, 12, destRect);
        break;
    // UPPERCASE LETTERS
    case 'A':
        blitTile(font, 0, 12, 8, 12, destRect);
        break;
    case 'B':
        blitTile(font, 8, 12, 8, 12, destRect);
        break;
    case 'C':
        blitTile(font, 16, 12, 8, 12, destRect);
        break;
    case 'D':
        blitTile(font, 24, 12, 8, 12, destRect);
        break;
    case 'E':
        blitTile(font, 32, 12, 8, 12, destRect);
        break;
    case 'F':
        blitTile(font, 40, 12, 8, 12, destRect);
        break;
    case 'G':
        blitTile(font, 48, 12, 8, 12, destRect);
        break;
    case 'H':
        blitTile(font, 56, 12, 8, 12, destRect);
        break;
    case 'I':
        blitTile(font, 64, 12, 8, 12, destRect);
        break;
    case 'J':
        blitTile(font, 72, 12, 8, 12, destRect);
        break;
    case 'K':
        blitTile(font, 80, 12, 8, 12, destRect);
        break;
    case 'L':
        blitTile(font, 88, 12, 8, 12, destRect);
        break;
    case 'M':
        blitTile(font, 96, 12, 8, 12, destRect);
        break;
    case 'N':
        blitTile(font, 104, 12, 8, 12, destRect);
        break;
    case 'O':
        blitTile(font, 112, 12, 8, 12, destRect);
        break;
    case 'P':
        blitTile(font, 120, 12, 8, 12, destRect);
        break;
    case 'Q':
        blitTile(font, 0, 24, 8, 12, destRect);
        break;
    case 'R':
        blitTile(font, 8, 24, 8, 12, destRect);
        break;
    case 'S':
        blitTile(font, 16, 24, 8, 12, destRect);
        break;
    case 'T':
        blitTile(font, 24, 24, 8, 12, destRect);
        break;
    case 'U':
        blitTile(font, 32, 24, 8, 12, destRect);
        break;
    case 'V':
        blitTile(font, 40, 24, 8, 12, destRect);
        break;
    case 'W':
        blitTile(font, 48, 24, 8, 12, destRect);
        break;
    case 'X':
        blitTile(font, 56, 24, 8, 12, destRect);
        break;
    case 'Y':
        blitTile(font, 64, 24, 8, 12, destRect);
        break;
    case 'Z':
        blitTile(font, 72, 24, 8, 12, destRect);
        break;
    // LOWERCASE LETTERS
    case 'a':
        blitTile(font, 0, 36, 8, 12, destRect);
        break;
    case 'b':
        blitTile(font, 8, 36, 8, 12, destRect);
        break;
    case 'c':
        blitTile(font, 16, 36, 8, 12, destRect);
        break;
    case 'd':
        blitTile(font, 24, 36, 8, 12, destRect);
        break;
    case 'e':
        blitTile(font, 32, 36, 8, 12, destRect);
        break;
    case 'f':
        blitTile(font, 40, 36, 8, 12, destRect);
        break;
    case 'g':
        blitTile(font, 48, 36, 8, 12, destRect);
        break;
    case 'h':
        blitTile(font, 56, 36, 8, 12, destRect);
        break;
    case 'i':
        blitTile(font, 64, 36, 8, 12, destRect);
        break;
    case 'j':
        blitTile(font, 72, 36, 8, 12, destRect);
        break;
    case 'k':
        blitTile(font, 80, 36, 8, 12, destRect);
        break;
    case 'l':
        blitTile(font, 88, 36, 8, 12, destRect);
        break;
    case 'm':
        blitTile(font, 96, 36, 8, 12, destRect);
        break;
    case 'n':
        blitTile(font, 104, 36, 8, 12, destRect);
        break;
    case 'o':
        blitTile(font, 112, 36, 8, 12, destRect);
        break;
    case 'p':
        blitTile(font, 120, 36, 8, 12, destRect);
        break;
    case 'q':
        blitTile(font, 0, 48, 8, 12, destRect);
        break;
    case 'r':
        blitTile(font, 8, 48, 8, 12, destRect);
        break;
    case 's':
        blitTile(font, 16, 48, 8, 12, destRect);
        break;
    case 't':
        blitTile(font, 24, 48, 8, 12, destRect);
        break;
    case 'u':
        blitTile(font, 32, 48, 8, 12, destRect);
        break;
    case 'v':
        blitTile(font, 40, 48, 8, 12, destRect);
        break;
    case 'w':
        blitTile(font, 48, 48, 8, 12, destRect);
        break;
    case 'x':
        blitTile(font, 56, 48, 8, 12, destRect);
        break;
    case 'y':
        blitTile(font, 64, 48, 8, 12, destRect);
        break;
    case 'z':
        blitTile(font, 72, 48, 8, 12, destRect);
        break;
    // SYMBOLS & PUNCTUATION
    
    default:
        break;
    }
}