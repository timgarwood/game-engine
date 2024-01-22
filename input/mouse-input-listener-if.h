#ifndef _MOUSE_INPUT_LISTENER_IF_H
#define _MOUSE_INPUT_LISTENER_IF_H

typedef void (*mouse_move_callback)(int x, int y);

class MouseInputListenerIF
{
public:
    virtual void RegisterMouseMoveCallback(mouse_move_callback callback) = 0;
    virtual void UnregisterMouseMoveCallback(mouse_move_callback callback) = 0;
};

#endif