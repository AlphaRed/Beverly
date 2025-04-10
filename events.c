#include"common.h"
#include "events.h"

int checkGameEvents(SDL_Event e)
{
    if(e.type == SDL_EVENT_QUIT)
        return 0;
    else if(e.type == SDL_EVENT_KEY_DOWN)
    {
        /*
        switch(e.key.key)
        {
            case SDLK_W:
                c->y -= 1;
                if(c->y < 0)
                    c->y = 0;
                break;
            case SDLK_S:
                c->y += 1;
                if(c->y > MAX_MAP_SIZE - 1)
                    c->y = MAX_MAP_SIZE - 1;
                break;
            case SDLK_A:
                c->x -= 1;
                if(c->x < 0)
                    c->x = 0;
                break;
            case SDLK_D:
                c->x += 1;
                if(c->x > MAX_MAP_SIZE - 1)
                    c->x = MAX_MAP_SIZE - 1;
                break;
            default:
                break;
        }
        */
        return 1;    
    }
}

int checkMenuEvents(SDL_Event e)
{
    if (e.type == SDL_EVENT_QUIT)
        return 0;
    else if (e.type == SDL_EVENT_KEY_DOWN)
    {
        switch (e.key.key)
        {
        case SDLK_RETURN:
            return 2;
            break;
        case SDLK_ESCAPE:
            return 1;
            break;
        default:
            break;
        }
        return 0;
    }
    else
        return 0;
}