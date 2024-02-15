#include "fps-camera-controller.h"
#include "sdl-event-dispatcher.h"
#include "camera.h"

using namespace std;

FPSCameraController *FPSCameraController::s_instance = NULL;

static float s_mouseSensitivity = 2.0;
static float s_moveSensitivity = 1.0;
static float s_moveX = 10;
static float s_moveY = 10;

static FrameCallbackResult fps_camera_controller_next_frame()
{
    return FPSCameraController::Instance()->NextFrame();
}

static void camera_controller_window_resized(int windowWidth, int windowHeight)
{
    FPSCameraController::Instance()->WindowResized(windowWidth, windowHeight);
}

static void camera_controller_mouse_move_callback(int x, int y)
{
    FPSCameraController::Instance()->MouseMoveCallback(x, y);
}

static void camera_controller_key_down(char key)
{
    FPSCameraController::Instance()->KeyDown(key);
}

static void camera_controller_key_up(char key)
{
    FPSCameraController::Instance()->KeyUp(key);
}

FPSCameraController *FPSCameraController::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new FPSCameraController(640, 480);
    }

    return s_instance;
}

FPSCameraController::FPSCameraController(int windowWidth, int windowHeight)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    Engine::Instance()->RegisterFrameCallback(fps_camera_controller_next_frame);
    SDLEventDispatcher::Instance()->RegisterMouseMoveCallback(camera_controller_mouse_move_callback);
    SDLEventDispatcher::Instance()->RegisterForKeyDown(camera_controller_key_down);
    SDLEventDispatcher::Instance()->RegisterForKeyUp(camera_controller_key_up);
    SDLEventDispatcher::Instance()->RegisterForWindowResized(camera_controller_window_resized);
    m_lastMouseX = windowWidth / 2;
    m_lastMouseY = windowHeight / 2;
    m_nextMouseX = m_lastMouseX;
    m_nextMouseY = m_lastMouseY;
}

FrameCallbackResult FPSCameraController::NextFrame()
{
    int xdiff = 0;
    int ydiff = 0;
    if (m_nextMouseX < m_lastMouseX || m_nextMouseX <= 0)
    {
        xdiff = -s_moveX;
    }
    else if (m_nextMouseX > m_lastMouseX || (m_nextMouseX >= (m_windowWidth - 1)))
    {
        xdiff = s_moveX;
    }

    if (m_nextMouseY < m_lastMouseY || m_nextMouseY <= 0)
    {
        ydiff = -s_moveY;
    }
    else if (m_nextMouseY > m_lastMouseY || m_nextMouseY >= (m_windowHeight - 1))
    {
        ydiff = s_moveY;
    }

    if (xdiff != 0 || ydiff != 0)
    {
        float xangle = ((float)(xdiff * s_mouseSensitivity)) / 20.0;
        float yangle = ((float)(ydiff * s_mouseSensitivity)) / 40.0;

        Camera::Instance()->RotateX(xangle);
        Camera::Instance()->RotateY(yangle);
    }

    m_lastMouseX = m_nextMouseX;
    m_lastMouseY = m_nextMouseY;

    return CONTINUE;
}

void FPSCameraController::WindowResized(int windowWidth, int windowHeight)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}

void FPSCameraController::MouseMoveCallback(int x, int y)
{
    m_nextMouseX = x;
    m_nextMouseY = y;
}

void FPSCameraController::KeyDown(char key)
{
    if (key == 'w')
    {
        Camera::Instance()->MoveForward(s_moveSensitivity);
    }
    else if (key == 's')
    {
        Camera::Instance()->MoveBackward(s_moveSensitivity);
    }
    else if (key == 'a')
    {
        Camera::Instance()->MoveLeft(s_moveSensitivity);
    }
    else if (key == 'd')
    {
        Camera::Instance()->MoveRight(s_moveSensitivity);
    }
}

void FPSCameraController::KeyUp(char key)
{
}