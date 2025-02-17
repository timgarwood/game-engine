#ifndef _RAYCASTER_H
#define _RAYCASTER_H

#include <gl/GL.h>
#include "vector.h"

class Raycaster
{
public:
    static Raycaster *Instance();
    void Render();
    void Init();
    void WindowResized(int width, int height);

private:
    static Raycaster *s_instance;
    Raycaster();

    Vector3f *m_columns;
    GLuint m_vbo;
};

#endif