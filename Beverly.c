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

    SDL_Texture *sheep = loadImage("art/sheepjeeps.png");
    if(sheep == NULL)
        printf("Sheep image failed to load.\n");

    font = loadImage("art/font-ascii.png");
    if(font == NULL)
        printf("Font image filed to load.\n");
    
    setupFontTiles(fontTiles, FONT_NUM);

    int quit = 1;
    SDL_Event e;
    int current_ticks, delta_ticks;
    int fps_counter = 0;

    // Game loop
    while(quit)
    {   
        current_ticks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        quit = checkEvents(e, &player);

        // Logic

        // Render
        blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        blitImage(bust, 176, 110, 76, 117);
        blitImage(sheep, 176, 210, 448, 105);
        drawString("Welcome...Otacon.", 0);
        drawString("We have sheep jeeps.", 12 * 4);
        drawFPS(fps_counter);
        
        SDL_RenderPresent(renderer);

        delta_ticks = SDL_GetTicks() - current_ticks;
        //printf("delta: %d\n", delta_ticks);
        if(delta_ticks > 0)
            fps_counter = 1000 / delta_ticks;
        
        if(fps_counter > MAX_FPS)
        {
            int delay_time = (1000 / MAX_FPS) - delta_ticks;
            SDL_Delay(delay_time);
            // check again to see that it is fixed
            delta_ticks = SDL_GetTicks() - current_ticks;
            fps_counter = 1000 / delta_ticks;
        }
            
    }

    cleanup(window);
    return 0;
}