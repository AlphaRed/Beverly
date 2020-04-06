#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "gfx.h"
#include "system.h"

typedef struct
{
    int x;
    int y;
} ShipStruct;

ShipStruct player;

int checkEvents(SDL_Event e)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_a: player.x -= 10;
                break;
            case SDLK_d: player.x += 10;
                break;
            default:
                break;
        }
        return 1;    
    }
}

void boundCheck(int *x, int *y)
{
    if(*x < 0)
        *x = 0;
    if(*x > SCREEN_WIDTH - (TILE_SIZE * 2))
        *x = SCREEN_WIDTH - (TILE_SIZE * 2);
}

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
    
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    //SDL_RenderSetLogicalSize(renderer, 320, 240);
    
    // Load in tile map and setup individual tiles
    SDL_Texture *tiles = loadImage("art/tiles.png", renderer);
    if(tiles == NULL)
        printf("Image failed to load.\n");

    SDL_Rect bgTile = initTile(0, 0);
    SDL_Rect shipTile = initTile(16, 0);
    SDL_Rect enemyTileA = initTile(32, 0);
    SDL_Rect enemyTileB = initTile(48, 0);
    SDL_Rect enemyTileC = initTile(64, 0);

    int quit = 1;
    SDL_Event e;

    // Setup inital player
    player.x = (SCREEN_WIDTH / 2) - TILE_SIZE;
    player.y = SCREEN_HEIGHT - (TILE_SIZE * 6);

    // Game loop
    while(quit)
    {   
        // Input
        SDL_PollEvent(&e);
        quit = checkEvents(e);

        // Logic
        boundCheck(&player.x, &player.y);

        // Render
        blitTile(tiles, renderer, bgTile, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        blitTile(tiles, renderer, shipTile, player.x, player.y, TILE_SIZE * 2, TILE_SIZE * 2);
        //blitTile(tiles, renderer, enemyTileA, 0, 0, TILE_SIZE * 2, TILE_SIZE * 2);
        //blitTile(tiles, renderer, enemyTileB, 32, 0, TILE_SIZE * 2, TILE_SIZE * 2);
        //blitTile(tiles, renderer, enemyTileC, 64, 0, TILE_SIZE * 2, TILE_SIZE * 2);

        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer);
    return 0;
}