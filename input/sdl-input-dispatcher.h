#ifndef _INPUT_DISPATCHER_H
#define _INPUT_DISPATCHER_H

#include "mouse-input-listener-if.h"
#include <vector>
#include "engine-api.h"

class SDLInputDispatcher : MouseInputListenerIF
{
public:
    static SDLInputDispatcher *Instance();
    virtual void RegisterMouseMoveCallback(mouse_move_callback callback);
    virtual void UnregisterMouseMoveCallback(mouse_move_callback callback);
    FrameCallbackResult FrameCallback();

private:
    SDLInputDispatcher();

    static SDLInputDispatcher *s_instance;

    std::vector<mouse_move_callback> m_mouseMoveCallbacks;
};

#endif