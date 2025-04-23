#include "common.h"
#include "gfx.h"

// FOR LOADING TEXTURE
SDL_Texture *loadTexture(char *filename) {
    SDL_Texture *retTex = IMG_LoadTexture(client.renderer, filename);
    if (!retTex) {
        printf("Texture file failed to load\n");
        return NULL;
    }
    return retTex;
}

// FOR BLITTING SINGLE TILES FROM A TILE SHEET
void blitTile(Sprite_t *spr, int tileNum, float x, float y, float w, float h) {
    SDL_FRect tile;
    tile.x = (tileNum % TILE_COLUMNS) * w;
    tile.y = (tileNum / TILE_COLUMNS) * h;
    tile.w = w;
    tile.h = h;
    
    SDL_FRect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderTexture(client.renderer, spr->img, &tile, &dest);
}

// FOR BLITTING FULL SPRITES/IMAGES
void blitSprite(Sprite_t* spr) {
    SDL_FRect dest;

    dest.x = spr->x;
    dest.y = spr->y;
    dest.w = spr->w;
    dest.h = spr->h;
    SDL_RenderTexture(client.renderer, spr->img, NULL, &dest);
}

// FOR DRAWING WINDOWS
void drawWindow(Sprite_t* spr) {
    int x = spr->x;
    int y = spr->y;

    // top bar
    for (int i = 0; i < spr->w; i++) {
        if (i == 0)
            blitTile(spr, 0, x, y, TILE_WIDTH, TILE_HEIGHT);
        else if(i == spr->w - 1)
            blitTile(spr, 2, x, y, TILE_WIDTH, TILE_HEIGHT);
        else
            blitTile(spr, 1, x, y, TILE_WIDTH, TILE_HEIGHT);
        x += TILE_WIDTH;
    }

    // side bars
    x = spr->x; // reset x and set x to next line
    y += TILE_HEIGHT;
    for (int i = 1; i < spr->h; i++) {
        blitTile(spr, 4, x, y, TILE_WIDTH, TILE_HEIGHT);
        blitTile(spr, 3, x + (spr->w - 1) * TILE_WIDTH, y, TILE_WIDTH, TILE_HEIGHT);
        y += TILE_HEIGHT;
    }

    // bottom bar
    x = spr->x; // reset x and move back up one
    y -= TILE_HEIGHT;
    for (int i = 0; i < spr->w; i++) {
        if(i == 0)
            blitTile(spr, 7, x, y, TILE_WIDTH, TILE_HEIGHT);
        else if(i == spr->w - 1)
            blitTile(spr, 6, x, y, TILE_WIDTH, TILE_HEIGHT);
        else
            blitTile(spr, 5, x, y, TILE_WIDTH, TILE_HEIGHT);
        x += TILE_WIDTH;
    }
}

// FOR DRAWING TEXT
void drawText(Sprite_t* spr) {
    int x = spr->x;
    int y = spr->y;

    for (int i = 0; i < spr->len; i++) {
        char c = spr->string[i];
        blitTile(spr, c - 32, x, y, FONT_WIDTH, FONT_HEIGHT);
        x += FONT_WIDTH;
    }
}

// ADD SPRITE TO DRAWLIST
DrawList_t* addSprite(DrawList_t* head, int data, Sprite_t *sprite) {
    DrawList_t* new = NULL;
    new = malloc(sizeof(DrawList_t));
    if (new == NULL)
        return NULL;
    new->id = data;
    new->spr = sprite;
    new->next = head;
    printf("Added a sprite-> %d\n", new->id);
    return new;
}

// RENDERS THE DRAWLIST
void renderDrawList() {
    DrawList_t* current = client.DLhead;
    while (current != NULL) {
        if (current->spr->type == WINDOW)
            drawWindow(current->spr);
        else if(current->spr->type == TEXT)
            drawText(current->spr);
        else
            blitSprite(current->spr);
        current = current->next;
    }
}

// EVERYTHING BELOW THIS COMMENT IS UNREVIEWED AND NEEDS TO BE REWRITTEN OR DELETED...FOR FUTURE ISAAC
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

// delete later?
void drawLetter(char c, int x, int y, int s)
{
    //int x = ((c - 32) % 8) * 8; // ASCII starts at char = 32, font width = 8px
    //int y = ((c - 32) / 16) * 12; // ASCII starts at char = 32, num of chars in width = 16, font height = 12px

    SDL_FRect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = 8 * s;
    destRect.h = 12 * s;
    
    int fontIndex = c - 32; // ASCII starts at character #32
    // to fix later as I changed blitTile function!
    //blitTile(font, fontTiles[fontIndex].x, fontTiles[fontIndex].y, fontTiles[fontIndex].w, fontTiles[fontIndex].h);
}

// delete later?
void setupFontTiles(SDL_FRect f[], int num)
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

void drawCursorNew(Sprite_t *s) {
    SDL_FRect destRect = {client.drawX, client.drawY, 8 * 2, 12 * 2};
    SDL_FRect srcRect;
    srcRect.x = (s->frame % s->cols) * s->w;
    srcRect.y = (s->frame / s->cols) * s->h;
    srcRect.w = s->w;
    srcRect.h = s->h;
    
    client.DLhead = addSprite(client.DLhead, 3, s);
    int deltaTicks = client.currentTicks - s->lastTick;
    if(deltaTicks > 400) { // delay is hardcoded...s/b slower than draw
        if(s->frame >= 1)
            s->frame = 0;
        else
            s->frame = 1;
        s->lastTick = client.currentTicks;
    }
}

int drawRow(String_t *str, Sprite_t spr) {
    char c = str->data[str->index];
    //printf("Char: %c\n", c);

    int frame = c - 32;
    SDL_FRect srcRect;
    srcRect.x = (frame % spr.cols) * spr.w;
    srcRect.y = (frame / spr.cols) * spr.h;
    srcRect.w = spr.w;
    srcRect.h = spr.h;

    SDL_FRect destRect;
    destRect.x = client.drawX;
    destRect.y = client.drawY;
    destRect.w = spr.w * spr.scale;
    destRect.h = spr.h * spr.scale;

    if(str->index <= str->len) {
        client.DLhead = addSprite(client.DLhead, 3, &spr);
        str->index++;
        client.drawX += 8 * 2;
    }
    else { // string/row is done
        // need to clear data
        return 1;
    }
}