# ArtEngine Build Recipe
# Author: Kenneth Onulak Jr
# Version 1.0
# Tested on Windows 10

################################################################################
# basic settings
cmake_minimum_required( VERSION 3.20 ) # cmake version
set( PROJECT ArtEngine )               # project name
project( ${PROJECT} )                  # set the project
set( CMAKE_CXX_STANDARD 20 )           # C++ version

################################################################################
# dependencies use vcpkg on windows
#if ( WIN32 )
#  set( VCPKG_ROOT "${LOCAL_ROOT}/dev/vcpkg" )
#  set( CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" )
#  set( VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "" )
#endif ( WIN32 )

################################################################################
################################## START EDIT ##################################
################################################################################
# uncomment the line corresponding to the project you want to build

#set( EXAMPLE_DIR examples/image )    # image
set( EXAMPLE_DIR examples/scene )    # scene

################################################################################
################################### END EDIT ###################################
################################################################################

################################################################################
# GLOB build files
# engine files
file( GLOB_RECURSE ENGINE CONFIG_DEPENDS include/*h include/*.cpp )
# project files
file( GLOB_RECURSE EXAMPLE CONFIG_DEPENDS ${EXAMPLE_DIR}/*.h ${EXAMPLE_DIR}/*.cpp )

################################################################################
# Find dependencies
find_package( GLEW 4.5 REQUIRED )
find_package( glm CONFIG REQUIRED )
find_package( SDL2 CONFIG REQUIRED )
find_package( sdl2-ttf CONFIG REQUIRED )
find_package( sdl2-image CONFIG REQUIRED )
find_package( Freetype REQUIRED )
find_package( Boost REQUIRED COMPONENTS filesystem )
find_package( imgui CONFIG REQUIRED )

################################################################################
# add the executable with all globbed files (project and engine)
add_executable( ${PROJECT}
                ${EXAMPLE}
                ${ENGINE}
                )

################################################################################
# link dependencies
target_link_libraries( ${PROJECT} PRIVATE
                       GLEW::GLEW
                       glm::glm
                       SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_image
                       Freetype::Freetype
                       Boost::boost Boost::filesystem
                       imgui::imgui
                       )

################################################################################
# copy over required files to build
# shader files
add_custom_command( TARGET ${PROJECT} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${EXAMPLE_DIR}/shader/
                    $<TARGET_FILE_DIR:ArtEngine>/shader/
                    )
# object files
add_custom_command( TARGET ${PROJECT} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${EXAMPLE_DIR}/object/
                    $<TARGET_FILE_DIR:ArtEngine>/object/
                    )
# image files
add_custom_command( TARGET ${PROJECT} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${EXAMPLE_DIR}/image/
                    $<TARGET_FILE_DIR:ArtEngine>/image/
                    )