#ifndef _FPS_CAMERA_CONTROLLER_H
#define _FPS_CAMERA_CONTROLLER_H

#include "engine.h"

class FPSCameraController
{
public:
    static FPSCameraController *Instance();

    FrameCallbackResult NextFrame();
    void MouseMoveCallback(int x, int y);
    void WindowResized(int windowWidth, int windowHeight);
    void KeyDown(char key);
    void KeyUp(char key);

private:
    FPSCameraController(int windowWidth, int windowHeight);
    static FPSCameraController *s_instance;

    int m_lastMouseX;
    int m_lastMouseY;
    int m_nextMouseX;
    int m_nextMouseY;
    int m_windowWidth;
    int m_windowHeight;
};

#endif