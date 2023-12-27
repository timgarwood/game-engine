#include "graphics-engine.h"
#include "engine-api.h"
#include "SDL2/SDL.h"
#include <stddef.h>

GraphicsEngine *GraphicsEngine::s_instance = NULL;
SDL_Window *s_window = NULL;
SDL_GLContext s_glContext;

static void graphics_init(void)
{
    GraphicsEngine::Instance()->Init();
}

static void graphics_next_frame(void)
{
    GraphicsEngine::Instance()->NextFrame();
}

static void graphics_teardown(void)
{
    GraphicsEngine::Instance()->TearDown();
}

GraphicsEngine::GraphicsEngine()
{
    s_instance = this;
    engine_register_module_init_callback(graphics_init);
    engine_register_frame_callback(graphics_next_frame);
    engine_register_module_teardown_callback(graphics_teardown);
}

GraphicsEngine *GraphicsEngine::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new GraphicsEngine();
    }

    return s_instance;
}

void GraphicsEngine::NextFrame(void)
{
    if (s_window == NULL)
    {
        // TODO throw exception
    }

    SDL_GL_SwapWindow(s_window);
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
}

void GraphicsEngine::TearDown(void)
{
    SDL_DestroyWindow(s_window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    s_window = NULL;
}