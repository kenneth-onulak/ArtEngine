/*+*************************************************************************//*!
 \file:      view.h

 \summary:   visual interface

 \classes:   View

 \functions: View::init\n
             View::quit\n
             View::render\n
             View::target\n
             View::draw_interface\n
             View::interface\n
             View::pipeline\n
             View::enabled\n
             View::width\n
             View::width\n
             View::height\n
             View::height\n
             View::toggle_interface\n
             View::toggle_fullscreen\n
             View::window\n
             View::windowed\n
             View::windowed\n

 \origin:    ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#ifndef ARTENGINE_VIEW_H
#define ARTENGINE_VIEW_H

/*C+C***********************************************************************//*!
 \class:    View

 \summary:  visual interface

 \methods:  init - initialize the window, context, launches glew, and performs
                   important setup steps\n
         :  quit - shutdown the window, context, and other things setup in init\n
         :  render - process user defined pipeline, and draw the interface\n
         :  target - target main window for drawing\n
         :  draw_interface - draw imgui interface\n
         :  interface - user-defined interface\n
         :  pipeline - user-defined pipeline\n
         :  enabled - accessor to get if the window is enabled\n
         :  width - accessor to set the window width\n
         :  width - accessor to get the window width\n
         :  height - accessor to set the window height\n
         :  height - accessor to get the window height\n
         :  toggle_interface - toggle the visual interface\n
         :  toggle_fullscreen - toggle fullscreen mode\n
         :  window - accessor to get the window pointer\n
         :  windowed - accessor to get if the window is in windowed mode\n
         :  windowed - accessor to set the windowed mode\n
************************************************************************//*C-C*/
class View
{
  public:
    // initialize and shutdown
    bool init(std::string window_name, int width, int height);
    void quit();

    // methods
    void render();
    void target(glm::vec3 clear_color, bool clear_color_bit = true, bool clear_depth_bit = true);
    void draw_interface();

    // user-defined
    Handle interface = [] {}; //!< user-defined interface
    Handle pipeline = [] {};  //!< user-defined pipeline

    // accessors
    [[nodiscard]] bool enabled() const;

    void width(unsigned width);
    [[nodiscard]] unsigned width() const;
    void height(unsigned height);
    [[nodiscard]] unsigned height() const;

    void toggle_interface();
    void toggle_fullscreen();

    [[nodiscard]] bool fullscreen() const;

    SDL_Window *window();

    [[nodiscard]] bool windowed() const;
    void windowed(bool is_windowed);

    void ccw(bool is_counter_clockwise);
    void vsync(bool use_vsync);

  private:
    // window
    unsigned int m_width;  //!< window width
    unsigned int m_height; //!< window height

    SDL_Window *m_window;    //!< window pointer
    SDL_GLContext m_context; //!< render context

    // interface
    ImGuiIO m_io;                  //!< ImGui inputs/outputs
    bool m_show_interface = false; //!< toggle ImGui interface

    // settings
    bool m_enabled = false;         //!< is the view enabled
    bool m_windowed = false;        //!< is the view windowed
    bool m_fullscreen = false;      //!< is the view fullscreen
    bool m_vsync = true;            //!< monitor synced with gpu
    bool m_ccw = true;              //!< use counter-clockwise winding
    unsigned int m_anti_alias = 16; //!< antialiasing samples
    float m_line_width = 1.0f;      //!< line width
    float m_point_size = 1.0f;      //!< point size

}; // class View

#endif // ARTENGINE_VIEW_H
