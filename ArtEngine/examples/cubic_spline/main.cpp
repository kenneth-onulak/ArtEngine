#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

#include "settings.h"
#include "cubic_spline.h"

int main(int argc, char *args[])
{
    // initialize the window
    Art::view.m_show_interface = true;
    Art::view.vsync(true);
    Art::window("Lighting Scene Test", 1200, 800);

    // set up the camera and view
    setup();

    // set input event handler
    Art::event.handler = eventHandler;

    // set imgui interface
    Art::view.interface = interfaceFunc;

    // set up the shader
    Shader shader({"shader/default.vs", "shader/default.fs"}, {"in_Position", "in_Normal", "in_Color"});

    // create the control point model
    Icosphere sphere(1, 2);

    glLineWidth(0.5f);

    // view pipeline draws everything on screen
    Art::view.pipeline = [&]() {
        // Render Scene
        Art::view.target(color::black); // target Screen

        shader.use();
        shader.uniform("vp", proj * view);
        shader.uniform("camera", pos);

        // draw the control points
        shader.uniform("color", color::lime);
        shader.uniform("alpha", 1.0f);
        if (draw_control_points)
            for (auto const &p : control_points)
            {
                sphere.model = glm::translate(glm::mat4(1), p) * //
                               glm::scale(glm::mat4(1), glm::vec3(1));
                shader.uniform("model", sphere.model);
                sphere.render(GL_LINES);
            }

        // draw polygonal line
        shader.uniform("color", color::lime);
        shader.uniform("alpha", 0.5f);
        if (draw_polygonal_line && control_points.size() >= 2)
        {
            for (int i = 0; i < control_points.size() - 1; ++i)
            {
                Line line(control_points[i], control_points[i + 1]);
                shader.uniform("model", line.model);
                line.render(GL_LINES);
            }
        }

        // draw curve
        shader.uniform("color", color::magenta);
        shader.uniform("alpha", 1.00f);
        for (int i = 0; i < curve_points.size() - 1; ++i)
        {
            Line line(curve_points[i], curve_points[i + 1]);
            shader.uniform("model", line.model);
            line.render(GL_LINES);
        }
    };

    // project loop
    Art::loop([&]() {
        // perform cubic spline mathd
        if (control_points.size() >= 3)
        {
            std::vector<glm::vec3> coeffs = CubicSpline(control_points);
            size_t size = control_points.size() - 1;
            for (int i = 0; i < line_points; ++i)
            {
                float const t = static_cast<float>(i) / static_cast<float>(line_points - 1) * static_cast<float>(size);

                glm::vec3 p(0);

                int c = 0;
                for (size_t j = 0; j < coeffs.size(); ++j)
                {
                    if (j < 4)
                        p += coeffs[j] * powf(t, j);
                    else
                    {
                        ++c;
                        p += coeffs[j] * static_cast<float>(truncated_power_function(t, c, 3));
                    }
                }
                curve_points[i] = p;
            }
        }
    });

    Art::quit();

    return 0;
}
