#include"common.h"
#include "system.h"
#include "gfx.h"

int initWindow() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return 1;
    }
    else
        client.window = SDL_CreateWindow("Beverly", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    return 0;
}

int initRenderer() {
    client.renderer = SDL_CreateRenderer(client.window, NULL);
    if(client.renderer == NULL) {
        printf("Renderer failed to be created: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

int initSDL() {
    if(initWindow()) {
        printf("initWindow failed.\n");
        return 1;
    }
    if(initRenderer()) {
        printf("initRenderer failed.\n");
        return 1;
    }
    return 0;
}

void cleanup() {
    SDL_DestroyRenderer(client.renderer);
    SDL_DestroyWindow(client.window);
    SDL_Quit();
}

int calculateFPS() {
    int fps = 0;
    int deltaTicks = SDL_GetTicks() - client.currentTicks;
        
    if(deltaTicks > 0)
        fps = 1000 / deltaTicks;
        
    if(fps > MAX_FPS) {
        int delay_time = (1000 / MAX_FPS) - deltaTicks;
        SDL_Delay(delay_time);
        // check again to see that it is fixed
        deltaTicks = SDL_GetTicks() - client.currentTicks;
        fps = 1000 / deltaTicks;
    }
    return fps;
}

void loadResources() {
    font = loadImage("art/font-ascii.png");
    if(font == NULL)
        printf("Font image filed to load.\n");
}