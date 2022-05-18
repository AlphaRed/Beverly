#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "map.h"

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

    SDL_Texture *tile = loadImage("art/tile.png");
    if(tile == NULL)
        printf("Tile image failed to load.\n");

    font = loadImage("art/font-ascii.png");
    if(font == NULL)
        printf("Font image filed to load.\n");
    
    setupFontTiles(fontTiles, FONT_NUM);

    int quit = 1;
    SDL_Event e;
    int current_ticks;
    int fps_counter = 0;
    int renderTicks = 0;

    LineStruct LineOne;
    LineOne.x = 0;
    LineOne.y = 0;
    LineOne.s = 4;
    LineOne.string = "Please login.";
    LineOne.length = 14; // should do a function to calculate this automatically
    LineOne.currentFrame = -1;
    LineOne.delay = 450; // half a second or so
    LineOne.lastTick = 0;

    LineStruct LineTwo;
    LineTwo.x = 0;
    LineTwo.y = 12 * 4;
    LineTwo.s = 4;
    LineTwo.string = "Welcome...Otacon.";
    LineTwo.length = 18; // should do a function to calculate this automatically
    LineTwo.currentFrame = -1;
    LineTwo.delay = 450; // half a second or so
    LineTwo.lastTick = 0;
    
    CursorStruct cursor;
    cursor.x = 0;
    cursor.y = 0;
    cursor.s = 4;
    cursor.c1 = ' ';
    cursor.c2 = 127;
    cursor.currentFrame = 0;
    cursor.delay = 450;
    cursor.lastTick = 0;

    TextStruct textTest;
    textTest.currentLetter = 0;
    textTest.lastTick = 0;
    
    FILE *file = openTextFile("data/test.txt");
    if(file == NULL)
        printf("Error loading text file!!!\n");
    loadTextFile(file, &textTest);

    //int map[2][2] = {1,1,1,1};
    if(loadMap("data/map.txt") == 1)
        printf("Error loading map!\n");
    cameraOffsetX = 0;
    cameraOffsetY = 0;

    // Game loop
    while(quit)
    {
        current_ticks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        quit = checkEvents(e);

        // Logic

        // Render
        renderTicks = SDL_GetTicks();
        blitImage(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        blitImage(bust, 176, 110, 76, 117);

        for(int i = 0; i < MAX_MAP_SIZE; i++)
        {
            for(int j = 0; j < MAX_MAP_SIZE; j++)
            {
                if(levelMap[j][i] == 1)
                {
                    int x = (j - i) * 16 + cameraOffsetX;
                    int y = (j + i) * 8 + cameraOffsetY;
                    blitImage(tile, x, y, 32, 32);
                }
                    
            }
        }
        //blitImage(sheep, 176, 210, 448, 105);
        //drawAnimatedLine(&LineOne, renderTicks, &cursor);
        //drawAnimatedLine(&LineTwo, renderTicks, &cursor);
        //drawParagraph(&LineOne, renderTicks, &cursor);
        //drawCursor(&cursor, renderTicks);
        //drawString("Welcome...Otacon.", 0);

        // Do the cursor after
        //drawParagraph(&textTest, renderTicks, &cursor); // still work in progress

        drawFPS(fps_counter);
        
        SDL_RenderPresent(renderer);

        fps_counter = calculateFPS(current_ticks);
    }

    closeTextFile(file);
    cleanup(window);
    return 0;
}