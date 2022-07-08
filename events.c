#include"common.h"
#include "events.h"

int checkEvents(SDL_Event e, MapCursor *c)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_w:
                c->y -= 1;
                if(c->y < 0)
                    c->y = 0;
                break;
            case SDLK_s:
                c->y += 1;
                if(c->y > MAX_MAP_SIZE - 1)
                    c->y = MAX_MAP_SIZE - 1;
                break;
            case SDLK_a:
                c->x -= 1;
                if(c->x < 0)
                    c->x = 0;
                break;
            case SDLK_d:
                c->x += 1;
                if(c->x > MAX_MAP_SIZE - 1)
                    c->x = MAX_MAP_SIZE - 1;
                break;
            default:
                break;
        }
        return 1;    
    }
}