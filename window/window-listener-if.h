#ifndef _WINDOW_LISTENER_IF_H
#define _WINDOW_LISTENER_IF_H

typedef void (*window_resized_callback)(int windowWidth, int windowHeight);

class WindowListenerIF
{
public:
    virtual void RegisterForWindowResized(window_resized_callback callback) = 0;
    virtual void UnregisterForWindowResized(window_resized_callback callback) = 0;
};

#endif
