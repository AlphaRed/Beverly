#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "map.h"
#include "mech.h"

// some things were meant to be global
SDL_Window *window;
SDL_Renderer *renderer;
Gamestate gs = MENU;
// resources
SDL_Texture *bg;
SDL_Texture *tiles;
SDL_Texture *font;

int main(int argc, char *args[])
{    
    // SDL setup
    if(initSDL())
    {
        printf("initSDL failed.\n");
        return 1;
    }

    // Load in images and tiles
    loadResources();
    setupFontTiles(fontTiles, FONT_NUM); // move this?
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

    // for mech test
    SDL_Texture *mechImg = loadImage("art/mech.png");
    Mech_t *mechHead = NULL;
    mechHead = addMech(mechHead, mechImg, 0, 0);
    mechHead = addMech(mechHead, mechImg, 2, 1);
    mechHead = addMech(mechHead, mechImg, 5, 4);

    // Game loop
    while(quit)
    {
        current_ticks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        if(gs == GAME)
        {
            quit = checkGameEvents(e, &c);
        }
        else if(gs == MENU)
        {
            quit = checkMenuEvents(e, &c);
            if(quit == 2)\
                gs = GAME;
        }

        // Logic
        if(gs == GAME)
            checkFocus(c.x, c.y, &cam);

        // Render
        renderTicks = SDL_GetTicks();

        if(gs == GAME)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black      
            drawMap(tiles, cam.offsetX, cam.offsetY);
            drawMapCursor(c.x, c.y, cam.offsetX, cam.offsetY, c.img); // draw cursor after map
            drawMech(mechHead, cam.offsetX, cam.offsetY);
        }
        else if(gs == MENU)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black
            drawMenu();
        }
        
        drawFPS(fps_counter);
        SDL_RenderPresent(renderer);
        fps_counter = calculateFPS(current_ticks);
    }

    cleanup();
    return 0;
}