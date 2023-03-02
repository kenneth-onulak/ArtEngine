#include "../../include/pch.h"
#include "bounding_volume_hierarchy.h"

namespace bvh
{

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

AABB compute_aabb(std::vector<Model *> const &models, int start, int end)
{
    glm::vec3 min = models[start]->aabb.min;
    glm::vec3 max = models[start]->aabb.max;

    for (int i = start + 1; i <= end; ++i)
    {
        min.x = std::min(min.x, models[i]->aabb.min.x);
        min.y = std::min(min.x, models[i]->aabb.min.x);
        min.y = std::min(min.y, models[i]->aabb.min.y);

        max.x = std::max(max.x, models[i]->aabb.max.x);
        max.y = std::max(max.y, models[i]->aabb.max.y);
        max.z = std::max(max.z, models[i]->aabb.max.z);
    }

    return AABB(min, max);
}

} // namespace bvh