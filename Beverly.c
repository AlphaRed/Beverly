#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "text.h"

// resources
SDL_Texture *font;

SDL_Rect fontTiles[FONT_NUM];
SDL_Rect mapTiles[TILE_NUM];

Client_t client;
Sprite_t bg;
Sprite_t bust;
Sprite_t text;
Sprite_t cursor;

String_t stringy;

void checkDelay(FILE *f) {
    int deltaTicks = client.currentTicks - client.prevTicks;
    int endofRow = 0;
    if(deltaTicks > 400) { // hardcoded for now
        endofRow = drawRow(&stringy, text);
        client.prevTicks = client.currentTicks;
    }
    if(endofRow == 1) {
        loadText(f, &stringy);
        client.drawY += 12 * 2;
        client.drawX = 0;
    }
}

int main(int argc, char *args[]) {    
    // SDL setup
    if(initSDL()) {
        printf("initSDL failed.\n");
        return 1;
    }

    // Load in images and tiles
    loadResources();
    setupFontTiles(fontTiles, FONT_NUM); // move this?
    
    // will need to move these...eventually!
    bust.x = 50;
    bust.y = 100;
    bust.w = 76;
    bust.h = 117;
    bust.scale = 1;
    bust.frame = 0;
    bust.cols = 1;
    bust.img = loadImage("art/bust.png");

    bg.x = 0;
    bg.y = 0;
    bg.w = 32;
    bg.h = 32;
    bg.scale = 0;
    bg.frame = 0;
    bg.cols = 1;
    bg.img = loadImage("art/bg.png");

    text.x = 0;
    text.y = 0;
    text.w = 8;
    text.h = 12;
    text.scale = 2; // go with 2x for now...
    text.frame = 0;
    text.cols = 16;
    text.img = loadImage("art/font-ascii.png");

    cursor.x = 0;
    cursor.y = 0;
    cursor.w = 8;
    cursor.h = 12;
    cursor.scale = 2; // go with 2x for now...
    cursor.frame = 0;
    cursor.cols = 2;
    cursor.lastTick = 0;
    cursor.img = loadImage("art/cursor.png");

    String_t testStr;
    //testStr.data = "I'm back Otacon.";
    testStr.len = 16;
    testStr.y = 0;
    testStr.index = 0;
    testStr.lastTick = 0;

    int quit = 1;
    SDL_Event e;
    int fps_counter = 0;
    int renderTicks = 0;
    client.gamestate = MENU;
    client.prevTicks = 0;
    client.drawX = 0;
    client.drawY = 0;
    client.DLhead = NULL;

    // drawlist testing
    SDL_Rect sRect, dRect;
    sRect.x = 0;
    sRect.y = 0;
    sRect.w = 76;
    sRect.h = 117;
    dRect.x = 0;
    dRect.y = 0;
    dRect.w = 76;
    dRect.h = 117;
    SDL_Texture * testimg = loadImage("art/bust.png");
    //client.DLhead = addSprite(client.DLhead, 1, testimg, sRect, dRect);
    dRect.x = 50;
    dRect.y = 50;
    dRect.w = 76;
    dRect.h = 117;
    client.DLhead = addSprite(client.DLhead, 2, testimg, sRect, dRect);

    printSprites();

    //drawCursorNew(&cursor);
    FILE *t = openTextFile("string.txt");
    loadText(t, &stringy);

    // Game loop
    while(quit) {
        client.currentTicks = SDL_GetTicks();

        // Input
        SDL_PollEvent(&e);
        if(client.gamestate == GAME) {
            quit = checkGameEvents(e);
        }
        else if(client.gamestate == MENU) {
            quit = checkMenuEvents(e);
            if(quit == 2)
                client.gamestate = GAME;
        }

        // Logic
        if(client.gamestate == GAME) {
            checkDelay(t);
        }
        else if(client.gamestate == MENU) {
            checkDelay(t);
        }

        // Render
        renderTicks = SDL_GetTicks();

        if(client.gamestate == GAME) {  
            blitSprite(&bg);
            blitSprite(&bust); 
        }
        else if(client.gamestate == MENU) {
            blitSprite(&bg); // clearing colour
            //blitSprite(&bust);
            //blitSprite(&text);
            //drawChar(&text, 'H', 0, 0);
            //drawLine(&testStr, &text);
            //drawCursor(&cursor);
            renderDrawList();
        }
        
        drawFPS(fps_counter);
        SDL_RenderPresent(client.renderer);
        fps_counter = calculateFPS(client.currentTicks);
    }
    closeTextFile(t);
    cleanup();
    return 0;
}