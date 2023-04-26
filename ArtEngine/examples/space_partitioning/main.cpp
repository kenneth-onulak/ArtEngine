#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

#include "helpers.h"
#include "octree.h"
#include "bsp_tree.h"

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
    std::vector<Model *> models = object::load_all({path + "Section4"}, color::silver);
    model_size = models.size() - 1;

    // store diffuse color info
    std::vector<std::vector<glm::vec4>> default_colors;
    for (auto const &model : models)
    {
        // get the color information
        std::vector<glm::vec4> color;
        color.resize(model->size);
        model->buffers["in_Color"]->retrieve(color);

        default_colors.push_back(color);
    }

    // create the octree
    OctreeNode const *octree = BuildOctTree(models, Center(models), Longest(models), 8);

    // create the bsp tree
    std::vector<triangle> world_triangles;
    std::vector<int> model_index;
    std::vector<std::vector<size_t>> model_indices;
    for (size_t j = 0; j < models.size(); ++j)
    {
        // get the vertex information
        std::vector<glm::vec3> vertices;
        vertices.resize(models[j]->size);
        models[j]->buffers["in_Position"]->retrieve(vertices);

        for (size_t i = 0; i < vertices.size(); i += 3)
        {
            triangle temp;
            temp.points[0] = vertices[i];
            temp.points[1] = vertices[i + 1];
            temp.points[2] = vertices[i + 2];

            world_triangles.push_back(temp);

            model_index.push_back(static_cast<int>(j));

            std::vector<size_t> temp_v;
            temp_v.push_back(i);
            temp_v.push_back(i + 1);
            temp_v.push_back(i + 2);
            model_indices.push_back(temp_v);
        }
    }

    BSPNode const *bsp_tree = BuildBSPTree(world_triangles, models, 8, model_index, model_indices);

    // load debug objects
    Cube cube;
    Icosphere sphere(1, 3);

    // transform objects
    glm::vec3 translate(0, -43000, -15000);
    //    glm::vec3 translate(0, 0, 0);
    for (auto const &model : models)
        model->model = glm::translate(glm::mat4(1), translate);

    // helper function to render entire tree
    std::function<void(OctreeNode const *)> render_octree = [&](OctreeNode const *node) {
        // base case
        if (node == nullptr)
            return;

        shader.uniform("bvcolor", colors[node->depth % 7]);

        cube.model = glm::translate(glm::mat4(1), node->center + translate) * //
                     glm::scale(scale_matrix(glm::vec3(node->half_size)), glm::vec3(1));
        shader.uniform("model", cube.model);
        cube.render(GL_LINES);

        for (auto const *child : node->children)
            render_octree(child);
    };

    std::function<void(BSPNode const *)> render_bsp_tree = [&](BSPNode const *node) {
        // base case
        if (node == nullptr)
            return;

        render_bsp_tree(node->front);
        render_bsp_tree(node->back);
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

        shader.uniform("renderbv", false);

        if (!use_bsp && needs_update)
        {
            // reset to default model color
            for (size_t i = 0; i < models.size(); ++i)
                models[i]->bind<glm::vec4>("in_Color", new Buffer(default_colors[i]), true);
            needs_update = false;
        }
        else if (needs_update)
        {
            for (auto const &model : models)
                model->bind<glm::vec4>("in_Color", new Buffer(model->color), true);
            needs_update = false;
        }


        // render models using diffuse rendering
        for (auto const &model : models)
        {
            shader.uniform("model", model->model);
            if (!use_bsp)
                model->render(GL_TRIANGLES);
            else
                model->render(GL_LINES);
        }

        // reset color index and render octree
        if (use_octree)
        {
            shader.uniform("renderbv", true);
            render_octree(octree);
        }

        if (use_bsp)
            render_bsp_tree(bsp_tree);
    };

    Art::loop([&]() {
        // do nothing
    });

    Art::quit();

    // cleanup
    for (auto &m : models)
        delete m;

    return 0;
}
