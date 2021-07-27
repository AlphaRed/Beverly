#include"common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"

ShipStruct player;

SDL_Color textColour = {255, 255, 255}; // white

int main(int argc, char *args[])
{
    // SDL and window setup
    SDL_Window *window = initSDL();
    if(window == NULL)
    {
        printf("Window failed to be created: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        printf("Renderer failed to be created: %s\n", SDL_GetError());
        return 1;
    }
    if(initIMG())
    {
        printf("IMG library failed to initialize.\n");
        return 1;
    }
    if(initTTF())
    {
        printf("TTF library failed to initialize.\n");
        return 1;
    }
    
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    //SDL_RenderSetLogicalSize(renderer, 320, 240);
    
    // Load in tile map and setup individual tiles
    SDL_Texture *bg = loadImage("art/bg.png", renderer);
    if(bg == NULL)
        printf("Image failed to load.\n");

    TTF_Font *font = TTF_OpenFont("art/clacon.ttf", 12);
    if(font == NULL)
        printf("Font failed to load.\n");

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello World!", textColour);
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = 400;
    textRect.h = 100;

    int quit = 1;
    SDL_Event e;

    // Game loop
    while(quit)
    {   
        // Input
        SDL_PollEvent(&e);
        quit = checkEvents(e, &player);

        // Logic

        // Render
        blitImage(bg, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderCopy(renderer, t, NULL, &textRect);
        
        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer);
    return 0;
}