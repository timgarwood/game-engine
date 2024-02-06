#ifndef _MATRIX_H
#define _MATRIX_H

#include "vector.h"

struct Matrix4f
{
    float matrix[4][4];
    Matrix4f();
    Matrix4f(float a0, float a1, float a2, float a3,
             float a4, float a5, float a6, float a7,
             float a8, float a9, float a10, float a11,
             float a12, float a13, float a14, float a15);
    Matrix4f(float *a);

    Matrix4f operator*(const Matrix4f &other);
    void InitCameraTransform(const Vector3f &Target, const Vector3f &Up);
    void InitCameraTransform(const Vector3f &Pos, const Vector3f &Target, const Vector3f &Up);
    void InitTranslationTransform(float x, float y, float z);
    void SetIdentity();
};

#endif