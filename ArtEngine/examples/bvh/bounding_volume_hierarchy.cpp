#include "../../include/pch.h"
#include "bounding_volume_hierarchy.h"

#include "helpers.h"

namespace bvh
{

Node **tree = nullptr;

static float constexpr f_max = std::numeric_limits<float>::max();
static float constexpr f_min = -f_max;

bool compare_x(Model *a, Model *b)
{
    return a->aabb.center.x < b->aabb.center.x;
}

bool compare_y(Model *a, Model *b)
{
    return a->aabb.center.y < b->aabb.center.y;
}

bool compare_z(Model *a, Model *b)
{
    return a->aabb.center.z < b->aabb.center.z;
}

char find_largest_axis(std::vector<Model *> const &models)
{
    glm::vec3 min(f_max);
    glm::vec3 max(f_min);

    for (size_t i = 0; i < models.size(); ++i)
    {
        min.x = std::min(min.x, models[i]->aabb.min.x);
        min.y = std::min(min.y, models[i]->aabb.min.y);
        min.z = std::min(min.z, models[i]->aabb.min.z);

        max.x = std::max(max.x, models[i]->aabb.max.x);
        max.y = std::max(max.y, models[i]->aabb.max.y);
        max.z = std::max(max.z, models[i]->aabb.max.z);
    }

    float dist_x = abs(max.x - min.x);
    float dist_y = abs(max.y - min.y);
    float dist_z = abs(max.z - min.z);

    if (dist_x > dist_y && dist_x > dist_z)
        return 'x';
    if (dist_y > dist_x && dist_y > dist_z)
        return 'y';
    return 'z';
}

int find_index_closest_to_point(std::vector<Model *> const &models, float point, int start, int end, char axis)
{
    float min = f_max;
    int index = start;

    for (int i = start; i <= end; ++i)
    {
        float distance = 0;
        if (axis == 'x')
            distance = abs(models[i]->aabb.center.x - point);
        if (axis == 'y')
            distance = abs(models[i]->aabb.center.y - point);
        if (axis == 'z')
            distance = abs(models[i]->aabb.center.z - point);

        if (distance < min)
        {
            min = distance;
            index = i;
        }
    }

    return index;
}
int find_index_with_extents(std::vector<Model *> const &models, float extent, int start, int end, char axis)
{
    for (int i = start; i <= end; ++i)
    {
        float distance = 0;
        if (use_sphere)
        {
            Sphere const &s = models[i]->sphere;
            if (axis == 'x')
                distance = std::min(abs(s.center.x - s.radius - extent), //
                                    abs(s.center.x + s.radius - extent));
            if (axis == 'y')
                distance = std::min(abs(s.center.y - s.radius - extent), //
                                    abs(s.center.y + s.radius - extent));
            if (axis == 'z')
                distance = std::min(abs(s.center.z - s.radius - extent), //
                                    abs(s.center.z + s.radius - extent));
        }

        if (use_aabb)
        {
            AABB const &b = models[i]->aabb;
            if (axis == 'x')
                distance = std::min(abs(b.min.x - extent), abs(b.max.x - extent));
            if (axis == 'y')
                distance = std::min(abs(b.min.y - extent), abs(b.max.y - extent));
            if (axis == 'z')
                distance = std::min(abs(b.min.z - extent), abs(b.max.z - extent));
        }

        // return first index that satisfies this condition
        if (distance == 0.f)
            return i;
    }

    return -1; // error
}

AABB compute_aabb(std::vector<Model *> const &models, int start, int end)
{
    glm::vec3 min = models[start]->aabb.min;
    glm::vec3 max = models[start]->aabb.max;

    for (int i = start + 1; i <= end; ++i)
    {
        min.x = std::min(min.x, models[i]->aabb.min.x);
        min.y = std::min(min.y, models[i]->aabb.min.y);
        min.z = std::min(min.z, models[i]->aabb.min.z);

        max.x = std::max(max.x, models[i]->aabb.max.x);
        max.y = std::max(max.y, models[i]->aabb.max.y);
        max.z = std::max(max.z, models[i]->aabb.max.z);
    }

    return {min, max};
}

Sphere compute_bounding_sphere(std::vector<Model *> const &models, int start, int end)
{
    // get the starting position of the bounding sphere
    Sphere sphere(models[start]->sphere.center, models[start]->sphere.radius);
    // grow the sphere to enclose multiple objects
    for (int i = start + 1; i <= end; ++i)
    {
        Sphere &s = models[i]->sphere;
        glm::vec3 dir = glm::normalize(s.center - sphere.center);
        glm::vec3 p = s.center + s.radius * dir;
        sphere.enclose(p);
    }

    return sphere;
}

Sphere recompute_parent_sphere(Sphere &parent, Sphere &left, Sphere &right)
{
    Sphere sphere(parent.center, parent.radius);
    // grow to include left child
    glm::vec3 dir = glm::normalize(left.center - sphere.center);
    glm::vec3 p = left.center + left.radius * dir;
    sphere.enclose(p);
    // grow to include right child
    dir = glm::normalize(right.center - sphere.center);
    p = right.center + right.radius * dir;
    sphere.enclose(p);

    return sphere;
}

void top_down_bvh(Node **tree, std::vector<Model *> &models, int start, int end, int depth)
{
    static int constexpr MIN_OBJECTS_PER_LEAF = 1;

    int num_models = end - start + 1;
    Node *node = new Node;
    *tree = node;

    if (use_aabb)
        node->aabb = compute_aabb(models, start, end);
    else
        node->sphere = compute_bounding_sphere(models, start, end);

    if (num_models <= MIN_OBJECTS_PER_LEAF)
    {
        node->type = Node::node_type::leaf;
        node->num_models = num_models;
        node->model = models[start];
        node->depth = depth;
    }
    else
    {
        node->type = Node::node_type::internal;
        node->depth = depth;
        // partition models
        int k = partition_models(models, start, end);
        // recursively construct left and right subtree
        top_down_bvh(&(node->left), models, start, k, depth + 1);
        top_down_bvh(&(node->right), models, k + 1, end, depth + 1);
    }

    // recompute parents when using spheres
    if (use_sphere && node->left && node->right)
        node->sphere = recompute_parent_sphere(node->sphere, node->left->sphere, node->right->sphere);
}

float get_heuristic_cost(std::vector<Model *> const &models, int start, int split, int end)
{
    // base case with no children
    if (end == 1)
    {
        Sphere left = compute_bounding_sphere(models, start, split);
        return left.surface_area();
    }

    if (use_sphere)
    {
        Sphere left = compute_bounding_sphere(models, start, split);
        Sphere right = compute_bounding_sphere(models, split + 1, end);
        return split * left.surface_area() + (end - split - 1) * right.surface_area();
    }

    if (use_aabb)
    {
        AABB left = compute_aabb(models, start, split);
        AABB right = compute_aabb(models, split + 1, end);
        return split * left.surface_area() + (end - split - 1) * right.surface_area();
    }

    Sphere left = compute_bounding_sphere(models, start, split);
    return left.surface_area();
}

int partition_models(std::vector<Model *> &models, int start, int end)
{
    int num_models = end - start;
    float cost_x, cost_y, cost_z;

    if (tree_type == static_cast<int>(tree::top_down_median_split))
    {
        // x plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_x);
        cost_x = get_heuristic_cost(models, start, start + num_models / 2, num_models);
        // y plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_y);
        cost_y = get_heuristic_cost(models, start, start + num_models / 2, num_models);
        // z plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_z);
        cost_z = get_heuristic_cost(models, start, start + num_models / 2, num_models);

        // resort based on smallest cost
        // assumes z is currently the smallest cost so only check x and y
        if (cost_x < cost_y && cost_x < cost_z)
            std::sort(models.begin() + start, models.begin() + end + 1, &compare_x);
        else if (cost_y < cost_x && cost_y < cost_z)
            std::sort(models.begin() + start, models.begin() + end + 1, &compare_y);

        return start + num_models / 2;
    }

    if (tree_type == static_cast<int>(tree::top_down_k_even_split))
    {
        static float constexpr k = 10.0f;

        int x, y, z; // index variables
        // test which axis to use for the split based on smallest cost
        // x plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_x);
        float range = abs(models[start]->aabb.center.x - models[end]->aabb.center.x);
        float split = range / k;
        float split_x = models[start]->aabb.center.x + split * k * 0.5f;
        x = find_index_closest_to_point(models, split_x, start, end, 'x');
        cost_x = get_heuristic_cost(models, start, x, num_models);
        // y plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_y);
        range = abs(models[start]->aabb.center.y - models[end]->aabb.center.y);
        split = range / k;
        float split_y = models[start]->aabb.center.y + split * k * 0.5f;
        y = find_index_closest_to_point(models, split_y, start, end, 'y');
        cost_y = get_heuristic_cost(models, start, y, num_models);
        // z plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_z);
        range = abs(models[start]->aabb.center.z - models[end]->aabb.center.z);
        split = range / k;
        float split_z = models[start]->aabb.center.z + split * k * 0.5f;
        z = find_index_closest_to_point(models, split_z, start, end, 'z');
        cost_z = get_heuristic_cost(models, start, z, num_models);

        // resort based on smallest cost
        // assumes z is currently the smallest cost so only check x and y
        if (cost_x < cost_y && cost_x < cost_z)
        {
            std::sort(models.begin() + start, models.begin() + end + 1, &compare_x);
            return x;
        }
        else if (cost_y < cost_x && cost_y < cost_z)
        {
            std::sort(models.begin() + start, models.begin() + end + 1, &compare_y);
            return y;
        }
        return z;
    }

    if (tree_type == static_cast<int>(tree::top_down_median_extents_split))
    {
        // check model count
        if (end - start <= 1)
            return start;

        int x, y, z; // index variables
        std::vector<float> extents;
        // x plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_x);
        for (int i = start; i <= end; ++i)
        {
            std::pair<float, float> extent;
            if (use_sphere)
                extent = models[i]->sphere.get_extents("x");
            if (use_aabb)
                extent = models[i]->aabb.get_extents("x");

            extents.emplace_back(extent.first);
            extents.emplace_back(extent.second);
        }
        x = find_index_with_extents(models, extents[(extents.size() - 1) / 2], start, end, 'x');
        cost_x = get_heuristic_cost(models, start, x, num_models);
        extents.clear();
        // y plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_y);
        for (int i = start; i <= end; ++i)
        {
            std::pair<float, float> extent;
            if (use_sphere)
                extent = models[i]->sphere.get_extents("y");
            if (use_aabb)
                extent = models[i]->aabb.get_extents("y");

            extents.emplace_back(extent.first);
            extents.emplace_back(extent.second);
        }
        y = find_index_with_extents(models, extents[(extents.size() - 1) / 2], start, end, 'y');
        cost_y = get_heuristic_cost(models, start, y, num_models);
        extents.clear();
        // z plane
        std::sort(models.begin() + start, models.begin() + end + 1, &compare_z);
        for (int i = start; i <= end; ++i)
        {
            std::pair<float, float> extent;
            if (use_sphere)
                extent = models[i]->sphere.get_extents("z");
            if (use_aabb)
                extent = models[i]->aabb.get_extents("z");

            extents.emplace_back(extent.first);
            extents.emplace_back(extent.second);
        }
        z = find_index_with_extents(models, extents[(extents.size() - 1) / 2], start, end, 'z');
        cost_z = get_heuristic_cost(models, start, z, num_models);

        // resort based on smallest cost
        // assumes z is currently the smallest cost so only check x and y
        if (cost_x < cost_y && cost_x < cost_z)
        {
            std::sort(models.begin() + start, models.begin() + end + 1, &compare_x);
            return x;
        }
        else if (cost_y < cost_x && cost_y < cost_z)
        {
            std::sort(models.begin() + start, models.begin() + end + 1, &compare_y);
            return y;
        }
        return z;
    }

    return -1;
}

void bottom_up_bvh(Node **tree, std::vector<Model *> const &models)
{
    int num_models = models.size();
    Node **temp = new Node *[num_models];

    // form leaf nodes
    for (int i = 0; i < num_models; ++i)
    {
        temp[i] = new Node;
        temp[i]->type = Node::node_type::leaf;
        temp[i]->model = models[i];
        temp[i]->position = models[i]->aabb.center;
        temp[i]->aabb = models[i]->aabb;
        temp[i]->sphere = models[i]->sphere;
    }

    int inv_depth = 0;
    // merge pairs until a single root node remains
    int i, j;
    while (num_models > 1)
    {
        // find indices of the two "nearest" nodes
        find_nodes_to_merge(temp, num_models, &i, &j);
        // group nodes
        Node *pair = new Node;
        pair->type = Node::node_type::internal;
        pair->left = temp[i];
        pair->right = temp[j];
        pair->depth = ++inv_depth;

        // compute bounding volume
        if (use_aabb)
        {
            pair->aabb = bottom_up_compute_aabb(temp[i], temp[j]);
            pair->position = (pair->aabb.max + pair->aabb.min) * 0.5f;
        }
        if (use_sphere)
        {
            pair->sphere = bottom_up_compute_bounding_sphere(temp[i], temp[j]);
            pair->position = (pair->sphere.center);
        }

        // remove the two nodes for the set and add in new pair
        int min = i;
        int max = j;
        if (i > j)
        {
            min = j;
            max = i;
        }
        temp[min] = pair;
        temp[max] = temp[num_models - 1];
        --num_models;
    }

    // cleanup
    Node *root = temp[0];
    if (temp)
        delete[] temp;
    *tree = root;
}

void find_nodes_to_merge(Node **nodes, int size, int *_i, int *_j)
{
    float min = f_max;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // only compare with every other node and not self
            if (i == j)
                continue;

            float cost = nearest_neighbor_cost(nodes, i, j);
            float combined_cost = combined_volume_cost(nodes, i, j);
            float relative_increase = relative_increase_cost(nodes, i, j);
            float total = neighbor_weight * cost + combined_weight * combined_cost + volume_weight * relative_increase;

            if (total < min)
            {
                min = total;
                *_i = i;
                *_j = j;
            }
        }
    }
}

