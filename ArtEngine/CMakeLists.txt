cmake_minimum_required( VERSION 3.20 )

set( PROJECT ArtEngine )

project( ${PROJECT} )

set( CMAKE_CXX_STANDARD 20 )

include_directories( ./include )

file( GLOB_RECURSE EXAMPLE CONFIG_DEPENDS examples/voronoi*h examples/voronoi/*.cpp )

# Find dependencies from vcpkg
find_package( GLEW )
find_package( glm CONFIG REQUIRED )
find_package( SDL2 CONFIG REQUIRED )
find_package( sdl2-ttf CONFIG REQUIRED )
find_package( sdl2-image CONFIG REQUIRED )
find_package( Freetype REQUIRED )
find_package( Boost REQUIRED COMPONENTS filesystem )
find_package( imgui CONFIG REQUIRED )

add_executable( ${PROJECT}
                examples/voronoi/main.cpp
                examples/voronoi/FastNoiseLite.h
                examples/voronoi/model.h
                ### engine files
                include/pch.h
                ### main files
                include/ArtEngine.h include/ArtEngine.cpp
                include/view.h include/view.cpp
                include/event.h include/event.cpp
                ### helpers
                include/helpers/camera.h include/helpers/camera.cpp
                include/helpers/color.h include/helpers/color.cpp
                include/helpers/object.h include/helpers/object.cpp
                include/helpers/image.h include/helpers/image.cpp
                include/helpers/log.h include/helpers/log.cpp
                include/helpers/parse.h include/helpers/parse.cpp
                include/helpers/timer.h
                ### utility
                include/utility/buffer.h include/utility/buffer.cpp
                include/utility/model.h include/utility/model.cpp
                include/utility/instance.h include/utility/instance.cpp
                include/utility/shader.h include/utility/shader.cpp
                include/utility/texture.h include/utility/texture.cpp
                include/utility/target.h include/utility/target.cpp
                ### imgui
                include/imgui/imgui_impl_sdl.h include/imgui/imgui_impl_sdl.cpp
                include/imgui/imgui_impl_opengl3.h include/imgui/imgui_impl_opengl3.cpp
                )

# link dependencies from vcpkg
target_link_libraries( ${PROJECT} PUBLIC
                       Freetype::Freetype
                       GLEW::GLEW
                       glm::glm
                       SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_image
                       Boost::boost Boost::filesystem
                       imgui::imgui )

target_include_directories( ${PROJECT} PRIVATE examples/shader/ )

add_custom_command( TARGET ${PROJECT} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples/voronoi/shader/
                    $<TARGET_FILE_DIR:ArtEngine>/shader/
                    )

add_custom_command( TARGET ${PROJECT} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/voronoi/starry_night.png
                    $<TARGET_FILE_DIR:ArtEngine>/
                    )

