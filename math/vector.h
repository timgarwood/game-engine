#ifndef _VECTOR_H
#define _VECTOR_H

struct Vector3f
{
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f Cross(const Vector3f &other);
    void Normalize();
    float Mag();
    void Rotate(float Angle, const Vector3f &V);

    float x;
    float y;
    float z;
};

struct Vector3i
{
    Vector3i();
    Vector3i(int x, int y, int z);

    int x;
    int y;
    int z;
};

#endif