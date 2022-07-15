#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "map.h"

// some things were meant to be global
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *args[])
{    
    // SDL setup
    if(initSDL())
    {
        printf("initSDL failed.\n");
        return 1;
    }

    // Load in images and tiles
    // TO DO: Handle this better?
    SDL_Texture *bg = loadImage("art/bg.png");
    if(bg == NULL)
        printf("BG image failed to load.\n");

    SDL_Texture *bust = loadImage("art/bust.png");
    if(bust == NULL)
        printf("Bust image failed to load.\n");

    SDL_Texture *sheep = loadImage("art/sheepjeeps.png");
    if(sheep == NULL)
        printf("Sheep image failed to load.\n");

    SDL_Texture *tile = loadImage("art/tile.png");
    if(tile == NULL)
        printf("Tile image failed to load.\n");

    font = loadImage("art/font-ascii.png");
    if(font == NULL)
        printf("Font image filed to load.\n");
    
    setupFontTiles(fontTiles, FONT_NUM);

    SDL_Texture *map = loadImage("art/maptiles.png");
    if(map == NULL)
        printf("Map tiles image failed to load.\n");

    setupMapTiles(mapTiles, TILE_NUM);

    int quit = 1;
    SDL_Event e;
    int current_ticks;
    int fps_counter = 0;
    int renderTicks = 0;

    if(loadMap("data/map.txt") == 1)
        printf("Error loading map!\n");
    if(loadHeightMap("data/heightmap.txt") == 1)
        printf("Error loading height map!\n");
    
    // center it initially
    // Setup camera
    Camera_t cam;
    cam.offsetX = (SCREEN_WIDTH / 2) - (TILE_SIZE * 4);
    cam.offsetY = 0;

    // Map cursor
    MapCursor c;
    c.img = loadImage("art/map-cursor1.png");
    if(c.img == NULL)
        printf("Map cursor image failed to load.\n");
    c.x = 0; // start at the first tile
    c.y = 0; // start at the first tile

    // Game loop
    while(quit)
    {
        current_ticks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        quit = checkEvents(e, &c);

        // Logic
        checkFocus(c.x, c.y, &cam);

        // Render
        renderTicks = SDL_GetTicks();
        blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black      

        drawMap(map, cam.offsetX, cam.offsetY);
        drawMapCursor(c.x, c.y, cam.offsetX, cam.offsetY, c.img); // draw cursor after map
        //blitImage(bust, 176, 110, 76, 117, 1);

        drawFPS(fps_counter);
        
        SDL_RenderPresent(renderer);

        fps_counter = calculateFPS(current_ticks);
    }

    cleanup();
    return 0;
}