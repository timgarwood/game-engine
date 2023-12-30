#ifndef _MATH_H
#define _MATH_H

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

#endif