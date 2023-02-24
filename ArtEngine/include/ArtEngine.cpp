/*+*************************************************************************//*!
 \file:        ArtEngine.cpp

 \summary:     Main header file for Art Engine. Includes all other engine files.

 \namespaces:  Art

 \functions:   sig_handler
               init
               window
               quit

 \origin:      ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#include "pch.h"
#include "ArtEngine.h"

namespace Art
{

View view;
Event event;

bool benchmark = false;
int average = 0;

/*!F+F**************************************************************************
 \function: sig_handler

 \summary:  quit when you catch a signal

 \arg:      signal - SIGINT
**************************************************************************F-F!*/
void sig_handler(int signal)
{
    event.quit(true);
}

/*!F+F**************************************************************************
 \function: init

 \summary:  initialize the engine

 \return:   True, if initialized successfully
 \return:   False, otherwise
**************************************************************************F-F!*/
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "SDL_Image could not initialize! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
        return false;
    }

    signal(SIGINT, &sig_handler);

    if (!view.windowed() && !view.init("ArtEngine OpenGL Context", 0, 0))
    {
        std::cout << "Failed to launch OpenGL Context" << std::endl;
        return false;
    }

    return true;
}

/*!F+F**************************************************************************
 \function: quit

 \summary:  shutdown and cleanup the engine
**************************************************************************F-F!*/
void quit()
{
    if (view.enabled())
        view.quit();
    TTF_Quit();
    SDL_Quit();
}

/*!F+F**************************************************************************
 \function: window

 \summary:  create a window

 \arg:      window_name - name of the window
 \arg:      width - width of the window
 \arg:      height - height of the window

 \return:   True, if created successfully
 \return:   False, otherwise
**************************************************************************F-F!*/
bool window(std::string window_name, int width, int height)
{
    view.windowed(true);

    if (!init())
        return false;

    // start the visual interface
    if (!view.init(window_name, width, height))
    {
        std::cout << "Failed to launch visual interface." << std::endl;
        return false;
    }

    return true;
}

} // namespace Art