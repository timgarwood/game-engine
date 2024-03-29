#include "graphics-engine.h"
#include "engine-api.h"
#include "sdl-event-dispatcher.h"
#include <GL/glew.h>
#include "SDL2/SDL.h"
#include <stddef.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

GraphicsEngine *GraphicsEngine::s_instance = NULL;
SDL_Window *s_window = NULL;
SDL_GLContext s_glContext;

static void graphics_init(void)
{
    GraphicsEngine::Instance()->Init();
}

static FrameCallbackResult graphics_next_frame(void)
{
    return GraphicsEngine::Instance()->NextFrame();
}

static void graphics_teardown(void)
{
    GraphicsEngine::Instance()->TearDown();
}

static void graphics_engine_window_resize(int width, int height)
{
    GraphicsEngine::Instance()->Resize(width, height);
}

GraphicsEngine::GraphicsEngine()
{
    engine_register_module_init_callback(graphics_init);
    engine_register_frame_callback(graphics_next_frame);
    engine_register_module_teardown_callback(graphics_teardown);
    SDLEventDispatcher::Instance()->RegisterForWindowResized(graphics_engine_window_resize);
}

GraphicsEngine *GraphicsEngine::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new GraphicsEngine();
    }

    return s_instance;
}

FrameCallbackResult GraphicsEngine::NextFrame(void)
{
    if (s_window == NULL)
    {
        // TODO throw exception
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto iter = m_render_callbacks.begin();
    for (; iter != m_render_callbacks.end(); ++iter)
    {
        (*iter)();
    }

    SDL_GL_SwapWindow(s_window);

    return CONTINUE;
}

void GraphicsEngine::Init(void)
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    s_window = SDL_CreateWindow("Engine", 10, 10, 640, 480, flags);

    s_glContext = SDL_GL_CreateContext(s_window);

    // request double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        cerr << "Error: " << glewGetErrorString(res);
        return;
    }
}

void GraphicsEngine::Resize(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void GraphicsEngine::TearDown(void)
{
    SDL_DestroyWindow(s_window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    s_window = NULL;
}

void GraphicsEngine::RegisterRenderCallback(render_callback callback)
{
    m_render_callbacks.push_back(callback);
}

void GraphicsEngine::UnregisterRenderCallback(render_callback callback)
{
    m_render_callbacks.remove(callback);
}