AABB bottom_up_compute_aabb(Node *first, Node *second)
{
    glm::vec3 min, max;

    min.x = std::min(first->aabb.min.x, second->aabb.min.x);
    min.y = std::min(first->aabb.min.y, second->aabb.min.y);
    min.z = std::min(first->aabb.min.z, second->aabb.min.z);

    max.x = std::max(first->aabb.max.x, second->aabb.max.x);
    max.y = std::max(first->aabb.max.y, second->aabb.max.y);
    max.z = std::max(first->aabb.max.z, second->aabb.max.z);

    return {min, max};
}

Sphere bottom_up_compute_bounding_sphere(Node *first, Node *second)
{
    Sphere s(first->sphere.center, first->sphere.radius);
    glm::vec3 dir = glm::normalize(second->sphere.center - s.center);
    glm::vec3 p = second->sphere.center + second->sphere.radius * dir;
    s.enclose(p);
    return s;
}

void bottom_up_depth(Node *tree, int depth)
{
    if (!tree)
        return;
    Node *node = tree;
    node->depth = depth;
    bottom_up_depth(node->left, depth + 1);
    bottom_up_depth(node->right, depth + 1);
}

float nearest_neighbor_cost(Node **nodes, int i, int j)
{
    return glm::distance(nodes[i]->position, nodes[j]->position);
}

float combined_volume_cost(Node **nodes, int i, int j)
{
    if (use_sphere)
    {
        Sphere sphere = bottom_up_compute_bounding_sphere(nodes[i], nodes[j]);
        return sphere.surface_area();
    }
    AABB aabb = bottom_up_compute_aabb(nodes[i], nodes[j]);
    return aabb.surface_area();
}

float relative_increase_cost(Node **nodes, int i, int j)
{
    if (use_sphere)
    {
        Sphere sphere = bottom_up_compute_bounding_sphere(nodes[i], nodes[j]);
        return sphere.surface_area() / (nodes[i]->sphere.surface_area() + nodes[j]->sphere.surface_area());
    }
    AABB aabb = bottom_up_compute_aabb(nodes[i], nodes[j]);
    return aabb.surface_area() / (nodes[i]->aabb.surface_area() + nodes[j]->aabb.surface_area());
}

void clear_tree(Node *node)
{
    if (!node)
        return;
    clear_tree(node->left);
    clear_tree(node->right);
    delete node;
    node = nullptr;
}
} // namespace bvh