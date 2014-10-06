#include <SDL.h>
#include "inputwrapper.h"

InputWrapper::InputWrapper(XBMCRemote *remote, int width, int height)
{
    this->remote = remote;
    this->screenWidth = width;
    this->screenHeight = height;
}

void InputWrapper::processEvent(SDL_Event *event){
    switch(event->type){
    case SDL_KEYDOWN:
        processKeyDownEvent(event);
        break;

    case SDL_KEYUP:
        processKeyUpEvent(event);
        break;

    case SDL_MOUSEMOTION:
        processMouseMoveEvent(event);
        break;

    case SDL_MOUSEBUTTONDOWN:
        processMouseDownEvent(event);
        break;

    case SDL_MOUSEBUTTONUP:
        processMouseUpEvent(event);
        break;
    }
}

void InputWrapper::processKeyDownEvent(SDL_Event *event){
    switch( event->key.keysym.sym){
    case SDLK_DOWN:
        remote->sendButton("down", "KB");
        break;

    case SDLK_UP:
        remote->sendButton("up", "KB");
        break;

    case SDLK_LEFT:
        remote->sendButton("left", "KB");
        break;

    case SDLK_RIGHT:
        remote->sendButton("right", "KB");
        break;

    default:
        remote->sendButtonNumber(event->key.keysym.sym, true);
        break;
    }
}

void InputWrapper::processKeyUpEvent(SDL_Event *event){
    switch(event->key.keysym.sym){
    default:
        remote->sendButtonNumber(event->key.keysym.sym, false);
        break;
    }
}

void InputWrapper::processMouseMoveEvent(SDL_Event *event){
    float relX = 1.f * event->motion.x / screenWidth;
    float relY = 1.f * event->motion.y / screenHeight;
    uint16_t absX = (uint16_t)(relX * UINT16_MAX);
    uint16_t absY = (uint16_t)(relY * UINT16_MAX);
    remote->sendMouseMove(absX, absY);
}

void InputWrapper::processMouseDownEvent(SDL_Event *event){
    remote->sendMouseDown(event->button.button);
}

void InputWrapper::processMouseUpEvent(SDL_Event *event){
    remote->sendMouseDown(event->button.button);
}
