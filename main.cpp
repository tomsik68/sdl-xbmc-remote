#include <iostream>
#include <stdio.h>
#include "xbmcremote.h"
#include "inputwrapper.h"
#include <SDL.h>

#define MANUAL_ARROWS_WORKAROUND

const int screenWidth = 800;
const int screenHeight = 600;

using namespace std;

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "Couldn't initialize SDL :(" << endl;
        return 1;
    }
    XBMCRemote remote("jasku-PC", "jasku-eee",9777);
    cout << "Connecting to XBMC..." << endl;
    if(remote.sayHello() == CONNECT_FAILED){
        cout << "Couldn't connect to XBMC!" << endl;
        return 1;
    }
    cout << "Connected to XBMC" << endl;
    InputWrapper inputWrapper(&remote, screenWidth, screenHeight);
    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, 0);
    bool exiting = false;
    while(!exiting){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            inputWrapper.processEvent(&event);
            if(event.type == SDL_QUIT)
                exiting = true;
        }
        SDL_Flip(screen);
    }
    remote.sayBye();
    SDL_Quit();
    return 0;

}
