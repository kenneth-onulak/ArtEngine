#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

#include "helpers.h"

int main(int argc, char *args[])
{
    // create window
    Art::view.vsync(true);
    Art::view.m_line_width = 2.0f;
    Art::window("Bounding Volume Scene", 1200, 800);

    // setup views
    setup();

    // set handler functions
    Art::event.handler = eventHandler;
    Art::view.interface = interfaceFunc;

    // load shader
    Shader shader({"shader/default.vs", "shader/default.fs"}, {"in_Position", "in_Normal", "in_Color"});

    // load multiple objects from a file
    std::string path = "object/";
    std::vector<Model *> models = object::load_all(path + "Section6", color::silver);
    model_size = models.size() - 1;

    // load debug objects
    Cube cube;
    Model *sphere = object::load(path + "sphere_mid_poly");

    // transform objects
    glm::vec3 translate(0, -20000, 0);
    for (auto const &model : models)
        model->model = glm::translate(glm::mat4(1), translate);

    // render scene
    Art::view.pipeline = [&]() {
        Art::view.target(color::black); // target screen

        // update shader lighting
        shader.use();
        shader.uniform("vp", proj * view);
        shader.uniform("camera", pos);
        shader.uniform("pointlightpos", plightpos);
        shader.uniform("pointlightfar", pointfar);
        shader.uniform("pointlighton", on);
        shader.uniform("pointlightcolor", lightcolor);
        shader.uniform("brightness", brightness);
        shader.uniform("attenuation", attenuation);

        // render model array
        shader.uniform("renderbv", false);
        for (auto const &model : models)
        {
            shader.uniform("model", model->model);
            model->render(GL_TRIANGLES);
        }

        // render debug bounding volumes
        shader.uniform("renderbv", true);
        shader.uniform("bvcolor", bv_color);
        if (!use_single_bv)
            for (auto const &model : models)
            {
                if (use_aabb)
                {
                    model->aabb.compute();
                    cube.model = glm::translate(glm::mat4(1), model->aabb.center + translate) * //
                                 glm::scale(scale_matrix(model->aabb.scale), glm::vec3(1));
                    shader.uniform("model", cube.model);
                    cube.render(GL_LINES);
                }
                if (use_sphere)
                {
                    model->sphere.compute(sphere_type);
                    sphere->model = glm::translate(glm::mat4(1), model->sphere.center + translate) * //
                                    glm::scale(scale_matrix(model->sphere.radius), glm::vec3(1));
                    shader.uniform("model", sphere->model);
                    sphere->render(GL_LINES);
                }
            }
        if (use_single_bv)
        {
            if (use_aabb)
            {
                models[model_index]->aabb.compute();
                cube.model = glm::translate(glm::mat4(1), models[model_index]->aabb.center + translate) * //
                             glm::scale(scale_matrix(models[model_index]->aabb.scale), glm::vec3(1));
                shader.uniform("model", cube.model);
                cube.render(GL_LINES);
            }
            if (use_sphere)
            {
                models[model_index]->sphere.compute(sphere_type);
                sphere->model = glm::translate(glm::mat4(1), models[model_index]->sphere.center + translate) * //
                                glm::scale(scale_matrix(models[model_index]->sphere.radius), glm::vec3(1));
                shader.uniform("model", sphere->model);
                sphere->render(GL_LINES);
            }
        }
    };

    glm::mat4 mat4 =
        glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(1, 0, 0, 0), glm::vec4(1, 0, 0, 0), glm::vec4(1, 0, 0, 0));
    Art::loop([&]() {

    });

    Art::quit();

    return 0;
}
