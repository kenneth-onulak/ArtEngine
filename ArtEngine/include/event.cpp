
/*+*************************************************************************//*!
 \file:      event.h

 \summary:   track and handle events

 \structs    Scroll
 \classes:   Event

 \functions: Scroll::reset\n
             Event::input\n
             Event::handle\n
             Event::quit\n
             Event::key_down\n
             Event::key_down\n
             Event::scroll\n
             Event::resize_window\n

 \origin:    ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#include "pch.h"

////////////////////////////////////////////////////////////////////////////////
//// SCROLL STRUCT
////////////////////////////////////////////////////////////////////////////////

/*M+M***********************************************************************//*!
 \method:   Scroll::reset

 \summary:  reset the scroll direction indicators

 \modifies: [positive_x, positive_y, negative_x, negative_y].
************************************************************************//*M-M*/
void Scroll::reset()
{
    positive_x = positive_y = negative_x = negative_y = false;
}

////////////////////////////////////////////////////////////////////////////////
//// EVENT CLASS
////////////////////////////////////////////////////////////////////////////////

/*M+M***********************************************************************//*!
 \method:   Event::input

 \summary:  track inputs and add them to the stack

 \modifies: [m_input, m_quit, m_key_down, m_key_up, m_scroll, m_mouse,
            m_mouse_move, m_button_down, m_button_up, m_window_event,
            m_window_resize]
************************************************************************//*M-M*/
void Event::input()
{
    while (SDL_PollEvent(&m_input))
    {
        ImGui_ImplSDL2_ProcessEvent(&m_input);

        switch (m_input.type)
        {
        case SDL_QUIT:
            m_quit = true;
            break;
        case SDL_KEYDOWN:
            m_key_down[m_input.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_key_down[m_input.key.keysym.sym] = false;
            m_key_up.push_front(static_cast<SDL_KeyCode>(m_input.key.keysym.sym));
            break;
        case SDL_MOUSEWHEEL:
            m_scroll.positive_x = (m_input.wheel.x > 0.99);  // right
            m_scroll.positive_y = (m_input.wheel.y > 0.99);  // up
            m_scroll.negative_x = (m_input.wheel.x < -0.99); // left
            m_scroll.negative_y = (m_input.wheel.y < -0.99); // down
            break;
        case SDL_MOUSEMOTION:
            m_mouse = m_input.motion;
            m_mouse_move = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_button_down[m_input.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_button_down[m_input.button.button] = false;
            m_button_up.push_front(m_input.button.button);
            break;
        case SDL_WINDOWEVENT:
            // only handle resizing events
            if (m_input.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_window_event = m_input;
                m_window_resize = true;
            }
            break;
        default:
            break;
        }
    }
}

/*M+M***********************************************************************//*!
 \method:   Event::handle

 \summary:  event input handler

 \args:     view - view to potentially resize

 \modifies: [m_key_up, m_button_up, m_scroll, m_mouse_move, m_window_resize]
************************************************************************//*M-M*/
void Event::handle(View &view)
{
    if (m_window_resize)
    {
        view.width(m_window_event.window.data1);
        view.height(m_window_event.window.data2);
    }

    handler(); // call user-defined handler

    if (!m_key_up.empty())
    {
        // toggle interface visibility
        if (m_key_up.back() == SDLK_ESCAPE)
            view.toggle_interface();

        // toggle fullscreen
        if (m_key_up.back() == SDLK_F11)
        {
            view.toggle_fullscreen();
            if (!view.fullscreen())
                SDL_SetWindowFullscreen(view.window(), 0);
            else
                SDL_SetWindowFullscreen(view.window(), SDL_WINDOW_FULLSCREEN_DESKTOP);
        }

        m_key_up.pop_back();
    }

    // reset event triggers
    if (!m_button_up.empty())
        m_button_up.pop_back();

    m_scroll.reset();
    m_mouse_move = false;
    m_window_resize = false;
}

/*M+M***********************************************************************//*!
 \method:   Event::quit

 \summary:  accessor to return if shutdown was called

 \return:   True, shutdown was called
 \return:   False, otherwise
************************************************************************//*M-M*/
bool Event::quit() const
{
    return m_quit;
}

/*M+M***********************************************************************//*!
 \method:   Event::quit

 \summary:  accessor to set shutdown value

 \args:     quit - boolean representing if shutdown should be called or not

 \modifies: [m_quit]
************************************************************************//*M-M*/
void Event::quit(bool quit)
{
    m_quit = quit;
}

/*M+M***********************************************************************//*!
 \method:   Event::key_down

 \summary:  accessor to check if a key is down

 \args:     key - SDL_Keycode to check

 \return:   True, if the key is down
 \return:   False, otherwise
************************************************************************//*M-M*/
bool Event::key_down(SDL_Keycode key)
{
    return m_key_down[key];
}

SDL_KeyCode Event::key_up() const
{
    if (!m_key_up.empty())
        return m_key_up.back();
    else
        return SDLK_UNKNOWN;
}

/*M+M***********************************************************************//*!
 \method:   Event::scroll

 \summary:  accessor to get the scroll direction

 \return:   Scroll - container controlling the scroll directions
************************************************************************//*M-M*/
Scroll Event::scroll() const
{
    return m_scroll;
}

/*M+M***********************************************************************//*!
 \method:   Event::resize_window

 \summary:  accessor to get if the window should be resized or not

 \return:   True, window was resized
 \return:   False, otherwise
************************************************************************//*M-M*/
bool Event::resize_window() const
{
    return m_window_resize;
}
