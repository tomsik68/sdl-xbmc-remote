#include <iostream>
#include <stdio.h>
#include "xbmcremote.h"
#include <SDL.h>

#define MANUAL_ARROWS_WORKAROUND


const int screenWidth = 800;
const int screenHeight = 600;

using namespace std;

bool mapKey(XBMCRemote* remote, SDLKey keysym){
    bool result = false;
#ifdef MANUAL_ARROWS_WORKAROUND
    if(keysym == SDLK_RIGHT){
        cout << "test" << endl;
        remote->sendButton("right", "KB");
        result = true;
    } else if(keysym == SDLK_LEFT){
        remote->sendButton("left", "KB");
        result = true;
    } else if(keysym == SDLK_UP){
        remote->sendButton("up", "KB");
        result = true;
    } else if(keysym == SDLK_DOWN){
        remote->sendButton("down", "KB");
        result = true;
    } else
#endif // MANUAL_ARROWS_WORKAROUND
    return result;
}

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
    SDL_Surface* screen = SDL_SetVideoMode(screenWidth, screenHeight, 32, 0);
    bool exiting = false;
    while(!exiting){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                if(!mapKey(&remote, event.key.keysym.sym))
                    remote.sendButtonNumber(event.key.keysym.sym, true);
            } else if(event.type == SDL_KEYUP){
                remote.sendButtonNumber(event.key.keysym.sym, false);
                cout << "Released:" << event.key.keysym.sym << endl;
            }
            if(event.type == SDL_MOUSEMOTION){
                float relX = 1.f * event.motion.x / screenWidth;
                float relY = 1.f * event.motion.y / screenHeight;
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
