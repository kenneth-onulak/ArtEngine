/******************************************************************************/
/*!
\file   octree.h
\author Kenneth Onulak
\par    email: kenneth.onulakjr\@digipen.edu
\par    DigiPen login: kenneth.onulakjr
\par    Course: CS350
\par    Term: SPRING 2023
\par    Section: A
\par    Assignment #ArtEngine
\date   04/08/2023
\brief
    This file contains the declaration of the octree functions and relevant
    containers.
*/
/******************************************************************************/
#ifndef ARTENGINE_OCTREE_H
#define ARTENGINE_OCTREE_H

#include <vector>
#include <glm/glm.hpp>

struct Model;

struct OctreeNode
{
    OctreeNode *children[8]; // pointers to children nodes
    glm::vec3 center;        // center of this node
    glm::vec3 color;         // color to render this node
    float half_size;         // half width/height/depth (cube)
    int depth;               // depth of the node
};

OctreeNode *BuildOctTree(std::vector<Model *> const &models, glm::vec3 const &center, float half_size, int depth);

// get number of triangles withing a given range given a center and half size
int TriangleCount(std::vector<Model *> const &models, glm::vec3 const &center, float half_size, glm::vec4 const &color);

// compute the center of all models
glm::vec3 Center(std::vector<Model *> const & models);

// compute the longest axis
float Longest(std::vector<Model *> const & models);

#endif // ARTENGINE_OCTREE_H
