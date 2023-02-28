#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

int main(int argc, char *args[])
{
    // initialize a window
    Art::window("Example Window", 600, 400);

    // add the Event handler
    Art::event.handler = [&]() {};

    // set up an ImGUI Interface here
    Art::view.interface = [&]() {};

    // define the rendering pipeline
    Art::view.pipeline = []() {
        Art::view.target(color::silver); // clear screen to silver
    };

    // execute the render loop
    Art::loop([&]() {});

    // shutdown and cleanup
    Art::quit();
    return 0;
}
