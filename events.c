#include"common.h"
#include "events.h"

int checkEvents(SDL_Event e)
{
    if(e.type == SDL_QUIT)
        return 0;
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_w:
                cameraOffsetY -= 20;
                break;
            case SDLK_s:
                cameraOffsetY += 20;
                break;
            case SDLK_a:
                cameraOffsetX -= 20;
                break;
            case SDLK_d:
                cameraOffsetX += 20;
                break;
            default:
                break;
        }
        return 1;    
    }
}