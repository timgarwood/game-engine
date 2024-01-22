#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "vector.h"

struct Quaternion
{
    Quaternion(float Angle, const Vector3f &V);
    Quaternion(float _x, float _y, float _z, float _w);
    void Normalize();
    Quaternion Conjugate() const;
    Quaternion operator*(const Vector3f &v);
    Quaternion operator*(const Quaternion &r);
    Vector3f ToDegrees();

    float x;
    float y;
    float z;
    float w;
};

#endif