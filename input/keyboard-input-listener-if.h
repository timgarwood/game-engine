#ifndef _KEYBOARD_INPUT_LISTENER_IF_H
#define _KEYBOARD_INPUT_LISTENER_IF_H

typedef void (*key_up_callback)(char key);
typedef void (*key_down_callback)(char key);

class KeyboardInputListenerIF
{
public:
    virtual void RegisterForKeyDown(key_down_callback callback) = 0;
    virtual void UnregisterForKeyDown(key_down_callback callback) = 0;
    virtual void RegisterForKeyUp(key_up_callback callback) = 0;
    virtual void UnregisterForKeyUp(key_up_callback callback) = 0;
};

#endif