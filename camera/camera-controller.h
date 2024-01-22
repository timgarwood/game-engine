#ifndef _CAMERA_CONTROLLER_H
#define _CAMERA_CONTROLLER_H

class CameraController
{
public:
    static CameraController *Instance();

    void MouseMoveCallback(int x, int y);

private:
    CameraController(int windowWidth, int windowHeight);
    static CameraController *s_instance;

    int m_lastMouseX;
    int m_lastMouseY;
};

#endif