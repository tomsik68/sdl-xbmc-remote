#include <stdio.h>
#include "xbmcremote.h"
#include <SDL.h>

const int screenWidth = 800;
const int screenHeight = 600;

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Couldn't initialize SDL :( \n");
        return 1;
    }
    XBMCRemote remote("jasku-PC", "jasku-eee",9777);
    printf("Connecting to XBMC... \n");
    if(remote.sayHello() == CONNECT_FAILED){
        printf("Couldn't connect to XBMC!\n");
        return 1;
    }
    printf("Connected to XBMC \n");
    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, 0);
    bool exiting = false;
    while(!exiting){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                remote.sendButtonNumber(event.key.keysym.sym, true);
            } else if(event.type == SDL_KEYUP){
                remote.sendButtonNumber(event.key.keysym.scancode, false);
            }
            if(event.type == SDL_MOUSEMOTION){
                float relX = 1.f*event.motion.x / screenWidth;
                float relY = 1.f*event.motion.y / screenHeight;
                uint16_t absX = (uint16_t)(relX*65535);
                uint16_t absY = (uint16_t)(relY*65535);
                remote.sendMouse(absX, absY);
            }
            if(event.type == SDL_QUIT)
                exiting = true;
        }
        SDL_Flip(screen);
    }
    remote.sayBye();
    SDL_Quit();
    return 0;

}
