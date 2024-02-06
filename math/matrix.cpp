#include "matrix.h"
#include <cstring> // memset

Matrix4f::Matrix4f()
{
    memset(matrix, 0, sizeof(matrix));
}

Matrix4f::Matrix4f(float a0, float a1, float a2, float a3,
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

Matrix4f::Matrix4f(float *a)
{
    matrix[0][0] = a[0];
    matrix[0][1] = a[1];
    matrix[0][2] = a[2];
    matrix[0][3] = a[3];

    matrix[1][0] = a[4];
    matrix[1][1] = a[5];
    matrix[1][2] = a[6];
    matrix[1][3] = a[7];

    matrix[2][0] = a[8];
    matrix[2][1] = a[9];
    matrix[2][2] = a[10];
    matrix[2][3] = a[11];

    matrix[3][0] = a[12];
    matrix[3][1] = a[13];
    matrix[3][2] = a[14];
    matrix[3][3] = a[15];
}

Matrix4f Matrix4f::operator*(const Matrix4f &other)
{
    return Matrix4f(
        (matrix[0][0] * other.matrix[0][0]) + (matrix[0][1] * other.matrix[1][0]) + (matrix[0][2] * other.matrix[2][0]) + (matrix[0][3] * other.matrix[3][0]), // row 0 col 0
        (matrix[0][0] * other.matrix[0][1]) + (matrix[0][1] * other.matrix[1][1]) + (matrix[0][2] * other.matrix[2][1]) + (matrix[0][3] * other.matrix[3][1]), // row 0 col 1
        (matrix[0][0] * other.matrix[0][2]) + (matrix[0][1] * other.matrix[1][2]) + (matrix[0][2] * other.matrix[2][2]) + (matrix[0][3] * other.matrix[3][2]), // row 0 col 2
        (matrix[0][0] * other.matrix[0][3]) + (matrix[0][1] * other.matrix[1][3]) + (matrix[0][2] * other.matrix[2][3]) + (matrix[0][3] * other.matrix[3][3]), // row 0 col 3

        (matrix[1][0] * other.matrix[0][0]) + (matrix[1][1] * other.matrix[1][0]) + (matrix[1][2] * other.matrix[2][0]) + (matrix[1][3] * other.matrix[3][0]), // row 1 col 0
        (matrix[1][0] * other.matrix[0][1]) + (matrix[1][1] * other.matrix[1][1]) + (matrix[1][2] * other.matrix[2][1]) + (matrix[1][3] * other.matrix[3][1]), // row 1 col 1
        (matrix[1][0] * other.matrix[0][2]) + (matrix[1][1] * other.matrix[1][2]) + (matrix[1][2] * other.matrix[2][2]) + (matrix[1][3] * other.matrix[3][2]), // row 1 col 2
        (matrix[1][0] * other.matrix[0][3]) + (matrix[1][1] * other.matrix[1][3]) + (matrix[1][2] * other.matrix[2][3]) + (matrix[1][3] * other.matrix[3][3]), // row 1 col 3

        (matrix[2][0] * other.matrix[0][0]) + (matrix[2][1] * other.matrix[1][0]) + (matrix[2][2] * other.matrix[2][0]) + (matrix[2][3] * other.matrix[3][0]), // row 2 col 0
        (matrix[2][0] * other.matrix[0][1]) + (matrix[2][1] * other.matrix[1][1]) + (matrix[2][2] * other.matrix[2][1]) + (matrix[2][3] * other.matrix[3][1]), // row 2 col 1
        (matrix[2][0] * other.matrix[0][2]) + (matrix[2][1] * other.matrix[1][2]) + (matrix[2][2] * other.matrix[2][2]) + (matrix[2][3] * other.matrix[3][2]), // row 2 col 2
        (matrix[2][0] * other.matrix[0][3]) + (matrix[2][1] * other.matrix[1][3]) + (matrix[2][2] * other.matrix[2][3]) + (matrix[2][3] * other.matrix[3][3]), // row 2 col 3

        (matrix[3][0] * other.matrix[0][0]) + (matrix[3][1] * other.matrix[1][0]) + (matrix[3][2] * other.matrix[2][0]) + (matrix[3][3] * other.matrix[3][0]),  // row 2 col 0
        (matrix[3][0] * other.matrix[0][1]) + (matrix[3][1] * other.matrix[1][1]) + (matrix[3][2] * other.matrix[2][1]) + (matrix[3][3] * other.matrix[3][1]),  // row 2 col 1
        (matrix[3][0] * other.matrix[0][2]) + (matrix[3][1] * other.matrix[1][2]) + (matrix[3][2] * other.matrix[2][2]) + (matrix[3][3] * other.matrix[3][2]),  // row 2 col 2
        (matrix[3][0] * other.matrix[0][3]) + (matrix[3][1] * other.matrix[1][3]) + (matrix[3][2] * other.matrix[2][3]) + (matrix[3][3] * other.matrix[3][3])); // row 2 col 3
}

void Matrix4f::InitTranslationTransform(float x, float y, float z)
{
    matrix[0][0] = 1.0f;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = x;
    matrix[1][0] = 0.0f;
    matrix[1][1] = 1.0f;
    matrix[1][2] = 0.0f;
    matrix[1][3] = y;
    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 1.0f;
    matrix[2][3] = z;
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

void Matrix4f::InitCameraTransform(const Vector3f &Pos, const Vector3f &Target, const Vector3f &Up)
{
    Matrix4f CameraTranslation;
    CameraTranslation.InitTranslationTransform(-Pos.x, -Pos.y, -Pos.z);

    Matrix4f CameraRotateTrans;
    CameraRotateTrans.InitCameraTransform(Target, Up);

    *this = CameraRotateTrans * CameraTranslation;
}

void Matrix4f::InitCameraTransform(const Vector3f &Target, const Vector3f &Up)
{
    Vector3f N = Target;
    N.Normalize();

    Vector3f UpNorm = Up;
    UpNorm.Normalize();

    Vector3f U;
    U = UpNorm.Cross(N);
    U.Normalize();

    Vector3f V = N.Cross(U);

    matrix[0][0] = U.x;
    matrix[0][1] = U.y;
    matrix[0][2] = U.z;
    matrix[0][3] = 0.0f;
    matrix[1][0] = V.x;
    matrix[1][1] = V.y;
    matrix[1][2] = V.z;
    matrix[1][3] = 0.0f;
    matrix[2][0] = N.x;
    matrix[2][1] = N.y;
    matrix[2][2] = N.z;
    matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

void Matrix4f::SetIdentity()
{
    memset(matrix, 0, sizeof(matrix));
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[3][3] = 1;
}