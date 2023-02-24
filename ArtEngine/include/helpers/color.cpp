#include "pch.h"
#include "color.h"

namespace color
{

glm::vec3 pick(int i, int const n)
{
    auto const z = static_cast<float>(i % n);
    return glm::vec3(((i / (n * n)) % n), ((i / n) % n), z) / glm::vec3(static_cast<float>(n) - 1.0f);
}

glm::vec3 rainbow(float t)
{
    return bezier(t, {red, yellow, lime, cyan, blue, magenta});
}

glm::vec4 i2rgba(int i)
{
    return glm::vec4(((i >> 0) & 0xff), ((i >> 8) & 0xff), ((i >> 16) & 0xff), ((i >> 24) & 0xff));
}

glm::vec3 i2rgb(int i)
{
    return glm::vec3(((i >> 0) & 0xff), ((i >> 8) & 0xff), ((i >> 16) & 0xff));
}

double hash_rand(int i)
{
    return static_cast<double>(position_hash(std::to_string(i)) % 1000) / 1000.0;
}

}
