#include "../pch.h"

void AABB::compute()
{
    if (!is_dirty)
        return;

    // get the vertex information
    std::vector<glm::vec3> points;
    points.resize(model->size);
    model->buffers["in_Position"]->retrieve(points);

    static float constexpr f_max = std::numeric_limits<float>::max();
    static float constexpr f_min = -f_max;

    glm::vec3 min_p(f_max);
    glm::vec3 max_p(f_min);

    // compute extreme points
    for (auto const &p : points)
    {
        min_p.x = std::min(min_p.x, p.x);
        min_p.y = std::min(min_p.y, p.y);
        min_p.z = std::min(min_p.z, p.z);

        max_p.x = std::max(max_p.x, p.x);
        max_p.y = std::max(max_p.y, p.y);
        max_p.z = std::max(max_p.z, p.z);
    }

    min = min_p;
    max = max_p;
    center = (max + min) * 0.5f;
    scale = max - center;

    is_dirty = false;
}

static std::array<glm::vec3, 4> constexpr epos8 = {
    glm::vec3{1, 1, 1},  //
    glm::vec3{1, 1, -1}, //
    glm::vec3{1, -1, 1}, //
    glm::vec3{1, -1, -1} //
};

static std::array<glm::vec3, 6> constexpr epos12 = {
    glm::vec3{1, 1, 0},  //
    glm::vec3{1, -1, 0}, //
    glm::vec3{1, 0, 1},  //
    glm::vec3{1, 0, -1}, //
    glm::vec3{0, 1, 1},  //
    glm::vec3{0, 1, -1}  //
};

static std::array<glm::vec3, 12> constexpr epos24 = {
    glm::vec3{0, 1, 2},  //
    glm::vec3{0, 2, 1},  //
    glm::vec3{1, 0, 2},  //
    glm::vec3{2, 0, 1},  //
    glm::vec3{1, 2, 0},  //
    glm::vec3{2, 1, 0},  //
    glm::vec3{0, 1, -2}, //
    glm::vec3{0, 2, -1}, //
    glm::vec3{1, 0, -2}, //
    glm::vec3{2, 0, -1}, //
    glm::vec3{1, -2, 0}, //
    glm::vec3{2, -1, 0}  //
};

void Sphere::compute(sphere_type t)
{
    if (type == t && !is_dirty)
        return;

    // update type
    type = t;

    // get the vertex information
    std::vector<glm::vec3> points;
    points.resize(model->size);
    model->buffers["in_Position"]->retrieve(points);

    switch (type)
    {
    case sphere_type::centroid:
        centroid(points);
        break;
    case sphere_type::ritter:
        ritter(points);
        break;
    case sphere_type::larsson8:
        // fallthrough
    case sphere_type::larsson12:
        // fallthrough
    case sphere_type::larsson24:
        // larsson(points);
        break;
    case sphere_type::pca:
        // pca(points);
        break;
    default:
        std::cout << "Error: Sphere type not recognized." << std::endl;
        break;
    }

    is_dirty = false;
}

void Sphere::enclose(glm::vec3 p)
{
    // compute distance to point (squared)
    glm::vec3 dir = p - center;
    float dist = glm::dot(dir, dir);
    // do nothing if point is in sphere
    if (dist < radius * radius)
        return;
    // point is outside sphere, update it
    glm::vec3 d = glm::normalize(dir);
    float new_radius = (glm::length(dir) + radius) * 0.5f;
    center = center + (new_radius - radius) * d;
    radius = new_radius;
}

std::pair<glm::vec3, glm::vec3> Sphere::extreme_points_along_xyz(const std::vector<glm::vec3> &v)
{
    // find extreme points along principle axes
    int min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
    for (size_t i = 1; i < v.size(); ++i)
    {
        min_x = (v[i].x < v[min_x].x) ? i : min_x;
        min_y = (v[i].y < v[min_y].y) ? i : min_y;
        min_z = (v[i].z < v[min_z].z) ? i : min_z;

        max_x = (v[i].x > v[max_x].x) ? i : max_x;
        max_y = (v[i].y > v[max_y].y) ? i : max_y;
        max_z = (v[i].z > v[max_z].z) ? i : max_z;
    }

    // compute distance of extreme points (squared)
    glm::vec3 d = v[max_x] - v[min_x];
    float const dist_x = glm::dot(d, d);
    d = v[max_y] - v[min_y];
    float const dist_y = glm::dot(d, d);
    d = v[max_z] - v[min_z];
    float const dist_z = glm::dot(d, d);

    // pick the (min, max) pair of most distance points
    int min = min_x;
    int max = max_x;
    if (dist_y > dist_x && dist_y > dist_z)
    {
        min = min_y;
        max = max_y;
    }
    if (dist_z > dist_x && dist_z > dist_y)
    {
        min = min_z;
        max = max_z;
    }
    return {v[min], v[max]};
}

void Sphere::centroid(const std::vector<glm::vec3> &v)
{
    static float constexpr f_max = std::numeric_limits<float>::max();
    static float constexpr f_min = -f_max;

    glm::vec3 min(f_max);
    glm::vec3 max(f_min);

    // compute aabb
    for (auto const &p : v)
    {
        min.x = std::min(min.x, p.x);
        min.y = std::min(min.y, p.y);
        min.z = std::min(min.z, p.z);

        max.x = std::max(max.x, p.x);
        max.y = std::max(max.y, p.y);
        max.z = std::max(max.z, p.z);
    }

    // center of sphere is the center of the aabb
    center = (max + min) * 0.5f;

    // find the furthest point from the center to make the radius
    float dist = f_min;
    for (auto const &p : v)
    {
        glm::vec3 dir = p - center;
        float d = glm::dot(dir, dir);
        dist = std::max(dist, d);
    }
    radius = sqrt(dist);
}

void Sphere::ritter(const std::vector<glm::vec3> &v)
{
    // get most distant points
    std::pair<glm::vec3, glm::vec3> extremes = extreme_points_along_xyz(v);
    // set sphere to encompass most distant points
    center = (extremes.first + extremes.second) * 0.5f;
    radius = glm::distance(extremes.second, center);

    // enclose all points in the sphere
    for (auto const &p : v)
        enclose(p);
}
