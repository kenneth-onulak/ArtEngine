#include "../include/pch.h"
#include "../include/ArtEngine.h"

#include "FastNoiseLite.h"

std::uniform_real_distribution<double> u(0.0, 1.0);

glm::vec3 sphere_sample(std::mt19937 &g)
{

    double theta = 2 * std::numbers::pi * u(g);
    double phi = acos(1 - 2 * u(g));
    return glm::vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}

int main(int argc, char *args[])
{
    Art::view.ccw(false);
    Art::view.vsync(false);
    // open window
    Art::window("Spherical Voronoi Diagram with Cubemap Texture", 800, 800);

    // camera
    camera::near = -100.0f;
    camera::far = 100.0f;
    camera::zoom_rate *= 10.0f;
    camera::init(500.0f, camera::camera_type::orthographic);

    // shaders
    Shader sphere({"shader/sphere.vs", "shader/sphere.fs"}, {"in_Position"});
    Icosphere icosahedron;

    Shader cube_voronoi({"shader/cubevoronoi.vs", "shader/cubevoronoi.gs", "shader/cubevoronoi.fs"}, {"in_Position"});
    Cubemap voronoi(512, 512);

    // view matrices
    glm::mat4 pointproj = glm::perspective(glm::radians(90.0f), 1.0f, 0.01f, 1.1f);
    std::vector<glm::mat4> views;
    views.push_back(pointproj * glm::lookAt(glm::vec3(0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    views.push_back(pointproj * glm::lookAt(glm::vec3(0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    views.push_back(pointproj * glm::lookAt(glm::vec3(0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    views.push_back(pointproj * glm::lookAt(glm::vec3(0), glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    views.push_back(pointproj * glm::lookAt(glm::vec3(0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    views.push_back(pointproj * glm::lookAt(glm::vec3(0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

    // Random centroids
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::vector<glm::vec3> centroids;
    std::vector<glm::vec3> offsets;
    for (size_t i = 0; i < (2 << 13); ++i)
        centroids.push_back(sphere_sample(generator));
    offsets = centroids;

    // buffer and instance
    Buffer centroid_buffer(offsets);

    Square3D flat;
    Instance instance(&flat);
    instance.bind<glm::vec3>("in_Centroid", &centroid_buffer);

    // loop
    const float R = 0.05f;
    Art::event.handler = camera::handler;

    Art::view.pipeline = [&]() {
        cube_voronoi.use();
        cube_voronoi.uniform("vp", views);
        cube_voronoi.uniform("R", R);
        instance.render();

        Art::view.target(color::silver);

        sphere.use();
        sphere.uniform("vp", camera::view_projection);
        sphere.texture("voronoicolor", voronoi.texture());
        sphere.texture("voronoidepth", voronoi.depth());
        icosahedron.render(GL_TRIANGLES);
    };

    // movement
    float t = 0.0f;

    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(8.0f);
    noise.SetFractalLacunarity(2.0f);
    noise.SetFractalGain(0.6f);
    noise.SetFrequency(1.0);

    Art::loop([&]() {
        t += 0.01f;

        for (size_t i = 0; i < offsets.size(); ++i)
        {
            offsets[i].x = centroids[i].x + 0.5f * R * noise.GetNoise(centroids[i].x, centroids[i].y, t);
            offsets[i].y = centroids[i].y + 0.5f * R * noise.GetNoise(centroids[i].x, centroids[i].y, -t);
            offsets[i].z = centroids[i].z + 0.5f * R * noise.GetNoise(centroids[i].x, centroids[i].y, t);
        }
        centroid_buffer.fill(offsets);
    });

    Art::quit();

    std::cout << "SUCCESS!" << std::endl;
    return EXIT_SUCCESS;
}
