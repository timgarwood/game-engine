#ifndef _SDL_EVENT_DISPATCHER_H
#define _SDL_EVENT_DISPATCHER_H

#include "mouse-input-listener-if.h"
#include "window-listener-if.h"
#include <vector>
#include "engine-api.h"

class SDLEventDispatcher : MouseInputListenerIF, WindowListenerIF
{
public:
    static SDLEventDispatcher *Instance();
    virtual void RegisterMouseMoveCallback(mouse_move_callback callback);
    virtual void UnregisterMouseMoveCallback(mouse_move_callback callback);
    virtual void RegisterForWindowResized(window_resized_callback callback);
    virtual void UnregisterForWindowResized(window_resized_callback callback);
    FrameCallbackResult FrameCallback();

private:
    SDLEventDispatcher();

    static SDLEventDispatcher *s_instance;

    std::vector<mouse_move_callback> m_mouseMoveCallbacks;
    std::vector<window_resized_callback> m_windowResizedCallbacks;
};

#endif