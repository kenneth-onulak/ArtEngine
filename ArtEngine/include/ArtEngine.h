/*+*************************************************************************//*!
 \file:        ArtEngine.h

 \summary:     Main header file for Art Engine. Includes all other engine files.

 \namespaces:  Art

 \functions:   sig_handler
               init
               window
               quit
               loop

 \origin:      ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#ifndef ARTENGINE_ARTENGINE_H
#define ARTENGINE_ARTENGINE_H

#ifndef ARTENGINE_NAMESPACE
#define ARTENGINE_NAMESPACE

#include "view.h"
#include "event.h"
#include "helpers/timer.h"

namespace Art
{

extern View view;   //!< window and interface (requires initialization)
extern Event event; //!< event handler

void sig_handler(int signal);
bool init();
void quit();

bool window(std::string window_name, int width, int height);

extern bool benchmark; //!< benchmark the game loop
extern int average;    //!< average for benchmarking the game loop

/*!F+F**************************************************************************
 \function: loop

 \summary:  perform the game loop with or without benchmarking data

 \arg:      function - user-defined game loop
 \arg:      args -user defined function arguments
**************************************************************************F-F!*/
template <typename F, typename... Args>
void loop(F function, Args &&...args)
{
    // perform the loop without benchmarking data
    if (!benchmark)
    {
        while (!event.quit())
        {
            if (view.enabled())
            {
                event.input();      // get input
                event.handle(view); // call event-handling system
            }

            function(args...); // user-defined game loop

            if (view.enabled())
            {
                view.render(); // render the view
            }
        }
        return; // completed main loop
    }

    // perform the loop with benchmarking data
    while (!event.quit())
    {
        if (view.enabled())
        {
            // get input
            std::cout << "Event Input ";
            timer::benchmark<std::chrono::milliseconds>([&]() { event.input(); });
            // call event-handling system
            std::cout << "Event Handling ";
            timer::benchmark<std::chrono::milliseconds>([&]() { event.handle(view); });
        }

        // user-defined game loop
        std::cout << "Loop Function ";
        timer::benchmark<std::chrono::microseconds>([&]() { function(args...); });

        if (Art::view.enabled())
        {
            // render view
            std::cout << "Render Pipeline ";
            double d = 0.99 * average + 0.01 * timer::benchmark<std::chrono::microseconds>([&]() {
                                            view.render();
                                            glFinish();
                                        });
            average = static_cast<int>(d);
        }
    }
}

} // namespace Art

#endif // ARTENGINE_NAMESPACE

#endif // ARTENGINE_ARTENGINE_H
