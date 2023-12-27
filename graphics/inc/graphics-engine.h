#ifndef _GRAPHICS_ENGINE_H
#define _GRAPHICS_ENGINE_H

class GraphicsEngine
{
private:
    static GraphicsEngine *s_instance;
    GraphicsEngine();

public:
    static GraphicsEngine *Instance(void);
    void Init(void);
    void NextFrame(void);
    void TearDown(void);
};

#endif