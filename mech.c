#include "common.h"
#include "mech.h"
#include "gfx.h"

Mech_t *addMech(Mech_t *m, SDL_Texture *t, int x, int y)
{
    Mech_t *newMech = malloc(sizeof(struct Mech_t));
    if(newMech == NULL)
    {
        printf("Error, malloc failed to create new mech!\n");
    }
    newMech->next = m;
    newMech->img = t;
    newMech->x = x;
    newMech->y = y;
    return newMech;
}

void drawMech(Mech_t *m, int offsetX, int offsetY)
{
    Mech_t *p;
    int x, y;
    for(p = m; p != NULL; p = p->next)
    {
        x = (p->x - p->y) * 64 + offsetX;
        y = (p->x + p->y) * 32 + offsetY - (TILE_SIZE * 2);
        blitImage(p->img, x, y, 32, 32, 4);
    }
}