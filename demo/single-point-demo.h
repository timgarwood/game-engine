#ifndef _SINGLE_POINT_DEMO_H
#define _SINGLE_POINT_DEMO_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "math.h"

class SinglePointDemo
{
private:
    static SinglePointDemo *s_instance;
    SinglePointDemo();

    Vector3f m_vertices[2];
    GLuint m_vbo;

public:
    static SinglePointDemo *Instance(void);
    void Init(void);
    void Render(void);
};

#endif