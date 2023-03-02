#ifndef ARTENGINE_BOUNDING_VOLUME_HIERARCHY_H
#define ARTENGINE_BOUNDING_VOLUME_HIERARCHY_H

#include <vector>
#include <glm/glm.hpp>

#include "../../include/utility/model.h"
#include "../../include/utility/bounding_volume.h"

namespace bvh
{

struct Node
{
    enum class node_type
    {
        internal,
        leaf
    };

    AABB aabb;          //!< aabb for this node
    Sphere sphere;      //!< sphere bounding volume for this node
    node_type type{};   //!< type of node
    Model *model{};     //!< pointer to the models / bounding volumes that the node represents
    int num_models{};   //!< number of models in this sub-tree
    int depth;          //!< depth in the tree
    glm::vec3 position; //!< position (used for bottom up only)

}; // struct Node

enum class tree
{
    top_down_median_split,
    top_down_k_even_split,
    top_down_median_extents_split
};

char find_largest_axis(std::vector<Model *> const &models);

AABB compute_aabb(std::vector<Model *> const &models, int start, int end);
Sphere compute_bounding_sphere(std::vector<Model *> const &models, int start, int end);

void top_down_bvh(Node **tree, std::vector<Model *> const &models, int start, int end, int depth);
void bottom_up_bvh(Node **tree, std::vector<Model *> const &models);

float get_heuristic_cost(std::vector<Model *> const &models, int start, int split, int end);
int partition_models(std::vector<Model *> const &models, int start, int end);

Sphere recompute_parent_sphere(Sphere &parent, Sphere &left, Sphere &right);

int find_index_closest_to_point(std::vector<Model *> const &models, float point, int start, int end, char axis);
int find_index_with_extents(std::vector<Model *> const &models, float extent, int start, int end, char axis,
                            bool render_sphere);

void find_nodes_to_merge(Node **nodes, int size, int *i, int *j);

AABB bottom_up_compute_aabb(Node *first, Node *second);
Sphere bottom_up_compute_bounding_sphere(Node *first, Node *second);

void bottom_up_depth(Node *tree, int depth);

float nearest_neighbor_cost(Node **nodes, int i, int j);
float combined_volume_cost(Node **nodes, int i, int j);
float relative_increase_cost(Node **nodes, int i, int j);

} // namespace bvh

#endif // ARTENGINE_BOUNDING_VOLUME_HIERARCHY_H
