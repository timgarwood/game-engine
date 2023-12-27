#include "engine-api.h"
#include "engine.h"
#include <stddef.h>
#include "SDL2/SDL_Events.h"

using namespace std;

void engine_register_module_init_callback(module_init_callback callback)
{
    Engine::Instance()->RegisterModuleInitCallback(callback);
}

void engine_register_frame_callback(frame_callback callback)
{
    Engine::Instance()->RegisterFrameCallback(callback);
}

void engine_unregister_frame_callback(frame_callback callback)
{
    Engine::Instance()->UnregisterFrameCallback(callback);
}

void engine_register_module_teardown_callback(module_teardown_callback callback)
{
    Engine::Instance()->RegisterModuleTeardownCallback(callback);
}

void engine_main_loop()
{
    Engine::Instance()->MainLoop();
}

Engine *Engine::s_instance = NULL;
Engine::Engine()
{
    s_instance = this;
}

Engine *Engine::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new Engine();
    }

    return s_instance;
}

void Engine::RegisterModuleInitCallback(module_init_callback callback)
{
    m_module_init_callbacks.push_back(callback);
}

void Engine::RegisterFrameCallback(frame_callback callback)
{
    m_frame_callbacks.push_back(callback);
}

void Engine::UnregisterFrameCallback(frame_callback callback)
{
    m_frame_callbacks.remove(callback);
}

void Engine::RegisterModuleTeardownCallback(module_teardown_callback callback)
{
    m_module_teardown_callbacks.push_back(callback);
}

void Engine::Init(void)
{
    list<module_init_callback>::iterator iter = m_module_init_callbacks.begin();
    for (; iter != m_module_init_callbacks.end(); ++iter)
    {
        (*iter)();
    }
}

void Engine::MainLoop(void)
{
    m_active = true;
    while (m_active)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                EndMainLoop();
            }
        }

        list<frame_callback>::iterator iter = m_frame_callbacks.begin();
        for (; iter != m_frame_callbacks.end(); ++iter)
        {

            (*iter)();
        }
    }
}

void Engine::EndMainLoop(void)
{
    m_active = false;

    m_module_init_callbacks.clear();
    m_frame_callbacks.clear();
}

void Engine::TearDown(void)
{
    list<module_teardown_callback>::iterator iter = m_module_teardown_callbacks.begin();
    for (; iter != m_module_teardown_callbacks.end(); ++iter)
    {
        (*iter)();
    }

    m_module_teardown_callbacks.clear();
}