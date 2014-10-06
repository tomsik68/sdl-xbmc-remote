#ifndef INPUTWRAPPER_H
#define INPUTWRAPPER_H

#include <SDL.h>
#include "xbmcremote.h"

// I don't know which header this is in on OpenPandora, so I'll just add ugly tempfix thing here:
#ifndef UINT16_MAX
    #define UINT16_MAX 65535
#endif

class InputWrapper
{
public:
    InputWrapper(XBMCRemote* remote, int width,int height);
    void processEvent(SDL_Event* event);
private:
    void processKeyDownEvent(SDL_Event* event);
    void processKeyUpEvent(SDL_Event* event);
    void processMouseMoveEvent(SDL_Event* event);
    void processMouseDownEvent(SDL_Event* event);
    void processMouseUpEvent(SDL_Event* event);

    XBMCRemote* remote;
    int screenWidth, screenHeight;
};

#endif // INPUTWRAPPER_H
