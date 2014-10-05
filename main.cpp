#include <stdio.h>
#include "xbmcremote.h"
#include <SDL.h>

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Couldn't initialize SDL :( \n");
        return 1;
    }
    XBMCRemote remote("jasku-PC","jasku-eee",9777);

    if(remote.sayHello() == CONNECT_FAILED){
        printf("Couldn't connect to XBMC!\n");
        return 1;
    }

    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, 0);
    bool exiting = false;
    while(!exiting){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            printf("Polujem >:| \n");
            if(event.type == SDL_KEYDOWN){
                remote.sendButtonNumber(event.key.keysym.sym, true);
            } else if(event.type == SDL_KEYUP){
                remote.sendButtonNumber(event.key.keysym.sym, false);
            }
            if(event.type == SDL_MOUSEMOTION){
                remote.sendMouse(event.motion.x, event.motion.y);
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
