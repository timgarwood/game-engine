#include "sdl-event-dispatcher.h"
#include "engine-api.h"
#include "SDL2/SDL_Events.h"
#include <algorithm>
#include <iostream>

using namespace std;

SDLEventDispatcher *SDLEventDispatcher::s_instance = NULL;

static FrameCallbackResult input_frame_callback()
{
    return SDLEventDispatcher::Instance()->FrameCallback();
}

SDLEventDispatcher::SDLEventDispatcher()
{
    engine_register_frame_callback(input_frame_callback);
}

SDLEventDispatcher *SDLEventDispatcher::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new SDLEventDispatcher();
    }

    return s_instance;
}

void SDLEventDispatcher::RegisterMouseMoveCallback(mouse_move_callback callback)
{
    m_mouseMoveCallbacks.push_back(callback);
}

void SDLEventDispatcher::UnregisterMouseMoveCallback(mouse_move_callback callback)
{
    auto iter = find(m_mouseMoveCallbacks.begin(), m_mouseMoveCallbacks.end(), callback);
    if (iter != m_mouseMoveCallbacks.end())
    {
        m_mouseMoveCallbacks.erase(iter);
    }
}

void SDLEventDispatcher::RegisterForWindowResized(window_resized_callback callback)
{
    m_windowResizedCallbacks.push_back(callback);
}

void SDLEventDispatcher::UnregisterForWindowResized(window_resized_callback callback)
{
    auto iter = find(m_windowResizedCallbacks.begin(), m_windowResizedCallbacks.end(), callback);
    if (iter != m_windowResizedCallbacks.end())
    {
        m_windowResizedCallbacks.erase(iter);
    }
}

void SDLEventDispatcher::RegisterForKeyDown(key_down_callback callback)
{
    m_keyDownCallbacks.push_back(callback);
}

void SDLEventDispatcher::UnregisterForKeyDown(key_down_callback callback)
{
    auto iter = find(m_keyDownCallbacks.begin(), m_keyDownCallbacks.end(), callback);
    if (iter != m_keyDownCallbacks.end())
    {
        m_keyDownCallbacks.erase(iter);
    }
}

void SDLEventDispatcher::RegisterForKeyUp(key_up_callback callback)
{
    m_keyUpCallbacks.push_back(callback);
}

void SDLEventDispatcher::UnregisterForKeyUp(key_up_callback callback)
{
    auto iter = find(m_keyUpCallbacks.begin(), m_keyUpCallbacks.end(), callback);
    if (iter != m_keyUpCallbacks.end())
    {
        m_keyUpCallbacks.erase(iter);
    }
}

FrameCallbackResult SDLEventDispatcher::FrameCallback()
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
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                auto iter = m_windowResizedCallbacks.begin();
                int width = event.window.data1;
                int height = event.window.data2;
                for (; iter != m_windowResizedCallbacks.end(); ++iter)
                {
                    (*iter)(width, height);
                }
            }
        }
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            char key;
            if (event.key.keysym.sym == SDLK_w)
            {
                key = 'w';
            }
            else if (event.key.keysym.sym == SDLK_s)
            {
                key = 's';
            }
            else if (event.key.keysym.sym == SDLK_a)
            {
                key = 'a';
            }
            else if (event.key.keysym.sym == SDLK_d)
            {
                key = 'd';
            }
            else
            {
                continue;
            }

            if (event.type == SDL_KEYDOWN)
            {
                SendKeyDown(key);
            }
            else
            {
                SendKeyUp(key);
            }
        }
    }

    return CONTINUE;
}

void SDLEventDispatcher::SendKeyDown(char key)
{
    auto iter = m_keyDownCallbacks.begin();
    for (; iter != m_keyDownCallbacks.end(); ++iter)
    {
        (*iter)(key);
    }
}

void SDLEventDispatcher::SendKeyUp(char key)
{
    auto iter = m_keyUpCallbacks.begin();
    for (; iter != m_keyUpCallbacks.end(); ++iter)
    {
        (*iter)(key);
    }
}