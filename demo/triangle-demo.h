#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "math.h"

class TriangleDemo
{
private:
    static TriangleDemo *s_instance;
    TriangleDemo();

    Vector3f m_vertices[3];
    GLuint m_vbo;

public:
    static TriangleDemo *Instance(void);
    void Init(void);
    void Render(void);
};

#endif