# 3D Interpolating Cubic Spline

- Kenneth Onulak Jr.
- kenneth.onulakjr@digipen.edu
- MAT300 Project 8 - 3D version of Project 4
- Hours Spent: 3  

Illustrates how a interpolating cubic spline can be created using standard basis spline functions, truncated power functions and Gauss Elimination to form the cubic spline.  

### Info:
- The `Release` folder contains the executable and necessary dlls.  
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

### Controls:
- WASD to rotate / zoom camera around objects
- Esc to toggle the imgui interface

### How To Use:
Left click inside a plot plane ("XY", "XZ", or "YZ") to place a 3D point.  
Left click and drag a point inside the plot plane to move it.  
NOTE: There can only be 21 control points at one time, adding additional points after 21 will remove from the beginning of the curve to add to the end.  

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
```

### About
Engine is modeled after TinyEngine.