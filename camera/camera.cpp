#include "camera.h"
#include "vector.h"

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

void Camera::MoveForward(float mult)
{
    m_position = m_position + (m_lookAt * mult);
}

void Camera::MoveBackward(float mult)
{
    m_position = m_position - (m_lookAt * mult);
}

void Camera::MoveRight(float mult)
{
    Vector3f moveAlong = m_lookAt;
    moveAlong.Rotate(270, m_up);
    moveAlong.Normalize();

    m_position = m_position - (moveAlong * mult);
}

void Camera::MoveLeft(float mult)
{
    Vector3f moveAlong = m_lookAt;
    moveAlong.Rotate(270, m_up);
    moveAlong.Normalize();

    m_position = m_position + (moveAlong * mult);
}

void Camera::SetPosition(Vector3f position)
{
    m_position = position;
}

void Camera::SetLookAt(Vector3f target)
{
    m_angleX = target.x;
    m_angleY = target.y;
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

    m_lookAt = View;

    m_up = View.Cross(U);
    m_up.Normalize();

    Matrix4f cameraTransformation;
    cameraTransformation.InitCameraTransform(m_position, View, m_up);

    return cameraTransformation;
}