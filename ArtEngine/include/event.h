/*+*************************************************************************//*!
 \file:      event.h

 \summary:   track and handle events

 \structs    Scroll
 \classes:   Event

 \functions: Scroll::reset\n
             Event::input\n
             Event::handle\n
             Event::handler\n
             Event::quit\n
             Event::key_down\n
             Event::scroll\n
             Event::resize_window\n

 \origin:    ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#ifndef ARTENGINE_EVENT_H
#define ARTENGINE_EVENT_H

/*S+S***********************************************************************//*!
 \struct:   Scroll

 \summary:  control scroll direction

 \methods:  reset - resets scroll direction to none
************************************************************************//*S-S*/
struct Scroll
{
    bool positive_x; //!< scroll right
    bool positive_y; //!< scroll up
    bool negative_x; //!< scroll left
    bool negative_y; //!< scroll down

    void reset();

}; // struct Scroll

/*C+C***********************************************************************//*!
 \class:    Event

 \summary:  track and handle input events

 \methods:  input - take inputs and add them to the stack\n
         :  handle - general event handler\n
         :  handler - user-defined event handler\n
         :  quit - accessor to get if shutdown was called\n
         :  key_down - accessor to check if a key is down\n
         :  scroll - accessor to get scroll directions\n
         :  resize_window - accessor to check if the window was resized\n
************************************************************************//*C-C*/
class Event
{
  public:
    void input();
    void handle(View &view);

    // user-defined
    Handle handler = []{}; //!< user-defined event handler

    // accessors
    [[nodiscard]] bool quit() const;
    void quit(bool quit);
    [[nodiscard]] bool key_down(SDL_Keycode key);
    [[nodiscard]] SDL_KeyCode key_up() const;
    [[nodiscard]] Scroll scroll() const;
    [[nodiscard]] bool resize_window() const;

  private:
    // public variables
    bool m_quit = false;      //!< shutdown
    bool m_toggle_fullscreen; //!< switch between fullscreen view

    // keyboard events
    std::unordered_map<SDL_Keycode, bool> m_key_down; //!< active keys
    std::deque<SDL_KeyCode> m_key_up;                 //!< key released

    // movement events
    SDL_MouseMotionEvent m_mouse; //!< active mouse
    bool m_mouse_move = false;    //!< mouse in motion

    // clicking events
    std::unordered_map<Uint8, bool> m_button_down; //!< active buttons
    std::deque<Uint8> m_button_up;                 //!< button released

    // scroll events
    Scroll m_scroll;              //!< scroll directions
    SDL_Event m_window_event;     //!< window resizing event
    bool m_window_resize = false; //!< window is resizing

    SDL_Event m_input; //!< SDL general events

}; // class Event

#endif // ARTENGINE_EVENT_H
