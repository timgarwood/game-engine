#ifndef _CAMERA_IF_H
#define _CAMERA_IF_H

#include "math.h"

class CameraIF
{
public:
    virtual void RotateX(float degrees) = 0;
    virtual void RotateY(float degrees) = 0;
    virtual void MoveForward(float inc) = 0;
    virtual void MoveBackward(float inc) = 0;
    virtual void MoveLeft(float inc) = 0;
    virtual void MoveRight(float inc) = 0;
    virtual void SetPosition(Vector3f position) = 0;
    virtual void SetLookAt(Vector3f target) = 0;
    virtual Vector3f GetPosition() = 0;
    virtual Matrix4f GetMatrix() = 0;
};

#endif