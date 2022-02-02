#include"common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"

ShipStruct player;

int main(int argc, char *args[])
{
    // SDL and window setup
    SDL_Window *window = initSDL();
    if(window == NULL)
    {
        printf("Window failed to be created: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
    
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    //SDL_RenderSetLogicalSize(renderer, 320, 240);
    
    // Load in images and tiles
    SDL_Texture *bg = loadImage("art/bg.png");
    if(bg == NULL)
        printf("BG image failed to load.\n");

    SDL_Texture *bust = loadImage("art/bust.png");
    if(bust == NULL)
        printf("Bust image failed to load.\n");

    font = loadImage("art/font-ascii.png");
    if(font == NULL)
        printf("Font image filed to load.\n");
    
    setupFontTiles(fontTiles, FONT_NUM);

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
        blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        blitImage(bust, 176, 110, 76, 117);
        drawString("Welcome...Otacon.", 0);
        drawString("We have been waiting.", 12 * 4);
        //SDL_Delay(100);
        
        SDL_RenderPresent(renderer);
    }

    cleanup(window);
    return 0;
}