#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "text.h"

// resources
SDL_Texture *font;

SDL_FRect fontTiles[FONT_NUM];

Client_t client;
Sprite_t bg;
Sprite_t bust;
Sprite_t text;
Sprite_t cursor;
Sprite_t loadbar;
Sprite_t windowTest;

String_t stringFile;

void checkDelay(FILE *f) {
    int deltaTicks = client.currentTicks - client.prevTicks;
    int endofRow = 0;
    if(deltaTicks > 400) { // hardcoded for now
        endofRow = drawRow(&stringFile, text);
        client.prevTicks = client.currentTicks;
    }
    if(endofRow == 1) {
        loadText(f, &stringFile);
        client.drawY += 12 * 2;
        client.drawX = 0;
    }
}

void drawLoadbar(Sprite_t *sprite, int maxLen) {
    float x = (float) sprite->x;
    float y = (float) sprite->y;
    //sprite->lastTick = client.currentTicks;

    if (client.currentTicks - sprite->lastTick > 300) {
        for (int i = 0; i <= sprite->frame; i++) {
            blitTile(sprite, 0, x + (i * sprite->w), y, 16.0, 16.0);
        }
        sprite->frame = sprite->frame + 1;
        if (sprite->frame > maxLen)
            sprite->frame = maxLen;
        sprite->lastTick = client.currentTicks;
    }
}

void drawWindow(int winW, int winH, Sprite_t *spr) {

}

int main(int argc, char *args[]) {    
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
    bust.img = loadTexture("art/bust.png");

    text.x = 0;
    text.y = 0;
    text.w = 8;
    text.h = 12;
    text.scale = 2; // go with 2x for now...
    text.frame = 0;
    text.cols = 16;
    text.img = loadTexture("art/font-ascii.png");

    cursor.x = 0;
    cursor.y = 0;
    cursor.w = 8;
    cursor.h = 12;
    cursor.scale = 2; // go with 2x for now...
    cursor.frame = 0;
    cursor.cols = 2;
    cursor.lastTick = 0;
    cursor.img = loadTexture("art/cursor.png");

    loadbar.x = 50;
    loadbar.y = 50;
    loadbar.w = 16;
    loadbar.h = 16;
    loadbar.scale = 1;
    loadbar.frame = 0;
    loadbar.cols = 4;
    loadbar.lastTick = 0;
    loadbar.img = loadTexture("art/loadbar.png");

    windowTest.x = 50;
    windowTest.y = 50;
    windowTest.w = 16;
    windowTest.h = 16;
    windowTest.scale = 1;
    windowTest.frame = 0;
    windowTest.cols = 4;
    windowTest.lastTick = 0;
    windowTest.img = loadTexture("art/window.png");

    int quit = 0;
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
    SDL_Texture * testimg = loadTexture("art/bust.png");
    dRect.x = 50;
    dRect.y = 50;
    dRect.w = 76;
    dRect.h = 117;
    client.DLhead = addSprite(client.DLhead, 2, testimg, sRect, dRect);

    printSprites();

    //drawCursorNew(&cursor);
    FILE *t = openTextFile("data/string.txt");
    loadText(t, &stringFile);

    // Game loop
    while(!quit) {
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
        SDL_RenderClear(client.renderer);

        if(client.gamestate == GAME) {  
            //blitSprite(&bust);
        }
        else if(client.gamestate == MENU) {
            blitSprite(&bust);
            blitTile(&windowTest, 0, 50, 50, TILE_WIDTH, TILE_HEIGHT);
            //drawLoadbar(&loadbar, 20);
            //blitSprite(&loadbar);
            //drawCursor(&cursor);
            //renderDrawList();
        }
        
        drawFPS(fps_counter);
        SDL_RenderPresent(client.renderer);
        fps_counter = calculateFPS(client.currentTicks);
    }
    closeTextFile(t);
    cleanup();
    return 0;
}