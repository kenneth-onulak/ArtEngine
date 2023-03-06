#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

#include "helpers.h"
#include "bounding_volume_hierarchy.h"

int main(int argc, char *args[])
{
    // create window
    Art::view.vsync(true);
    Art::view.m_line_width = 2.0f;
    Art::view.m_show_interface = true;
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
    std::vector<Model *> models =
        object::load_all({path + "Section4"}, color::silver);
    model_size = models.size() - 1;

    // load debug objects
    Cube cube;
    Icosphere sphere(1, 3);

    // transform objects
    glm::vec3 translate(0, -43000, -15000);
    //    glm::vec3 translate(0, 0, 0);
    for (auto const &model : models)
        model->model = glm::translate(glm::mat4(1), translate);

    // color value
    int color_index = 0;

    std::function<void(bvh::Node **)> render_tree = [&](bvh::Node **tree) {
        bvh::Node *node = *tree;
        // base case
        if (node == nullptr)
            return;
        // early out to render tree depths
        if (node->depth > depth)
            return;

        shader.uniform("bvcolor", colors[node->depth % 7]);

        if (use_aabb)
        {
            cube.model = glm::translate(glm::mat4(1), node->aabb.center + translate) * //
                         node->aabb.T * // rotation matrix for obb, otherwise identity matrix
                         glm::scale(scale_matrix(node->aabb.scale), glm::vec3(1));
            shader.uniform("model", cube.model);
            cube.render(GL_LINES);
        }
        if (use_sphere)
        {
            sphere.model = glm::translate(glm::mat4(1), node->sphere.center + translate) * //
                           ((sphere_type == Sphere::sphere_type::ellipsoid) // choose corresponding scale matrix
                                ? glm::scale(scale_matrix(node->sphere.scale), glm::vec3(1))
                                : glm::scale(scale_matrix(node->sphere.radius), glm::vec3(1)));
            shader.uniform("model", sphere.model);
            sphere.render(GL_LINES);
        }

        render_tree(&node->left);
        render_tree(&node->right);
    };

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

        // render models using diffuse rendering
        shader.uniform("renderbv", false);
        if (!use_single_bv)
            for (auto const &model : models)
            {
                shader.uniform("model", model->model);
                model->render(GL_TRIANGLES);
            }
        if (use_single_bv)
        {
            shader.uniform("model", models[model_index]->model);
            models[model_index]->render(GL_TRIANGLES);
        }

        // reset color index and render bounding volumes
        color_index = 0;
        shader.uniform("renderbv", true);
        if (!use_single_bv && !use_bvh)
            for (auto const &model : models)
            {
                shader.uniform("bvcolor", colors[color_index % 7]);
                ++color_index;

                if (use_aabb)
                {
                    model->aabb.compute(bb_type);
                    cube.model = glm::translate(glm::mat4(1), model->aabb.center + translate) * //
                                 model->aabb.T * // rotation matrix for obb, otherwise identity matrix
                                 glm::scale(scale_matrix(model->aabb.scale), glm::vec3(1));
                    shader.uniform("model", cube.model);
                    cube.render(GL_LINES);
                }
                if (use_sphere)
                {
                    model->sphere.compute(sphere_type);
                    sphere.model = glm::translate(glm::mat4(1), model->sphere.center + translate) * //
                                   ((sphere_type == Sphere::sphere_type::ellipsoid) // choose corresponding scale matrix
                                        ? glm::scale(scale_matrix(model->sphere.scale), glm::vec3(1))
                                        : glm::scale(scale_matrix(model->sphere.radius), glm::vec3(1)));
                    shader.uniform("model", sphere.model);
                    sphere.render(GL_LINES);
                }
            }
        if (use_single_bv && !use_bvh)
        {
            shader.uniform("bvcolor", color::lime);

            if (use_aabb)
            {
                models[model_index]->aabb.compute(bb_type);
                cube.model = glm::translate(glm::mat4(1), models[model_index]->aabb.center + translate) * //
                             models[model_index]->aabb.T * // rotation matrix for obb, otherwise identity matrix
                             glm::scale(scale_matrix(models[model_index]->aabb.scale), glm::vec3(1));
                shader.uniform("model", cube.model);
                cube.render(GL_LINES);
            }
            if (use_sphere)
            {
                models[model_index]->sphere.compute(sphere_type);
                sphere.model = glm::translate(glm::mat4(1), models[model_index]->sphere.center + translate) * //
                               ((sphere_type == Sphere::sphere_type::ellipsoid) // choose corresponding scale matrix
                                    ? glm::scale(scale_matrix(models[model_index]->sphere.scale), glm::vec3(1))
                                    : glm::scale(scale_matrix(models[model_index]->sphere.radius), glm::vec3(1)));
                shader.uniform("model", sphere.model);
                sphere.render(GL_LINES);
            }
        }

        if (use_bvh)
        {
            bb_type = AABB::bb_type::aabb;
            sphere_type = Sphere::sphere_type::ritter;
            // recompute aabb and ritter sphere for all models to use with bvh
            for (auto &model : models)
            {
                model->aabb.compute(bb_type);
                model->sphere.compute(sphere_type);
            }
            render_tree(bvh::tree);
        }
    };

    Art::loop([&]() {
        if(use_bvh)
        {
            if (!bvh::tree)
            {
                bvh::tree = new bvh::Node*;

                if (use_bottom_up)
                {
                    bvh::bottom_up_bvh(bvh::tree, models);
                    bvh::bottom_up_depth(*bvh::tree, 0);
                }
                else
                {
                    bvh::top_down_bvh(bvh::tree, models, 0, models.size() - 1, 0);
                }
            }
        }
    });

    Art::quit();

    for (auto &m : models)
        delete m;

    return 0;
}
