#ifndef _CAMERA_H
#define _CAMERA_H

#include "camera-if.h"

class Camera : public CameraIF
{
public:
    static CameraIF *Instance();
    virtual void RotateX(float degrees);
    virtual void RotateY(float degrees);
    virtual void MoveForward(float inc);
    virtual void MoveBackward(float inc);
    virtual void MoveLeft(float inc);
    virtual void MoveRight(float inc);
    virtual void SetPosition(Vector3f position);
    virtual void SetLookAt(Vector3f target);
    virtual Vector3f GetPosition();
    virtual Matrix4f GetMatrix();

private:
    Camera();
    static CameraIF *s_instance;
    float m_angleX;
    float m_angleY;
    Vector3f m_position;
    Vector3f m_lookAt;
    Vector3f m_up;
};

#endif