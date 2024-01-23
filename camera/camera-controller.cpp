#include "camera-controller.h"
#include "sdl-event-dispatcher.h"
#include "camera.h"

using namespace std;

CameraController *CameraController::s_instance = NULL;

static float s_mouseSensitivity = 2.0;

static void camera_controller_mouse_move_callback(int x, int y)
{
    CameraController::Instance()->MouseMoveCallback(x, y);
}

CameraController *CameraController::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new CameraController(640, 480);
    }

    return s_instance;
}

CameraController::CameraController(int windowWidth, int windowHeight)
{
    SDLEventDispatcher::Instance()->RegisterMouseMoveCallback(camera_controller_mouse_move_callback);
    m_lastMouseX = windowWidth / 2;
    m_lastMouseY = windowHeight / 2;
}

void CameraController::MouseMoveCallback(int x, int y)
{
    float xdiff = x - m_lastMouseX;
    float ydiff = y - m_lastMouseY;

    float xangle = (xdiff * s_mouseSensitivity) / 20.0;
    float yangle = (ydiff * s_mouseSensitivity) / 40.0;

    Camera::Instance()->RotateX(xangle);
    Camera::Instance()->RotateY(yangle);

    m_lastMouseX = x;
    m_lastMouseY = y;
}