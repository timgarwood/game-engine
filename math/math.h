#ifndef _MATH_H
#define _MATH_H

#include <gl/gl.h>
#include <cmath>
#include "vector.h"
#include "matrix.h"
#include <cstring>

#define TO_DEGREE(rads) (rads * 180.0 / M_PI)
#define TO_RADIAN(degs) (degs * M_PI / 180.0)

struct Vertex3f
{
    Vertex3f()
    {
        memset(&coords, 0, sizeof(Vector3f));
        memset(&color, 0, sizeof(Vector3f));
    }

    Vertex3f(Vector3f coords, Vector3f color)
    {
        this->coords = coords;
        this->color = color;
    }

    Vector3f coords;
    Vector3f color;
};

struct Triangle
{
    Vector3f vertices[3];
    Matrix4f translationMatrix;
    Matrix4f rotationMatrix;
    float rotation;
    float rotationDelta;
    GLuint vbo;

    Triangle()
    {
        memset(vertices, 0, sizeof(vertices));
        memset(&translationMatrix, 0, sizeof(Matrix4f));
        memset(&rotationMatrix, 0, sizeof(Matrix4f));

        rotation = 0.0f;
    }

    Triangle(Vector3f one, Vector3f two, Vector3f three)
    {
        vertices[0] = one;
        vertices[1] = two;
        vertices[2] = three;

        memset(&translationMatrix, 0, sizeof(Matrix4f));
        memset(&rotationMatrix, 0, sizeof(Matrix4f));

        rotation = 0.0f;
    }
};

#endif