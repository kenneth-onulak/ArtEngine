/*+*************************************************************************//*!
 \file:      view.cpp

 \summary:   visual interface

 \classes:   View

 \functions: View::init\n
             View::quit\n
             View::render\n
             View::target\n
             View::draw_interface\n
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
#include "pch.h"

/*M+M***********************************************************************//*!
 \method:   View::init

 \summary:  initialize the visual interface and perform setup tasks

 \args:     window_name - name of the window
 \args:     width - width of the window
 \args:     height - height of the window

 \modifies: [m_width, m_height, m_window, m_context, m_io, m_enabled].

 \return:   True, if everything is initialized successfully
 \return:   False, otherwise
************************************************************************//*M-M*/
bool View::init(std::string window_name, int width, int height)
{
    m_enabled = m_windowed;
    m_width = width;
    m_height = height;

    if (m_anti_alias)
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, m_anti_alias);

    // initialize window
    Uint32 window_flags = SDL_WINDOW_OPENGL;
    if (!m_windowed)
        window_flags = window_flags | SDL_WINDOW_HIDDEN;

    m_window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width,
                                m_height, window_flags);
    if (!m_window)
    {
        std::cout << "Window could not be created! SDL_Error: ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetWindowResizable(m_window, SDL_TRUE);

    // initialize context
    m_context = SDL_GL_CreateContext(m_window);
    if (!m_context)
    {
        std::cout << "Context could not be created! SDL_Error: ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetSwapInterval(m_vsync);
    // launch GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = ImGui::GetIO();
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_context);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    if (m_anti_alias)
        glEnable(GL_MULTISAMPLE);

    // setup global OpenGL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    if (m_ccw)
        glFrontFace(GL_CCW);
    else
        glFrontFace(GL_CW);
    glLineWidth(m_line_width);
    glPointSize(m_point_size);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::cout << glGetString(GL_VERSION) << std::endl;
    return true;
}

/*M+M***********************************************************************//*!
 \method:   View::quit

 \summary:  shutdown and cleanup the visual interface

 \modifies: [m_context, m_window]
************************************************************************//*M-M*/
void View::quit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
}

/*M+M***********************************************************************//*!
 \method:   View::render

 \summary:  update the window, call user defined pipeline and draw the interface
            on top
************************************************************************//*M-M*/
void View::render()
{
    // call user-defined pipeline
    pipeline();

    // draw interface on top
    if (m_show_interface)
        draw_interface();

    // update the window
    SDL_GL_SwapWindow(m_window);
}

/*M+M***********************************************************************//*!
 \method:   View::target

 \summary:  target main window for drawing

 \args:     clear_color - rgb color used to clear the window
 \args:     clear_color_bit - toggle to clear color bit, default = true
 \args:     clear_depth_bit - toggle to clear depth bit, default = true
************************************************************************//*M-M*/
void View::target(glm::vec3 clear_color, bool clear_color_bit, bool clear_depth_bit)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_width, m_height);
    glClearColor(clear_color.r, clear_color.g, clear_color.b, 1);
    if (clear_color_bit)
        glClear(GL_COLOR_BUFFER_BIT);
    if (clear_depth_bit)
        glClear(GL_DEPTH_BUFFER_BIT);
}

/*M+M***********************************************************************//*!
 \method:   View::draw_interface

 \summary:  draw the ImGui interface and user defined interface
************************************************************************//*M-M*/
void View::draw_interface()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui::NewFrame();

    // draw user-defined interface
    interface();
    // ImGui::ShowDemoWindow(); // Demo-window for examples

    ImGui::Render();
    glViewport(0, 0, static_cast<int>(m_io.DisplaySize.x), static_cast<int>(m_io.DisplaySize.y));
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/*M+M***********************************************************************//*!
 \method:   View::enabled

 \summary:  accessor to get if the view is enabled

 \return:   bool - represents if the view is enabled
************************************************************************//*M-M*/
bool View::enabled() const
{
    return m_enabled;
}

/*M+M***********************************************************************//*!
 \method:   View::width

 \summary:  accessor to set the view width

 \args:     width - new view width

 \modifies: [m_width]
************************************************************************//*M-M*/
void View::width(unsigned width)
{
    m_width = width;
}

/*M+M***********************************************************************//*!
 \method:   View::height

 \summary:  accessor to set the view height

 \args:     height - new view height

 \modifies: [m_height]
************************************************************************//*M-M*/
void View::height(unsigned height)
{
    m_height = height;
}

/*M+M***********************************************************************//*!
 \method:   View::width

 \summary:  accessor to get the current view width

 \return:   unsigned int - the width of the view
************************************************************************//*M-M*/
unsigned View::width() const
{
    return m_width;
}

/*M+M***********************************************************************//*!
 \method:   View::height

 \summary:  accessor to get the current view height

 \return:   unsigned int - the height of the view
************************************************************************//*M-M*/
unsigned View::height() const
{
    return m_height;
}

/*M+M***********************************************************************//*!
 \method:   View::toggle_interface

 \summary:  accessor to toggle showing the interface

 \modifies: [m_show_interface]
************************************************************************//*M-M*/
void View::toggle_interface()
{
    m_show_interface = !m_show_interface;
}

/*M+M***********************************************************************//*!
 \method:   View::toggle_fullscreen

 \summary:  accessor to toggle fullscreen mode

 \modifies: [m_fullscreen]
************************************************************************//*M-M*/
void View::toggle_fullscreen()
{
    m_fullscreen = !m_fullscreen;
}

/*M+M***********************************************************************//*!
 \method:   View::fullscreen

 \summary:  accessor to get if the view is in fullscreen mode

 \return:   bool - represents if the view is in fullscreen mode or not
************************************************************************//*M-M*/
bool View::fullscreen() const
{
    return m_fullscreen;
}

/*M+M***********************************************************************//*!
 \method:   View::window

 \summary:  accessor to get the window pointer

 \return:   SDL_Window* - pointer to the active window
************************************************************************//*M-M*/
SDL_Window *View::window()
{
    return m_window;
}

/*M+M***********************************************************************//*!
 \method:   View::windowed

 \summary:  accessor to get if the view is windowed

 \return:   bool - represents if the view is windowed or not
************************************************************************//*M-M*/
bool View::windowed() const
{
    return m_windowed;
}

/*M+M***********************************************************************//*!
 \method:   View::windowed

 \summary:  accessor to set if the view is windowed or not

 \args:     is_windowed - boolean value representing windowed mode

 \modifies: [m_windowed]
************************************************************************//*M-M*/
void View::windowed(bool is_windowed)
{
    m_windowed = is_windowed;
}

void View::ccw(bool is_counter_clockwise)
{
    m_ccw = is_counter_clockwise;
}

void View::vsync(bool use_vsync)
{
    m_vsync = use_vsync;
}
