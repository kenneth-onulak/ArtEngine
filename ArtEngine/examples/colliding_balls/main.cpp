#include "pch.h"
#include "ArtEngine.h"

#define SPARTICLESX 200
#define SPARTICLESY 100

#define RADIUS 0.004f
#define NPARTICLES (SPARTICLESX * SPARTICLESY)

int main(int argc, char *args[])
{
    // Initialize the Compute Shader System
    //  Art::benchmark = true;
    //  Art::view.vsync = false;
    Art::view.m_anti_alias = 0;
    Art::window("N-Ball Collisions", 800, 400);

    camera::near = -200.0f;
    camera::far = 200.0f;
    camera::zoom_rate = 15.0f;
    camera::init(500, camera::camera_type::orthographic);

    // glPointSize(2.0f);

    bool paused = true;
    Art::view.interface = [&]() {};
    Art::event.handler = [&]() {
        camera::handler();

        if (Art::event.key_up() == SDLK_p)
            paused = !paused;
    };

    // Get Positions and Velocities
    std::vector<glm::vec4> position;
    std::vector<glm::vec4> velocity;
    std::vector<float> mass;

    for (int i = 1; i <= SPARTICLESX; i++)
    {
        for (int j = 1; j <= SPARTICLESY; j++)
        {

            glm::vec4 pos =
                glm::vec4(2.0f * (float)i / (SPARTICLESX + 1) - 1.0f, 2.0f * (float)j / (SPARTICLESY + 1) - 1.0f, 0, 1);
            const glm::vec2 scale = glm::vec2(1, 8.0 / 4.0);

            if (glm::length(glm::vec2(pos) / scale - glm::vec2(0.5, 0) / scale) < 0.15)
                continue;

            if (glm::length(glm::vec2(pos) / scale - glm::vec2(-0.5, 0) / scale) < 0.15)
                continue;

            if (glm::length(glm::vec2(pos) / scale - glm::vec2(0, 0.5) / scale) < 0.15)
                continue;

            if (glm::length(glm::vec2(pos) / scale - glm::vec2(0, -0.5) / scale) < 0.15)
                continue;

            position.push_back(pos);
            // velocity.push_back(200.0f*glm::normalize((glm::vec4(rand()%1000, rand()%1000, rand()%1000,
            // 500.0f)-500.0f)/500.0f));
            velocity.push_back(glm::vec4(0, 0, 0, 0));
        }
    }

    // 3 Buffers
    Buffer posbufA(position);
    Buffer posbufB(position);
    Buffer velbufA(velocity);
    Buffer velbufB(velocity);
    // Buffer massbuf(mass);

    // Compute Shader with SSBO Binding Points
    Compute compute("shader/collide.cs", {"positionA", "positionB", "velocityA", "velocityB"});

    // Link Buffers to the SSBO Binding Points
    compute.bind<glm::vec4>("positionA", &posbufA);
    compute.bind<glm::vec4>("positionB", &posbufB);
    compute.bind<glm::vec4>("velocityA", &velbufA);
    compute.bind<glm::vec4>("velocityB", &velbufB);

    Square2D flat;
    Instance particles(&flat);
    particles.bind<glm::vec4>("in_Pos", &posbufA);
    particles.m_size = position.size();

    // Visualization Shader, does not need attributes
    Shader particleShader({"shader/particle.vs", "shader/particle.fs"}, {"in_Quad", "in_Tex", "in_Pos"},
                          {"velocityA", "velocityB"});
    particleShader.bind<glm::vec4>("velocityA", &velbufA);
    particleShader.bind<glm::vec4>("velocityB", &velbufB);

    // Define the rendering pipeline
    Art::view.pipeline = [&]() {
        Art::view.target(color::black); // Clear Screen to white
        particleShader.use();
        particleShader.uniform("R", RADIUS);
        particles.render(GL_TRIANGLE_STRIP);
    };

    // Execute the render loop
    Art::loop([&]() {
        if (paused)
            return;

        compute.use();
        compute.uniform("size", (int)particles.m_size);
        compute.uniform("R", RADIUS);

        compute.uniform("collide", true);
        compute.dispatch(1 + SPARTICLESX / 32, 1 + SPARTICLESY / 32);

        compute.uniform("collide", false);
        compute.dispatch(1 + SPARTICLESX / 32, 1 + SPARTICLESY / 32);
    });

    Art::quit();

    return 0;
}
