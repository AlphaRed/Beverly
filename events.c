#include"common.h"
#include "events.h"

int checkEvents(SDL_Event e, SpriteStruct *p)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            //case SDLK_a:;
                break;
            //case SDLK_d:;
                break;
            default:
                break;
        }
        return 1;    
    }
}