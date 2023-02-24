/*+*************************************************************************//*!
 \file:      camera.cpp

 \summary:   orthographic and perspective camera

 \functions: move\n
             shift\n
             update\n
             init\n
             zoom\n
             pan\n
             tilt\n
             stride\n
             strafe\n
             rise\n
             handler\n

 \origin:    ArtEngine

 Copyright (c) 2023 Kenneth Onulak Jr.
 MIT License
**************************************************************************//*+*/
#include "pch.h"
#include "camera.h"

#include "../ArtEngine.h"

namespace camera
{

float radius = 20.0f;
float rotation = 0.0f;
float rotation_y = 0.0f;

float near = 0.01f;
float far = 10.0f;
float field_of_view = 1.0f;

glm::vec3 position = glm::vec3(cos(glm::radians(rotation_y)) * sin(glm::radians(rotation)),   // x
                               sin(glm::radians(rotation_y)),                                 // y
                               -cos(glm::radians(rotation_y)) * cos(glm::radians(rotation))); // z

glm::vec3 look = glm::vec3(0);

float zoom_rate = 0.5f;
float move_rate = 1.0f;
float turn_rate = 1.5f;

bool moved = true;

camera_type type = camera_type::perspective;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 view_projection;
glm::mat4 inverse_view;

/*F+F***********************************************************************//*!
 \function: move

 \summary:  accessor to set the view matrix and update the view_projection

 \arg:      v - 4x4 matrix representing the new view matrix
************************************************************************//*F-F*/
void move(glm::mat4 v)
{
    view = v;
    view_projection = projection * view;
}

/*F+F***********************************************************************//*!
 \function: shift

 \summary:  accessor to se the the view matrix and update the view_projection

 \arg:      rot - 4x4 rotation matrix to concat with the current view
************************************************************************//*F-F*/
void shift(glm::mat4 rot)
{
    view = rot * view;
    view_projection = projection * view;
}

/*F+F***********************************************************************//*!
 \function: update

 \summary:  update the current camera by recalculating position, view,
            inverse view, and view_projection
************************************************************************//*F-F*/
void update()
{
    auto radians = glm::radians(rotation);
    auto radians_y = glm::radians(rotation_y);
    position = glm::vec3(cos(radians_y) * sin(radians),   // x
                         sin(radians_y),                  // y
                         -cos(radians_y) * cos(radians)); // z

    if (type == camera_type::perspective)
        view = glm::lookAt(look + radius * position, look, glm::vec3(0, 1, 0));
    else if (type == camera_type::orthographic)
        view = glm::lookAt(look + position, look, glm::vec3(0, 1, 0));

    inverse_view = glm::inverse(view);
    view_projection = projection * view;
}

/*F+F***********************************************************************//*!
 \function: init

 \summary:  initialize the camera with specified values

 \arg:      rad - radius distance to view point, defaults to 0.5f
 \arg:      t - type of camera, [orthographic, perspective]
            defaults to perspective
************************************************************************//*F-F*/
void init(float rad, camera_type t)
{
    type = t;
    radius = rad;

    if (type == camera_type::perspective)
    {
        projection = glm::perspective(
            field_of_view, static_cast<float>(Art::view.width()) / static_cast<float>(Art::view.height()), near, far);
        view = glm::lookAt(look + radius * position, look, glm::vec3(0, 1, 0));
    }
    else if (type == camera_type::orthographic)
    {
        float const width = static_cast<float>(Art::view.width()) / radius;
        float const height = static_cast<float>(Art::view.height()) / radius;
        projection = glm::ortho(-width, width, -height, height, near, far);
        view = glm::lookAt(look + position, look, glm::vec3(0, 1, 0));
    }

    inverse_view = glm::inverse(view);
    view_projection = projection * view;
}

/*F+F***********************************************************************//*!
 \function: zoom

 \summary:  accessor to adjust to the camera zoom (distance from view point)

 \arg:      value - value to adjust the zoom by
************************************************************************//*F-F*/
void zoom(float value)
{
    radius += value;
    if (type == camera_type::orthographic)
    {
        float const width = static_cast<float>(Art::view.width()) / radius;
        float const height = static_cast<float>(Art::view.height()) / radius;
        projection = glm::ortho(-width, width, -height, height, near, far);
    }
    update();
    moved = true;
}

/*F+F***********************************************************************//*!
 \function: pan

 \summary:  accessor to adjust the camera pan

 \arg:      value - value to adjust the pan by
************************************************************************//*F-F*/
void pan(float value)
{
    float x = rotation + value + 360.0f;
    rotation = x - static_cast<float>(static_cast<int>(x / 360.0f)) * 360.0f;
    update();
    moved = true;
}

/*F+F***********************************************************************//*!
 \function: tilt

 \summary:  accessor to adjust the camera tilt

 \arg:      value - value to adjust the tilt by
************************************************************************//*F-F*/
void tilt(float value)
{
    rotation_y += value;
    if (rotation_y >= 90.0f)
        rotation_y = 90.0f - value;
    if (rotation_y <= -90.0f)
        rotation_y = -90.0f - value;
    update();
    moved = true;
}

/*F+F***********************************************************************//*!
 \function: stride

 \summary:  accessor to adjust the camera stride

 \arg:      value - value to adjust the stride by
************************************************************************//*F-F*/
void stride(float value)
{
    auto radians = glm::radians(rotation);
    look.x += value * sin(radians);
    look.z -= value * cos(radians);
    update();
    moved = true;
}

/*F+F***********************************************************************//*!
 \function: strafe

 \summary:  accessor to adjust the camera strafe

 \arg:      value - value to adjust the strafe by
************************************************************************//*F-F*/
void strafe(float value)
{
    auto radians = glm::radians(rotation);
    look.x += value * cos(radians);
    look.z += value * sin(radians);
    update();
    moved = true;
}

/*F+F***********************************************************************//*!
 \function: rise

 \summary:  accessor to adjust the camera rise

 \arg:      value - value to adjust the rise by
************************************************************************//*F-F*/
void rise(float value)
{
    look.y += value;
    update();
    moved = true;
}

/*F+F***********************************************************************//*!
 \function: handler

 \summary:  handle event input to move the camera and resize the window

 \return:   True, if the camera was moved
 \return:   False, otherwise
************************************************************************//*F-F*/
std::function<bool()> handler = []() {
    moved = false; //

    // scrolling to zoom / pan
    if (Art::event.scroll().positive_y) // scroll up
        zoom(zoom_rate);
    if (Art::event.scroll().negative_y) // scroll down
        zoom(-zoom_rate);
    if (Art::event.scroll().positive_x) // scroll right
        pan(turn_rate);
    if (Art::event.scroll().negative_x) // scroll left
        pan(-turn_rate);

    // arrow keys to tilt / pan
    if (Art::event.key_down(SDLK_UP))
        tilt(turn_rate);
    if (Art::event.key_down(SDLK_DOWN))
        tilt(-turn_rate);
    if (Art::event.key_down(SDLK_LEFT))
        pan(turn_rate);
    if (Art::event.key_down(SDLK_RIGHT))
        pan(-turn_rate);

    // WASD keys to stride / strafe
    if (Art::event.key_down(SDLK_w))
        stride(-move_rate);
    if (Art::event.key_down(SDLK_a))
        strafe(move_rate);
    if (Art::event.key_down(SDLK_s))
        stride(move_rate);
    if (Art::event.key_down(SDLK_d))
        strafe(-move_rate);

    // shift / space to rise / fall
    if (Art::event.key_down(SDLK_LSHIFT))
        rise(move_rate);
    if (Art::event.key_down(SDLK_SPACE))
        rise(-move_rate);

    // window resizing
    if (Art::event.resize_window())
    {
        if (type == camera_type::perspective)
            projection = glm::perspective(
                field_of_view, static_cast<float>(Art::view.width()) / static_cast<float>(Art::view.height()), near,
                far);
        else if (type == camera_type::orthographic)
        {
            float const width = static_cast<float>(Art::view.width()) / radius;
            float const height = static_cast<float>(Art::view.height()) / radius;
            projection = glm::ortho(-width, width, -height, height, near, far);
        }
        view_projection = projection * view;
        moved = true;
        update();
    }

    return moved;
};

} // namespace camera