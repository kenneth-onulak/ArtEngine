/******************************************************************************/
/*!
\file   bsp_tree.h
\author Kenneth Onulak
\par    email: kenneth.onulakjr\@digipen.edu
\par    DigiPen login: kenneth.onulakjr
\par    Course: CS350
\par    Term: SPRING 2023
\par    Section: A
\par    Assignment #ArtEngine
\date   04/08/2023
\brief
    This file contains the declaration of the bsp_tree functions and relevant
    containers..
*/
/******************************************************************************/
#ifndef ARTENGINE_BSP_TREE_H
#define ARTENGINE_BSP_TREE_H

#include <array>
#include <vector>
#include <glm/glm.hpp>

struct Model;

struct triangle
{
    std::array<glm::vec3, 3> points;
    glm::vec3 normal;
};

struct BSPNode
{
    BSPNode() = default;

    explicit BSPNode(std::vector<triangle> const &v)
        : polygons(v)
    {
    }

    std::vector<triangle> polygons;
    BSPNode *front = nullptr;
    BSPNode *back = nullptr;
    glm::vec3 color = {0, 0, 0};
};

struct Plane
{
    glm::vec3 normal = {0, 0, 0}; // Dot product between the normal and and point on the plane = d
    float d = 0;                  // d = glm::dot(normal, point)
};

enum Point_
{
    POINT_IN_FRONT_OF_PLANE,
    POINT_BEHIND_PLANE,
    POINT_ON_PLANE
};

enum Plane_
{
    COPLANAR_WITH_PLANE,
    IN_FRONT_OF_PLANE,
    BEHIND_PLANE,
    STRADDLING_PLANE
};

BSPNode *BuildBSPTree(std::vector<triangle> const &polygons, //
                      std::vector<Model *> &models,          //
                      int depth,                             //
                      std::vector<int> const &model_index,   //
                      std::vector<std::vector<size_t>> const &model_indices);

Plane SplittingPlane(std::vector<triangle> const &polygons);

Plane PlaneFromPolygons(triangle const &poly);

int ClassifyPointToPlane(glm::vec3 const &p, Plane const &plane);

int ClassifyPolygonToPlane(triangle const &polygon, Plane const &plane);

#endif // ARTENGINE_BSP_TREE_H
