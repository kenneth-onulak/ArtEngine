#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

#include "settings.h"

int main(int argc, char *args[])
{
    Art::view.vsync(true);
    Art::window("Lighting Scene Test", 1200, 800);

    setup();

    Art::event.handler = eventHandler;
    Art::view.interface = interfaceFunc;

    Shader shader({"shader/default.vs", "shader/default.fs"}, {"in_Position", "in_Normal", "in_Color"});

    std::string path = "object/";
    std::vector<Model *> models = object::load_all(path + "Section4");

    for (auto const &model : models)
        model->model = glm::translate(glm::mat4(1), glm::vec3(0, -42500, 0));
    //    models[0]->model = glm::translate(glm::mat4(1.0f), glm::vec3(2, 5, 2));
    //    models[1]->model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));
    //    models[2]->model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 2));
    //    models[3]->model = glm::translate(glm::mat4(1.0f), glm::vec3(24, 0, 0));
    //    models[4]->model = glm::translate(glm::mat4(1.0f), glm::vec3(-25, 15, 0));
    //    models[4]->model = glm::rotate(models[4]->model, glm::radians(90.0f), glm::vec3(0, 1, 0));

//    Model *room = construct_room();
//    room->model = glm::scale(glm::mat4(1.0f), glm::vec3(25));

    Art::view.pipeline = [&]() {
        // Render Scene
        Art::view.target(color::silver); // target Screen

        shader.use();
        shader.uniform("vp", proj * view);
        shader.uniform("camera", pos);

        // Point Shadow
        shader.uniform("pointlightpos", plightpos);
        shader.uniform("pointlightfar", pointfar);
        shader.uniform("pointlighton", on);
        shader.uniform("pointlightcolor", lightcolor);
        shader.uniform("brightness", brightness);
        shader.uniform("attenuation", attenuation);

//        shader.uniform("model", room->model);
//        room->render(GL_TRIANGLES);

        for (auto const &model : models)
        {
            shader.uniform("model", model->model);
            model->render(GL_TRIANGLES);
        }
    };

    Art::loop([&]() {

    });

    Art::quit();

    return 0;
}
