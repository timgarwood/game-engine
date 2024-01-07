#ifndef _MATH_H
#define _MATH_H

#include <cstring> // memset
#include <gl/gl.h>

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

struct Vector3i
{
    Vector3i()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3i(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    int x;
    int y;
    int z;
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

    Matrix4f multiply(const Matrix4f &other)
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