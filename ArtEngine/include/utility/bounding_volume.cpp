#include "../pch.h"

static float constexpr f_max = std::numeric_limits<float>::max();
static float constexpr f_min = -f_max;

void AABB::compute()
{
    if (!is_dirty)
        return;

    // get the vertex information
    std::vector<glm::vec3> points;
    points.resize(model->size);
    model->buffers["in_Position"]->retrieve(points);

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

// type 0 0 1, #op (p * n) 0, normals 3
static std::array<glm::vec3, 3> constexpr epos6 = {
    glm::vec3{1, 0, 0}, //
    glm::vec3{0, 1, 0}, //
    glm::vec3{0, 0, 1}  //
};

// type 1 1 1, #op (p * n) 2, normals 4
static std::array<glm::vec3, 4> constexpr epos8 = {
    glm::vec3{1, 1, 1},  //
    glm::vec3{1, 1, -1}, //
    glm::vec3{1, -1, 1}, //
    glm::vec3{1, -1, -1} //
};

// type 0 1 1, #op (p * n) 1, normals 6
static std::array<glm::vec3, 6> constexpr epos12 = {
    glm::vec3{1, 1, 0},  //
    glm::vec3{1, -1, 0}, //
    glm::vec3{1, 0, 1},  //
    glm::vec3{1, 0, -1}, //
    glm::vec3{0, 1, 1},  //
    glm::vec3{0, 1, -1}  //
};

// type 0 1 2, #op (p * n) 2, normals 12
static std::array<glm::vec3, 12> constexpr epos24_1 = {
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

// type 1 1 2, #op (p * n) 3, normals 12
static std::array<glm::vec3, 12> constexpr epos24_2 = {
    glm::vec3{1, 1, 2},   //
    glm::vec3{2, 1, 1},   //
    glm::vec3{1, 2, 1},   //
    glm::vec3{1, -1, 2},  //
    glm::vec3{1, 1, -2},  //
    glm::vec3{1, -1, -2}, //
    glm::vec3{2, -1, 1},  //
    glm::vec3{2, 1, -1},  //
    glm::vec3{2, -1, -1}, //
    glm::vec3{1, -2, 1},  //
    glm::vec3{1, 2, -1},  //
    glm::vec3{1, -2, -1}  //
};

// type 1 2 2, #op (p * n) 4, normals 12
static std::array<glm::vec3, 12> constexpr epos24_3 = {
    glm::vec3{2, 2, 1},   //
    glm::vec3{1, 2, 2},   //
    glm::vec3{2, 1, 2},   //
    glm::vec3{2, -2, 1},  //
    glm::vec3{2, 2, -1},  //
    glm::vec3{2, -2, -1}, //
    glm::vec3{1, -2, 2},  //
    glm::vec3{1, 2, -2},  //
    glm::vec3{1, -2, -2}, //
    glm::vec3{2, -1, 2},  //
    glm::vec3{2, 1, -2},  //
    glm::vec3{2, -1, -2}  //
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
    default:
        std::cout << "Error: Sphere type not recognized, using centroid method." << std::endl;
        // fallthrough
    case sphere_type::centroid:
        centroid(points);
        break;
    case sphere_type::ritter:
        ritter(points);
        break;
    case sphere_type::larsson6:
        // fallthrough
    case sphere_type::larsson14:
        // fallthrough
    case sphere_type::larsson26:
        // fallthrough
    case sphere_type::larsson98:
        larsson(points);
        break;
    case sphere_type::pca:
        pca(points);
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

std::pair<glm::vec3, glm::vec3> Sphere::extreme_points_along_direction(glm::vec3 d, const std::vector<glm::vec3> &v)
{
    float min_dist = f_max;
    float max_dist = f_min;

    glm::vec3 min, max;
    for (auto const &p : v)
    {
        float dist = glm::dot(d, p);
        if (min_dist > dist)
        {
            min_dist = dist;
            min = p;
        }
        if (max_dist <= dist)
        {
            max_dist = dist;
            max = p;
        }
    }
    return {min, max};
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

glm::mat3 Sphere::covariance_matrix(const std::vector<glm::vec3> &v)
{
    // compute the average
    float const scalar = 1.0f / static_cast<float>(v.size());
    glm::vec3 u(0);
    for (auto const &p : v)
        u += p;
    u *= scalar;

    // compute the covariance matrix
    // C_ij = 1/N (E) k=1->N (P_k.i u.i)(P_k.j u.j)
    // for each index add the following
    // x*x x*y x*z
    // y*x y*y y*z
    // z*x z*y z*z
    glm::mat3 covariance(0);
    for (auto const &point : v)
    {
        glm::vec3 p = point - u;
        // top row
        covariance[0][0] += p.x * p.x;
        covariance[1][0] += p.x * p.y;
        covariance[2][0] += p.x * p.z;
        // middle row
        covariance[1][1] += p.y * p.y;
        covariance[2][1] += p.y * p.z;
        // bottom row
        covariance[2][2] += p.z * p.z;
    }
    covariance *= scalar;

    // matrix is mirrored across the diagonal
    covariance[0][1] = covariance[1][0];
    covariance[0][2] = covariance[2][0];
    covariance[1][2] = covariance[2][1];

    return covariance;
}

void Sphere::centroid(const std::vector<glm::vec3> &v)
{
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

void Sphere::larsson(const std::vector<glm::vec3> &v)
{
    // choose a set of k points from all points
    std::vector<glm::vec3> k_points;
    for (size_t i = 0; i < v.size(); i += 3)
        k_points.push_back(v[i]);

    // compute extreme points (min, max) for each epos
    std::vector<std::pair<glm::vec3, glm::vec3>> extremes;
    switch (type)
    {
    default:
        std::cout << "Error: EPOS value not recognized, using EPOS-98" << std::endl;
        // fallthrough
    case sphere_type::larsson98:
        for (auto const &dir : epos24_1)
            extremes.emplace_back(extreme_points_along_direction(dir, k_points));
        for (auto const &dir : epos24_2)
            extremes.emplace_back(extreme_points_along_direction(dir, k_points));
        for (auto const &dir : epos24_3)
            extremes.emplace_back(extreme_points_along_direction(dir, k_points));
        // fallthrough
    case sphere_type::larsson26:
        for (auto const &dir : epos12)
            extremes.emplace_back(extreme_points_along_direction(dir, k_points));
        // fallthrough
    case sphere_type::larsson14:
        for (auto const &dir : epos8)
            extremes.emplace_back(extreme_points_along_direction(dir, k_points));
        // fallthrough
    case sphere_type::larsson6:
        for (auto const &dir : epos6)
            extremes.emplace_back(extreme_points_along_direction(dir, k_points));
        break;
    }

    // find the pair of points the furthest apart
    float dist = f_min;
    std::pair<glm::vec3, glm::vec3> furthest_pair;
    for (auto const &[min, max] : extremes)
    {
        float d = glm::distance(min, max);
        if (dist < d)
        {
            dist = d;
            furthest_pair = {min, max};
        }
    }

    // set up sphere
    center = (furthest_pair.first + furthest_pair.second) * 0.5f;
    radius = glm::length(furthest_pair.second - center);

    // enclose all points
    for (auto const &p : v)
        enclose(p);
}

void Sphere::symschur2(const glm::mat3 &m, int p, int q, float &s, float &c)
{
    if (abs(m[p][q]) > 0.0001f)
    {
        float r = (m[q][p] - m[p][q]) / (2.0f * m[p][q]);
        float t;
        if (r >= 0.0f)
            t = 1.0f / (r + sqrt(1.0f + r * r));
        else
            t = -1.0f / (-r + sqrt(1.0f + r * r));
        c = 1.0f / sqrt(1.0f + t * t);
        s = t * c;
    }
    else
    {
        s = 0.0f;
        c = 1.0f;
    }
}

void Sphere::jacobi(glm::mat3 &m1, glm::mat3 &m2)
{
    // initialize m2 to identiy matrix
    glm::mat3 identity(1);
    m2 = identity;

    // repeat for some maximum number of iterations
    static int constexpr max_iterations = 50;

    int p, q;
    float s, c;      // initialized / modified by calls to symschur2()
    float prev_norm; // initialized at the end of the first n loop
    glm::mat3 J, b, t;
    for (int n = 0; n < max_iterations; ++n)
    {
        // find the largest off-diagonal absolute element m1[p][q]
        p = 0;
        q = 1;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                // off diagonal
                if (i == j)
                    continue;
                if (abs(m1[i][j]) > abs(m1[p][q]))
                {
                    p = i;
                    q = j;
                }
            }
        }

        // compute jacobi rotation matrix J(p, q, theta)
        symschur2(m1, p, q, s, c);
        // set J to the identity matrix
        J = identity;
        // set rotation matrix
        J[p][p] = c;
        J[p][q] = s;
        J[q][p] = -s;
        J[q][q] = c;

        // cumulate rotations into what will contain the eigen vectors
        m2 = m2 * J;
        // make m2 more diagonal, until eigen values remain on diagonal
        m1 = glm::transpose(J) * m1 * J;
        // compute "norm" of off-diagonal elements
        float norm = 0.0f;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (i == j)
                    continue;
                norm += m1[i][j] * m1[i][j];
            }
        }

        // stop when no longer decreasing
        if (n > 2 && norm >= prev_norm)
            return;
        prev_norm = norm;
    }
}

void Sphere::pca(const std::vector<glm::vec3> &vertices)
{
    // compute covariance matrix
    glm::mat3 m = covariance_matrix(vertices);
    // decompose it into eigen vectors (v) and eigen values (m)
    glm::mat3 v;
    jacobi(m, v);
    // find the component with the largest spread (the largest magnitude eigen value)
    glm::vec3 e;
    int max_c = 0;
    float max_f = abs(m[1][1]);
    float max_e = abs(m[0][0]);

    if (max_f > max_e)
    {
        max_c = 1;
        max_e = max_f;
    }
    max_f = abs(m[2][2]);
    if (max_f > max_e)
    {
        max_c = 2;
        max_e = max_f;
    }

    e[0] = v[0][max_c];
    e[1] = v[1][max_c];
    e[2] = v[2][max_c];

    // find the most extreme points along direction 'e'
    std::pair<glm::vec3, glm::vec3> result = extreme_points_along_direction(e, vertices);

    // set up the sphere
    center = (result.first + result.second) * 0.5f;
    radius = glm::length(result.second - center);

    // enclose all points
    for (auto const &p : vertices)
        enclose(p);
}
