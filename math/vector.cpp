#include "vector.h"
#include "quaternion.h"
#include <cmath>

Vector3f::Vector3f()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3f::Vector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f Vector3f::Cross(const Vector3f &other)
{
    float cx = (y * other.z) - (z * other.y);
    float cy = (z * other.x) - (x * other.z);
    float cz = (x * other.y) - (y * other.x);

    return Vector3f(cx, cy, cz);
}

void Vector3f::Normalize()
{
    float mag = Mag();
    x = x / mag;
    y = y / mag;
    z = z / mag;
}

float Vector3f::Mag()
{
    return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

void Vector3f::Rotate(float Angle, const Vector3f &V)
{
    Quaternion RotationQ(Angle, V);

    Quaternion ConjugateQ = RotationQ.Conjugate();

    Quaternion W = RotationQ * (*this) * ConjugateQ;

    x = W.x;
    y = W.y;
    z = W.z;
}

Vector3f Vector3f::operator*(const float &f)
{
    return Vector3f(this->x * f, this->y * f, this->z * f);
}

Vector3f Vector3f::operator+(const Vector3f &other)
{
    return Vector3f(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3f Vector3f::operator-(const Vector3f &other)
{
    return Vector3f(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3i::Vector3i()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3i::Vector3i(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}