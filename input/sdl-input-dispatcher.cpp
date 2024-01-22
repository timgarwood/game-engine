#include "sdl-input-dispatcher.h"
#include "engine-api.h"
#include "SDL2/SDL_Events.h"
#include <algorithm>
#include <iostream>

using namespace std;

SDLInputDispatcher *SDLInputDispatcher::s_instance = NULL;

static FrameCallbackResult input_frame_callback()
{
    return SDLInputDispatcher::Instance()->FrameCallback();
}

SDLInputDispatcher::SDLInputDispatcher()
{
    engine_register_frame_callback(input_frame_callback);
}

SDLInputDispatcher *SDLInputDispatcher::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new SDLInputDispatcher();
    }

    return s_instance;
}

void SDLInputDispatcher::RegisterMouseMoveCallback(mouse_move_callback callback)
{
    m_mouseMoveCallbacks.push_back(callback);
}

void SDLInputDispatcher::UnregisterMouseMoveCallback(mouse_move_callback callback)
{
    auto iter = find(m_mouseMoveCallbacks.begin(), m_mouseMoveCallbacks.end(), callback);
    if (iter != m_mouseMoveCallbacks.end())
    {
        m_mouseMoveCallbacks.erase(iter);
    }
}

FrameCallbackResult SDLInputDispatcher::FrameCallback()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            return EXIT;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            auto iter = m_mouseMoveCallbacks.begin();
            int x = event.motion.x;
            int y = event.motion.y;
            for (; iter != m_mouseMoveCallbacks.end(); ++iter)
            {
                (*iter)(x, y);
            }
        }
    }

    return CONTINUE;
}