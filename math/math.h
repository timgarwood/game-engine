#ifndef _MATH_H
#define _MATH_H

#include <cstring> // memset

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

struct Matrix4f
{
    float matrix[4][4];
    Matrix4f()
    {
        memset(matrix, 0, sizeof(matrix));
    }

    Matrix4f(float a0, float a1, float a2, float a3,
             float a4, float a5, float a6, float a7,
             float a8, float a9, float a10, float a11,
             float a12, float a13, float a14, float a15)
    {
        matrix[0][0] = a0;
        matrix[0][1] = a1;
        matrix[0][2] = a2;
        matrix[0][3] = a3;

        matrix[1][0] = a4;
        matrix[1][1] = a5;
        matrix[1][2] = a6;
        matrix[1][3] = a7;

        matrix[2][0] = a8;
        matrix[2][1] = a9;
        matrix[2][2] = a10;
        matrix[2][3] = a11;

        matrix[3][0] = a12;
        matrix[3][1] = a13;
        matrix[3][2] = a14;
        matrix[3][3] = a15;
    }
};

#endif