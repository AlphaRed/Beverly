#include "common.h"
#include "gfx.h"

SDL_Texture *loadImage(char *filename) {
    SDL_Texture *tex = NULL;
    SDL_Surface *img = IMG_Load(filename);
    if(!img) {
        printf("Image failed to load: %s\n", IMG_GetError());
        return NULL;
    }
    tex = SDL_CreateTextureFromSurface(client.renderer, img);
    return tex;
}

void blitSprite(Sprite_t *s) {
    SDL_Rect srcRect, destRect;
    srcRect.x = (s->frame % s->cols) * s->w;
    srcRect.y = (s->frame / s->cols) * s->h;
    srcRect.w = s->w;
    srcRect.h = s->h;

    /* in case of fire
    printf("x: %d\n", srcRect.x);
    printf("y: %d\n", srcRect.y);
    printf("w: %d\n", srcRect.w);
    printf("h: %d\n", srcRect.h);
    */

    if(s->scale == 0) // full screen blit
        SDL_RenderCopy(client.renderer, s->img, &srcRect, NULL);
    else {
        destRect.x = s->x;
        destRect.y = s->y;
        destRect.w = s->w * s->scale;
        destRect.h = s->h * s->scale;
        SDL_RenderCopy(client.renderer, s->img, &srcRect, &destRect);
    }
}

void drawChar(Sprite_t *s, char c, int x, int y) { // rename later? really small function
    s->frame = c - 32;
    s->x = x;
    s->y = y;
    blitSprite(s);
}

void drawLine(String_t *str, Sprite_t *s) {
    int drawX = 0; // start in a little
    for(int i = 0; i < str->index; i++) {
        char c = str->data[i];
        drawChar(s, c, client.drawX, client.drawY); // not sure we need a separate function?
        if(c == 'i')
            drawX += ((FONT_WIDTH - 4) * s->scale); // more for i...maybe l?
        else
            drawX += ((FONT_WIDTH - 2) * s->scale); // Minus two for distancing...kerning(?)            
    }
    int deltaTicks = client.currentTicks - str->lastTick;
    if(deltaTicks > 300) { // delay hardcoded for now
        str->index++;
        if(str->index > str->len)
            str->index = str->len; // prevent out of bounds
        str->lastTick = client.currentTicks;
        
        client.drawX += ((FONT_WIDTH - 2) * s->scale);
        if(client.drawX > drawX) // else it keeps drawing the last element along the window
            client.drawX = drawX;
    }
}

void drawCursor(Sprite_t *s) {
    s->x = client.drawX;
    s->y = client.drawY;
    blitSprite(s);
    int deltaTicks = client.currentTicks - s->lastTick;
    if(deltaTicks > 400) { // delay is hardcoded...s/b slower than draw
        if(s->frame >= 1)
            s->frame = 0;
        else
            s->frame = 1;
        s->lastTick = client.currentTicks;
    }
}

// might not be needed anymore...to remove from drawletter and drawmap(?)
void blitTile(SDL_Texture *image, int x, int y, int w, int h, SDL_Rect destRect) {
    SDL_Rect srcRect;
    srcRect.x = x;
    srcRect.y = y;
    srcRect.w = w;
    srcRect.h = h;

    SDL_RenderCopy(client.renderer, image, &srcRect, &destRect);
}

// delete later?
void drawLetter(char c, int x, int y, int s)
{
    //int x = ((c - 32) % 8) * 8; // ASCII starts at char = 32, font width = 8px
    //int y = ((c - 32) / 16) * 12; // ASCII starts at char = 32, num of chars in width = 16, font height = 12px

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 8 * s;
    destRect.h = 12 * s;
    
    int fontIndex = c - 32; // ASCII starts at character #32
    blitTile(font, fontTiles[fontIndex].x, fontTiles[fontIndex].y, fontTiles[fontIndex].w, fontTiles[fontIndex].h, destRect);
}

// delete later?
void setupFontTiles(SDL_Rect f[], int num)
{
    for(int i = 0; i < num; i++)
    {
        f[i].x = (i % 16) * 8;
        f[i].y = (i / 16) * 12;
        f[i].w = 8;
        f[i].h = 12;
    }
}

// To review...
void drawFPS(int fps)
{
    char c;
    int x;

    drawLetter('F', 1000, 0, 1);
    drawLetter('P', 1008, 0, 1);
    drawLetter('S', 1016, 0, 1);
    drawLetter(':', 1024, 0, 1);
    drawLetter(' ', 1032, 0, 1);

    if(fps > 1000)
        fps = 1000;
    
    for(int i = 0; i < 4; i++)
    {
        c = (fps % 10) + 48; // need 48 to convert to ASCII numbers
        fps = fps / 10;
        x = 1064 - (i * 8);
        drawLetter(c, x, 0, 1);
    }   
}

// delete later?
void drawTile(SDL_Texture *t, int index, int x, int y, int s)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = TILE_SIZE * s;
    destRect.h = TILE_SIZE * s;
    
    blitTile(t, mapTiles[index].x, mapTiles[index].y, mapTiles[index].w, mapTiles[index].h, destRect);
}

// delete later?
void drawMap(SDL_Texture *map, int offsetX, int offsetY)
{
    for(int h = 0; h < MAX_MAP_HEIGHT; h++)
    {
        for(int i = 0; i < MAX_MAP_SIZE; i++)
        {
            for(int j = 0; j < MAX_MAP_SIZE; j++)
            {   
                if(heightMap[j][i] == h)
                {
                    if(levelMap[j][i] == 1) // need to make this more robust, but it works for now
                    {
                        int x = (j - i) * 64 + offsetX;
                        int y = (j + i) * 32 + offsetY - (TILE_SIZE * 2 * h);
                        drawTile(map, 1, x, y, 4);
                    }
                    if(levelMap[j][i] == 0)
                    {
                        int x = (j - i) * 64 + offsetX;
                        int y = (j + i) * 32 + offsetY - (TILE_SIZE * 2 * h);
                        drawTile(map, 0, x, y, 4);
                    }
                }          
            }
        }
    }
}

// add a sprite
DrawList_t *addSprite(DrawList_t *head, int data, SDL_Texture *i, SDL_Rect sr, SDL_Rect dr) {
    DrawList_t *new = NULL;
    new = malloc(sizeof(DrawList_t));
    if(new == NULL)
        return NULL;
    new->id = data;
    new->img = i;
    new->srcRect = sr;
    new->destRect = dr;
    new->next = head;
    printf("Added a sprite-> %d\n", new->id);
    return new;
}

// remove a sprite...untested but should work!
int removeSprite(DrawList_t *head, int data) {
    DrawList_t *current = head;
    DrawList_t *prev = head;
    while(current != NULL) {
        if(current->id == data) {
            if(current == head){
                head = current->next;
            }
            else {
                prev->next = current->next;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

// print the sprites
void printSprites() {
    DrawList_t *current = client.DLhead;
    while(current != NULL) {
        printf("%d->", current->id);
        current = current->next;
    }
    printf("\n");
}

void renderDrawList() {
    DrawList_t *current = client.DLhead;
    while(current != NULL) {
        SDL_RenderCopy(client.renderer, current->img, &current->srcRect, &current->destRect);
        current = current->next;
    }
}