#ifndef _SINGLE_POINT_DEMO_H
#define _SINGLE_POINT_DEMO_H

#include <GL/gl.h>
#include <GL/glu.h>

struct Vector3f
{
    Vector3f()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3f(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float x;
    float y;
    float z;
};

class SinglePointDemo
{
private:
    static SinglePointDemo *s_instance;
    SinglePointDemo();

    Vector3f m_vertices[1];
    GLuint m_vbo;

public:
    static SinglePointDemo *Instance(void);
    void Init(void);
    void Render(void);
};

#endif