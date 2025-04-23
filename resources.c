#include "common.h"
#include "gfx.h"
#include "text.h"

extern SDL_Texture *font;
extern Client_t client;
extern Sprite_t sceneResources[MAX_SCENES][MAX_SPRITES];

// FOR LOADING SPRITES
void loadResources() {
    font = loadTexture("art/font-ascii.png");
    if (font == NULL)
        printf("Font image filed to load.\n");

    sceneResources[0][0].x = 50;
    sceneResources[0][0].y = 100;
    sceneResources[0][0].w = 76;
    sceneResources[0][0].h = 117;
    sceneResources[0][0].scale = 1;
    sceneResources[0][0].frame = 0;
    sceneResources[0][0].cols = 1;
    sceneResources[0][0].type = SPRITE;
    sceneResources[0][0].img = loadTexture("art/bust.png");

    sceneResources[0][1].x = 150;
    sceneResources[0][1].y = 100;
    sceneResources[0][1].w = 76;
    sceneResources[0][1].h = 117;
    sceneResources[0][1].scale = 1;
    sceneResources[0][1].frame = 0;
    sceneResources[0][1].cols = 1;
    sceneResources[0][1].type = SPRITE;
    sceneResources[0][1].img = loadTexture("art/bust.png");

    sceneResources[0][2].x = 50;
    sceneResources[0][2].y = 200;
    sceneResources[0][2].w = 10;
    sceneResources[0][2].h = 20;
    sceneResources[0][2].scale = 1;
    sceneResources[0][2].frame = 0;
    sceneResources[0][2].cols = 1;
    sceneResources[0][2].type = WINDOW;
    sceneResources[0][2].img = loadTexture("art/window.png");

    sceneResources[0][3].x = 0;
    sceneResources[0][3].y = 0;
    sceneResources[0][3].w = 0;
    sceneResources[0][3].h = 0;
    sceneResources[0][3].scale = 1;
    sceneResources[0][3].frame = 0;
    sceneResources[0][3].cols = 1;
    sceneResources[0][3].type = TEXT;
    sceneResources[0][3].img = loadTexture("art/font-ascii.png");
    strcpy_s(sceneResources[0][3].string, sizeof(sceneResources[0][3].string), "Hello Otacon.");
    sceneResources[0][3].len = 14;

}

// FOR LOADING SCENES INTO DRAWLIST
void loadScene(int sceneNum) {
    for (int spriteNum = 0; spriteNum < MAX_SPRITES; spriteNum++) {
        client.DLhead = addSprite(client.DLhead, spriteNum, &sceneResources[sceneNum][spriteNum]);
    }
}