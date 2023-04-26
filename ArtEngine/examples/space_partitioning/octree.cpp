/******************************************************************************/
/*!
\file   octree.cpp
\author Kenneth Onulak
\par    email: kenneth.onulakjr\@digipen.edu
\par    DigiPen login: kenneth.onulakjr
\par    Course: CS350
\par    Term: SPRING 2023
\par    Section: A
\par    Assignment #ArtEngine
\date   04/08/2023
\brief
    This file contains the implementation of the octree functions and relevant
    containers.
*/
/******************************************************************************/

//------------------------------------------------------------------------------
// INCLUDE FILES:
//------------------------------------------------------------------------------
#include "../../include/pch.h"
#include "octree.h"

static float constexpr f_max = std::numeric_limits<float>::max();
static float constexpr f_min = -f_max;

OctreeNode *BuildOctTree(std::vector<Model *> const &models, glm::vec3 const &center, float half_size, int depth)
{
    // color options
    static std::array<glm::vec3, 7> const colors = {color::red,  color::orange,  color::yellow, color::lime,
                                                    color::cyan, color::magenta, color::white};
    glm::vec3 color = colors[depth % 7];

    int triangles = TriangleCount(models, center, half_size, {color, 1});
    if (triangles <= 10 || depth < 0)
        return nullptr;

    // construct root node
    OctreeNode *node = new OctreeNode;
    node->center = center;
    node->half_size = half_size;
    node->color = color;
    node->depth = depth; // reverse depth [7,0]

    // recursively construct child nodes
    glm::vec3 offset;
    float step = half_size * 0.5f;
    for (int i = 0; i < 8; ++i)
    {
        offset.x = i & 1 ? step : -step;
        offset.y = i & 2 ? step : -step;
        offset.z = i & 4 ? step : -step;

        node->children[i] = BuildOctTree(models, center + offset, step, depth - 1);
    }

    return node;
}

bool inside(glm::vec3 const &a, glm::vec3 const &b, glm::vec3 const &c)
{
    return a.x <= b.x && a.y <= b.y && a.z <= b.z && a.x >= c.x && a.y >= c.y && a.z >= c.z;
}

// get number of triangles withing a given range given a center and half size
int TriangleCount(std::vector<Model *> const &models, glm::vec3 const &center, float const half_size, glm::vec4 const & color)
{
    int count = 0;
    glm::vec3 p0(0), p1(0), p2(0);

    for (auto const & model : models)
    {
        // get the vertex information
        std::vector<glm::vec3> points;
        points.resize(model->size);
        model->buffers["in_Position"]->retrieve(points);

        for (size_t i = 0; i < points.size(); i += 3)
        {
            bool in0 = false, in1 = false, in2 = false;

            p0 = points[i];
            p1 = points[i + 1];
            p2 = points[i + 2];

            glm::vec3 right = center + half_size;
            glm::vec3 left = center - half_size;
            if (inside(p0, right, left))
                in0 = true;
            if (inside(p1, right, left))
                in1 = true;
            if (inside(p2, right, left))
                in2 = true;

            if (in0 && in1 && in2)
                ++count;
        }
    }

    return count;
}

// compute the center of all models
glm::vec3 Center(std::vector<Model *> const &models)
{
    glm::vec3 min(f_max);
    glm::vec3 max(f_min);

    for (auto const &model : models)
    {
        min.x = std::min(model->aabb.min.x, min.x);
        min.y = std::min(model->aabb.min.y, min.y);
        min.z = std::min(model->aabb.min.z, min.z);

        max.x = std::max(model->aabb.max.x, max.x);
        max.y = std::max(model->aabb.max.y, max.y);
        max.z = std::max(model->aabb.max.z, max.z);
    }

    return (max + min) * 0.5f;
}

// compute the longest axis
float Longest(std::vector<Model *> const &models)
{
    glm::vec3 min(f_max);
    glm::vec3 max(f_min);
    float scalar = 0.5f;

    for (auto const &model : models)
    {
        min.x = std::min(model->aabb.min.x, min.x);
        min.y = std::min(model->aabb.min.y, min.y);
        min.z = std::min(model->aabb.min.z, min.z);

        max.x = std::max(model->aabb.max.x, max.x);
        max.y = std::max(model->aabb.max.y, max.y);
        max.z = std::max(model->aabb.max.z, max.z);
    }

    glm::vec3 dist = glm::abs(max - min);

    if (dist.x > dist.y && dist.x > dist.z)
        return dist.x * scalar;
    if (dist.y > dist.x && dist.y > dist.z)
        return dist.x * scalar;
    return dist.z * scalar;
}
