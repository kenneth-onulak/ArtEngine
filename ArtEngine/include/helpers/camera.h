/*+*************************************************************************//*!
 \file:      camera.h

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
#ifndef ARTENGINE_CAMERA_H
#define ARTENGINE_CAMERA_H

namespace camera
{

enum class camera_type
{
    orthographic,
    perspective
};

extern float radius;     //!< camera distance to view point
extern float rotation;   //!< camera rotation around y-axis
extern float rotation_y; //!< camera rotation around x/z axis

extern float near;          //!< near clipping plane
extern float far;           //!< far clipping plane
extern float field_of_view; //!< field of view

extern glm::vec3 position; // z

extern glm::vec3 look; // look at vector

extern float zoom_rate; //!< how fast you can zoom
extern float move_rate; //!< how fast you can move
extern float turn_rate; //!< how fast you can turn

extern bool moved; //!< did the camera move

extern camera_type type; //!< type of camera in use

extern glm::mat4 projection;      //!< camera space to clip space
extern glm::mat4 view;            //!< world space to camera space
extern glm::mat4 view_projection; //!< world space to clip space
extern glm::mat4 inverse_view;    //!< camera space to world space

void move(glm::mat4 v);
void shift(glm::mat4 rot);

void update();

void init(float rad = 5.0f, camera_type t = camera_type::perspective);

////////////////////////////////////////////////////////////////////////////////
//// ROTATIONS
////////////////////////////////////////////////////////////////////////////////

void zoom(float value);
void pan(float value);
void tilt(float value);

////////////////////////////////////////////////////////////////////////////////
//// TRANSLATION
////////////////////////////////////////////////////////////////////////////////

void stride(float value);
void strafe(float value);
void rise(float value);

////////////////////////////////////////////////////////////////////////////////
//// CAMERA EVENT HANDLER
////////////////////////////////////////////////////////////////////////////////

extern std::function<bool()> handler;

} // namespace camera

#endif // ARTENGINE_CAMERA_H
