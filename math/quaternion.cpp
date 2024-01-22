#include "quaternion.h"
#include <math.h>

#define TO_RADIAN(degs) (degs * M_PI / 180.0)

Quaternion::Quaternion(float Angle, const Vector3f &V)
{
    float HalfAngleInRadians = TO_RADIAN(Angle / 2);

    float SineHalfAngle = sinf(HalfAngleInRadians);
    float CosHalfAngle = cosf(HalfAngleInRadians);

    x = V.x * SineHalfAngle;
    y = V.y * SineHalfAngle;
    z = V.z * SineHalfAngle;
    w = CosHalfAngle;
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::Normalize()
{
    float Length = sqrtf(x * x + y * y + z * z + w * w);

    x /= Length;
    y /= Length;
    z /= Length;
    w /= Length;
}

Quaternion Quaternion::Conjugate() const
{
    Quaternion ret(-x, -y, -z, w);
    return ret;
}

Quaternion Quaternion::operator*(const Vector3f &v)
{
    float wn = -(x * v.x) - (y * v.y) - (z * v.z);
    float xn = (w * v.x) + (y * v.z) - (z * v.y);
    float yn = (w * v.y) + (z * v.x) - (x * v.z);
    float zn = (w * v.z) + (x * v.y) - (y * v.x);

    Quaternion ret(xn, yn, zn, wn);

    return ret;
}

Quaternion Quaternion::operator*(const Quaternion &r)
{
    float wn = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
    float xn = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
    float yn = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
    float zn = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

    Quaternion ret(xn, yn, zn, wn);

    return ret;
}

Vector3f Quaternion::ToDegrees()
{
    float f[3];

    f[0] = atan2(x * z + y * w, x * w - y * z);
    f[1] = acos(-x * x - y * y - z * z - w * w);
    f[2] = atan2(x * z - y * w, x * w + y * z);

    f[0] = TO_DEGREE(f[0]);
    f[1] = TO_DEGREE(f[1]);
    f[2] = TO_DEGREE(f[2]);

    return Vector3f(f[0], f[1], f[2]);
}
