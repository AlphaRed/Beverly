#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "map.h"

// resources
SDL_Texture *bg;
SDL_Texture *tiles;
SDL_Texture *font;

SDL_Rect fontTiles[FONT_NUM];
SDL_Rect mapTiles[TILE_NUM];

int levelMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
int heightMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

Client_t client;
Sprite_t background;
Sprite_t bust;

int main(int argc, char *args[]) {    
    // SDL setup
    if(initSDL()) {
        printf("initSDL failed.\n");
        return 1;
    }

    // Load in images and tiles
    loadResources();
    setupFontTiles(fontTiles, FONT_NUM); // move this?
    setupMapTiles(mapTiles, TILE_NUM);
    background.img = loadImage("art/bg.png");
    
    bust.img = loadImage("art/bust.png");
    bust.x = 50;
    bust.y = 100;
    bust.scale = 1;
    bust.w = 76;
    bust.h = 117;
    bust.frame = 0;
    bust.cols = 1;
    
    int quit = 1;
    SDL_Event e;
    int current_ticks;
    int fps_counter = 0;
    int renderTicks = 0;
    client.gamestate = MENU;

    if(loadMap("data/map.txt") == 1)
        printf("Error loading map!\n");
    if(loadHeightMap("data/heightmap.txt") == 1)
        printf("Error loading height map!\n");
    
    // center it initially
    // Setup camera
    Camera_t cam;
    cam.offsetX = (SCREEN_WIDTH / 2) - (TILE_SIZE * 4);
    cam.offsetY = 0;

    // Game loop
    while(quit)
    {
        current_ticks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        if(client.gamestate == GAME)
        {
            quit = checkGameEvents(e);
        }
        else if(client.gamestate == MENU)
        {
            quit = checkMenuEvents(e);
            if(quit == 2)
                client.gamestate = GAME;
        }

        // Logic
        if(client.gamestate == GAME)

        // Render
        renderTicks = SDL_GetTicks();

        if(client.gamestate == GAME)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black      
            drawMap(tiles, cam.offsetX, cam.offsetY);
        }
        else if(client.gamestate == MENU)
        {
            blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1); // clear bg to black
            blitSprite(bust);
            //drawMenu();
        }
        
        drawFPS(fps_counter);
        SDL_RenderPresent(client.renderer);
        fps_counter = calculateFPS(current_ticks);
    }

    cleanup();
    return 0;
}