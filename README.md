# Bounding Volumes

- Kenneth Onulak Jr.
- kenneth.onulakjr@digipen.edu
- CS350S23A Project 2
- Hours Spent - 52

### Installing Dependencies:
#### vcpkg
Follow the instructions at https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160#installation to clone the vcpkg repository.

Make sure to follow the integration instructions at https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=msvc-160#installation on a per-user basis so that include paths are resolved automagically.

The following packages need to be installed to compile.
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

### Build:
NOTE: You must set `-DCMAKE_TOOLCHAIN_FILE` for vcpkg. Such as the following where you just need to change `{PATH TO VCPKG}` to match your local vcpkg directory.
```
-DCMAKE_TOOLCHAIN_FILE={PATH TO VCPKG}/scripts/buildsystems/vcpkg.cmake
```
- Built using C++ 20
- Compiled with MSVC CMake in CLion on Windows

### How to Use:
Automatically loads models from power plant section text files
- Expects the following file structure to automatically load files
- NOTE: Missing ppsection(s) folder(s) from submission to omit obj files
```
- examples
    - bvh
        - object
            - ppsection4 // omitted from submission
            - ppsection5 // omitted from submission
            - ppsection6 // omitted from submission
            - Section4.txt
            - Section5.txt
            - Section6.txt
```

### Controls:
- WASD to move / rotate camera around objects
- Shift / Space to rotate the camera up and down
- Esc to toggle the imgui interface

### Directory File Structure:
```
- ArtEngine
    - examples // project files
        - bvh
            - object
                - ppsection(s)
                - Section#.txt
            - shader
                - default.fs / cs
            - ... // other project files
    - include
        - ... // all engine source files
```

### Implementation
Parts Completed (100%)
- Scene Setup
  - Objects loaded from text file
  - Diffuse colored model
- Bounding Volumes
  - AABB
  - OBB - see note near bottom
  - Bounding Sphere
    - Centroid
    - Ritter's
    - Larsson's
      - EPOC-6
      - EPOC-14
      - EPOC-26
      - EPOC-98
    - PCA
  - Ellipsoid
- Bounding Volume Heirarchy
  - Top-Down construction
    - AABB
    - Bounding Sphere (Ritter's)
  - Bottom-Up construction
    - AABB
    - Bounding Sphere (Ritter's)
- Interactivity
  - Toggle/Change Bounding Volumes
  - Display Bounding Volumes in Wireframe
  - Camera

### About
Engine is modeled after TinyEngine. 

Colours for Tree Depth:
- 0 - Red
- 1 - Orange
- 2 - Yellow
- 3 - Lime
- 4 - Cyan
- 5 - Magenta
- 6 - White

Note about OBB:
- Unfortunately, if the points are not well distributed the box may not be a tight fit. The reason for this is that variations in point sampling density can skew the eigenvectors of the covariance matrix and result in a poor orientation being found. A way to improve this sampling would be to use a covariance matrix that uses the surface area of each triangle instead. 

Bottom-up tree heuristic:
- Nearest neighbor weight will create a tree with more clustered nodes.
- Combined volume weight will create a tree with smaller nodes.
- Relative weight increase will create a tree that have smaller parents compared to children.