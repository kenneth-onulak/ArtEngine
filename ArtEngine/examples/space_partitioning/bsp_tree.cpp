/******************************************************************************/
/*!
\file   bsp_tree.cpp
\author Kenneth Onulak
\par    email: kenneth.onulakjr\@digipen.edu
\par    DigiPen login: kenneth.onulakjr
\par    Course: CS350
\par    Term: SPRING 2023
\par    Section: A
\par    Assignment #ArtEngine
\date   04/08/2023
\brief
    This file contains the implementation of the bsp_tree functions and relevant
    containers.
*/
/******************************************************************************/

//------------------------------------------------------------------------------
// INCLUDE FILES:
//------------------------------------------------------------------------------
#include "../../include/pch.h"
#include "bsp_tree.h"

#include <random>

static float constexpr f_max = std::numeric_limits<float>::max();
static float constexpr f_min = -f_max;

BSPNode *BuildBSPTree(std::vector<triangle> const &polygons, //
                      std::vector<Model *> &models,          //
                      int depth,                             //
                      std::vector<int> const &model_index,   //
                      std::vector<std::vector<size_t>> const &model_indices)
{
    if (polygons.empty())
        return nullptr;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0, 1); // uniform distribution between 0 and 1

    glm::vec4 color(dis(gen), dis(gen), dis(gen), 1);

    size_t polygon_count = polygons.size();

    // stop at a minimum number of polygons or depth
    if (depth <= 0 || polygon_count <= 250)
        return new BSPNode(polygons);

    auto *node = new BSPNode(polygons);

    Plane split_plane = SplittingPlane(polygons);
    std::vector<triangle> front;
    std::vector<triangle> back;
    std::vector<int> front_model_index;
    std::vector<int> back_model_index;
    std::vector<std::vector<size_t>> front_indices;
    std::vector<std::vector<size_t>> back_indices;

    for (int i = 0; i < polygon_count; ++i)
    {
        models[model_index[i]]->color[model_indices[i][0]] = color;
        models[model_index[i]]->color[model_indices[i][1]] = color;
        models[model_index[i]]->color[model_indices[i][2]] = color;

        triangle poly = polygons[i];

        switch (ClassifyPolygonToPlane(poly, split_plane))
        {
        case IN_FRONT_OF_PLANE:
            front.push_back(poly);
            front_model_index.push_back(model_index[i]);
            front_indices.push_back(model_indices[i]);
            break;
        case BEHIND_PLANE:
            back.push_back(poly);
            back_model_index.push_back(model_index[i]);
            back_indices.push_back(model_indices[i]);
            break;
        case STRADDLING_PLANE:
            front.push_back(poly);
            back.push_back(poly);
            front_model_index.push_back(model_index[i]);
            back_model_index.push_back(model_index[i]);
            front_indices.push_back(model_indices[i]);
            back_indices.push_back(model_indices[i]);
            break;
        default:
            // do nothing
            break;
        }
    }

    node->front = BuildBSPTree(front, models, depth - 1, front_model_index, front_indices);
    node->back = BuildBSPTree(back, models, depth - 1, back_model_index, back_indices);
    node->color = color;

    return node;
}

Plane SplittingPlane(std::vector<triangle> const &polygons)
{
    static float constexpr k = 0.8f;

    Plane best_plane = PlaneFromPolygons(polygons[0]);
    float best_score = f_max;

    for (size_t i = 0; i < polygons.size(); ++i)
    {
        int in_front = 0;
        int behind = 0;
        int straddling = 0;

        Plane plane = PlaneFromPolygons(polygons[i]);

        for (size_t j = 0; j < polygons.size(); ++j)
        {
            if (i == j)
                continue;

            switch (ClassifyPolygonToPlane(polygons[j], plane))
            {
            case IN_FRONT_OF_PLANE:
                ++in_front;
                break;
            case BEHIND_PLANE:
                ++behind;
                break;
            case STRADDLING_PLANE:
                ++straddling;
                break;
            default:
                // do nothing
                break;
            }
        }

        float score = k * straddling + (1.0f - k) * glm::abs(in_front - behind);
        if (score < best_score)
        {
            best_score = score;
            best_plane = plane;
        }
    }

    return best_plane;
}

Plane PlaneFromPolygons(triangle const &polygon)
{
    Plane plane;
    plane.normal =
        glm::normalize(glm::cross(polygon.points[1] - polygon.points[0], polygon.points[2] - polygon.points[0]));
    plane.d = glm::dot(plane.normal, polygon.points[0]);
    return plane;
}

int ClassifyPointToPlane(glm::vec3 const &p, Plane const &plane)
{
    static float constexpr epsilon = std::numeric_limits<float>::epsilon();

    float distance = glm::dot(plane.normal, p) - plane.d;

    if (distance > epsilon)
        return POINT_IN_FRONT_OF_PLANE;
    if (distance < -epsilon)
        return POINT_BEHIND_PLANE;
    return POINT_ON_PLANE;
}

int ClassifyPolygonToPlane(triangle const &poly, Plane const &plane)
{
    int in_front = 0;
    int behind = 0;

    int vertices = 3;
    for (int i = 0; i < vertices; ++i)
    {
        glm::vec3 p = poly.points[i];

        switch (ClassifyPointToPlane(p, plane))
        {
        case POINT_IN_FRONT_OF_PLANE:
            ++in_front;
            break;
        case POINT_BEHIND_PLANE:
            ++behind;
            break;
        default:
            // do nothing
            break;
        }
    }

    if (behind && in_front)
        return STRADDLING_PLANE;
    if (in_front)
        return IN_FRONT_OF_PLANE;
    if (behind)
        return BEHIND_PLANE;
    return COPLANAR_WITH_PLANE;
}