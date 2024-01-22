#include "camera.h"

CameraIF *Camera::s_instance = NULL;

Camera::Camera()
{
    m_up = Vector3f(0, 1, 0);
    m_position = Vector3f(0, 0, 0);
    m_angleX = 270;
    m_angleY = 0;
}

CameraIF *Camera::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new Camera();
    }

    return s_instance;
}

void Camera::RotateX(float degrees)
{
    m_angleX += degrees;
}

void Camera::RotateY(float degrees)
{
    m_angleY += degrees;
}

void Camera::TranslateX(float inc)
{
    m_position.x += inc;
}

void Camera::TranslateY(float inc)
{
    m_position.y += inc;
}

void Camera::TranslateZ(float inc)
{
    m_position.z += inc;
}

void Camera::SetPosition(Vector3f position)
{
    m_position = position;
}

Vector3f Camera::GetPosition()
{
    return m_position;
}

Matrix4f Camera::GetMatrix()
{
    Vector3f Yaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_angleX, Yaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f U = Yaxis.Cross(View);
    U.Normalize();
    View.Rotate(m_angleY, U);

    View.Normalize();

    m_up = View.Cross(U);
    m_up.Normalize();

    Matrix4f cameraTransformation;
    cameraTransformation.InitCameraTransform(m_position, View, m_up);

    return cameraTransformation;

    /*   return Matrix4f(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
                       */
}