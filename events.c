#include"common.h"
#include "events.h"

int checkEvents(SDL_Event e, ShipStruct *p)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_a: p->x -= 10;
                break;
            case SDLK_d: p->x += 10;
                break;
            default:
                break;
        }
        return 1;    
    }
}