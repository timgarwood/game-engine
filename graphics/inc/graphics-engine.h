#ifndef _GRAPHICS_ENGINE_H
#define _GRAPHICS_ENGINE_H

#include <list>
#include "engine.h"

typedef void (*render_callback)(void);

class GraphicsEngine
{
private:
    static GraphicsEngine *s_instance;
    GraphicsEngine();

    std::list<render_callback> m_render_callbacks;

public:
    static GraphicsEngine *Instance(void);
    void Init(void);
    void RegisterRenderCallback(render_callback callback);
    FrameCallbackResult NextFrame(void);
    void UnregisterRenderCallback(render_callback callback);
    void TearDown(void);
};

#endif