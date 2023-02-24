#ifndef ARTENGINE_COLOR_H
#define ARTENGINE_COLOR_H

namespace color
{

// predefined colors
glm::vec3 const black(0);
glm::vec3 const white(1);

glm::vec3 const red(1, 0, 0);
glm::vec3 const lime(0, 1, 0);
glm::vec3 const blue(0, 0, 1);

glm::vec3 const yellow(1, 1, 0);
glm::vec3 const cyan(0, 1, 1);
glm::vec3 const magenta(1, 0, 1);

glm::vec3 const silver(0.753, 0.753, 0.753);
glm::vec3 const gray(0.5, 0.5, 0.5);
glm::vec3 const maroon(0.5, 0, 0);
glm::vec3 const olive(0.5, 0.5, 0);
glm::vec3 const green(0, 0.5, 0);
glm::vec3 const purple(0.5, 0, 0.5);
glm::vec3 const teal(0, 0.5, 0.5);
glm::vec3 const navy(0, 0, 0.5);

template <typename T>
T bezier(float t, std::vector<T> points)
{
    while (points.size() > 1)
    {
        std::vector<T> next;
        for (size_t i = 0; i < points.size() - 1; ++i)
            next.push_back((1.0f - t) * points[i] + t * points[i + 1]);
        points = next;
    }

    return points[0];
}

template <typename T>
T bezier(float t, std::initializer_list<T> p)
{
    std::vector<T> points;
    points.insert(points.end(), p.begin(), p.end());
    return bezier(t, points);
}

template <typename T>
float index(T c, const int n)
{
    glm::vec3 w = glm::vec3(static_cast<float>(n) - 1.0f) * glm::vec3(n * n, n, 1);
    return glm::dot(c, w);
}

glm::vec3 pick(int i, int const n);

glm::vec3 rainbow(float t);

glm::vec4 i2rgba(int i);
glm::vec3 i2rgb(int i);

std::hash<std::string> const position_hash;
double hash_rand(int i);

} // namespace color

#endif // ARTENGINE_COLOR_H
