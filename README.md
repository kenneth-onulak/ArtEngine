# Art Engine

- Kenneth Onulak Jr.
- kenneth.onulakjr@digipen.edu
- Exploratory Engine framework for completing DigiPen course work.

### Info:
- The `Release` folder contains an example executable and necessary dlls.  
- The `ArtEngine` folder contains the source code.
- Third party libraries / dependencies are not included and will need to be installed to build.

### Installing Dependencies:
#### vcpkg
Follow the instructions at https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160#installation to clone the vcpkg repository.

Make sure to follow the integration instructions at https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160#installation on a per-user basis so that include paths are resolved automagically.

The following packages need to be installed to build and compile.  

#### SDL2
    ./vcpkg install sdl2:x64-windows
    ./vcpkg install sdl2-image:x64-windows
    ./vcpkg install sdl2-ttf:x64-windows
    ./vcpkg install sdl2-mixer:x64-windows

#### GLEW 
    ./vcpkg install glew:x64-windows

#### GLM 
    ./vcpkg install glm:x64-windows

#### Boost Filesystem
    ./vcpkg install boost-filesystem:x64-windows

#### Libnoise
    ./vcpkg install libnoise:x64-windows

#### Freetype
    ./vcpkg install freetype:x64-windows

#### Imgui
    ./vcpkg install imgui:x64-windows

#### Implot
    ./vcpkg install implot:x64-windows

### Build:
NOTE: You must set `-DCMAKE_TOOLCHAIN_FILE` for vcpkg. Such as the following where you just need to change `{PATH TO VCPKG}` to match your local vcpkg directory.  

    -DCMAKE_TOOLCHAIN_FILE={PATH TO VCPKG}/scripts/buildsystems/vcpkg.cmake

- Built using C++ 20
- Compiled with MSVC CMake in CLion on Windows
- While not tested extensively, nothing should prevent the framework from compiling on Linux should the necessary dependencies be installed and linked properly. 

### Directory File Structure:
```
- ArtEngine
    - examples
        - cubic_spline        // contains all project files
            - object
            - shader
                - default.fs
                - default.vs
            - cubic_spline.h
            - main.cpp
            - settings.h
    - include
        - ... // all engine source files
    - CMakeLists.txt // modify the EXAMPLE_DIR to build a different project
```

### About
This engine was created to learn more about Graphics Programming and used to complete my graphics course work at DigiPen. This is a learning environment modeled after TinyEngine for practicing engine and system design.  

The goal of this framework is to act as an intuitive wrapper for OpenGL, allowing for quick and easy deployment of 2D and 3D visuals. I wanted something easily adaptable to any project I was required to create utilizing user-defined behaviors passed to the base framework.  
