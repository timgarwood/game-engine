#ifndef _CAMERA_H
#define _CAMERA_H

#include "camera-if.h"

class Camera : public CameraIF
{
public:
    static CameraIF *Instance();
    virtual void RotateX(float degrees);
    virtual void RotateY(float degrees);
    virtual void TranslateX(float inc);
    virtual void TranslateY(float inc);
    virtual void TranslateZ(float inc);
    virtual void SetPosition(Vector3f position);
    virtual Vector3f GetPosition();
    virtual Matrix4f GetMatrix();

private:
    Camera();
    static CameraIF *s_instance;
    float m_angleX;
    float m_angleY;
    Vector3f m_position;
    Vector3f m_up;
};

#endif