#include "common.h"
#include "events.h"
#include "gfx.h"
#include "system.h"
#include "text.h"

// resources
SDL_Texture *font;

SDL_FRect fontTiles[FONT_NUM];

Client_t client;
Sprite_t sceneResources[MAX_SCENES][MAX_SPRITES];
// prob delete below?
Sprite_t text;
Sprite_t cursor;
Sprite_t loadbar;

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

// to be reworked soon...when I get to animations again...
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

int main(int argc, char *args[]) {    
    if(initSDL()) {
        printf("initSDL failed.\n");
        return 1;
    }
    
    // will need to move these...eventually!
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

    int quit = 0;
    SDL_Event e;
    int fps_counter = 0;
    int renderTicks = 0;
    client.gamestate = MENU;
    client.prevTicks = 0;
    client.drawX = 0;
    client.drawY = 0;
    client.DLhead = NULL;

    // Load in images and tiles
    loadResources();
    loadScene(0);
    setupFontTiles(fontTiles, FONT_NUM); // move this?

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