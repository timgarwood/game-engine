#ifndef _SDL_EVENT_DISPATCHER_H
#define _SDL_EVENT_DISPATCHER_H

#include "keyboard-input-listener-if.h"
#include "mouse-input-listener-if.h"
#include "window-listener-if.h"
#include <vector>
#include "engine-api.h"

class SDLEventDispatcher : MouseInputListenerIF, WindowListenerIF, KeyboardInputListenerIF
{
public:
    static SDLEventDispatcher *Instance();
    virtual void RegisterMouseMoveCallback(mouse_move_callback callback);
    virtual void UnregisterMouseMoveCallback(mouse_move_callback callback);
    virtual void RegisterForWindowResized(window_resized_callback callback);
    virtual void UnregisterForWindowResized(window_resized_callback callback);

    virtual void RegisterForKeyDown(key_down_callback callback);
    virtual void UnregisterForKeyDown(key_down_callback callback);
    virtual void RegisterForKeyUp(key_up_callback callback);
    virtual void UnregisterForKeyUp(key_up_callback callback);

    FrameCallbackResult FrameCallback();

private:
    SDLEventDispatcher();

    void SendKeyDown(char key);
    void SendKeyUp(char key);

    static SDLEventDispatcher *s_instance;

    std::vector<mouse_move_callback> m_mouseMoveCallbacks;
    std::vector<window_resized_callback> m_windowResizedCallbacks;
    std::vector<key_down_callback> m_keyDownCallbacks;
    std::vector<key_up_callback> m_keyUpCallbacks;
};

#endif