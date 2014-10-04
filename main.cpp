#include <iostream>
#include "xbmcremote.h"
#include <SDL.h>

using namespace std;

int main()
{
    XBMCRemote remote("jasku-PC","jasku-eee",9777);

    if(remote.sayHello() == CONNECT_FAILED){
        printf("Couldn't connect to XBMC!");
        return 1;
    }
    if(!SDL_Init(SDL_INIT_EVERYTHING)){
        printf("Couldn't initialize SDL");
        return 1;
    }
    SDL_Surface* screen = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
    bool exiting = false;
    while(!exiting){
        SDL_Event* event;
        if(SDL_PollEvent(event)){
            if(event->type == SDL_KEYDOWN){
            }
            if(event->type == SDL_MOUSEMOTION){
                remote.sendMouse(event->motion.x, event->motion.y);
            }
            if(event->type == SDL_QUIT)
                exiting = true;
        }
        SDL_Flip(screen);
        SDL_Delay(100);
    }
    SDL_Quit();
    remote.sayBye();
    return 0;
}

