#include "../../include/ArtEngine.h"

// Camera Data
glm::vec3 pos = glm::vec3(20);
glm::vec3 up = glm::vec3(0, 1, 0);
glm::vec3 xz = glm::vec3(1, 0, 1);
glm::vec3 look = glm::vec3(0, 10, 0);
glm::mat4 proj;
glm::mat4 view;
float scale = 0.025f;

// Pointlight Data
float pointnear = 0.1f;
float pointfar = 60.0f;
std::vector<glm::mat4> views;
glm::mat4 pointproj;
glm::vec3 plightpos = glm::vec3(4022, 32758, 50000);
bool lightupdate = true;

// Pointlight Properties
bool on = true;
float lightcolor[3] = {1.0, 0.9, 0.8};
float brightness = 1.0;
float attenuation[3] = {0.5, 1.0, 5.0};

// compute matrices
void setup()
{
    proj = glm::ortho(-(float)Art::view.width() / scale, (float)Art::view.width() / scale,
                      -(float)Art::view.height() / scale, (float)Art::view.height() / scale, -50000.0f, 50000.0f);
    view = glm::lookAt(pos, look, up);

    pointproj = glm::perspective(glm::radians(90.0f), 1.0f, pointnear, pointfar);
    views.clear();
    views.push_back(pointproj *
                    glm::lookAt(plightpos, plightpos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    views.push_back(pointproj *
                    glm::lookAt(plightpos, plightpos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    views.push_back(pointproj * glm::lookAt(plightpos, plightpos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    views.push_back(pointproj *
                    glm::lookAt(plightpos, plightpos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    views.push_back(pointproj *
                    glm::lookAt(plightpos, plightpos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    views.push_back(pointproj *
                    glm::lookAt(plightpos, plightpos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
}

// Event Handler
std::function<void()> eventHandler = []() {
    if (Art::event.key_down(SDLK_w))
        scale /= 0.99;
    if (Art::event.key_down(SDLK_a))
        pos = glm::rotate(glm::mat4(1), -glm::radians(0.75f), up) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_s))
        scale *= 0.99;
    if (Art::event.key_down(SDLK_d))
        pos = glm::rotate(glm::mat4(1), glm::radians(0.75f), up) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_LSHIFT))
        pos = glm::rotate(glm::mat4(1), -glm::radians(0.75f), glm::vec3(1, 1, 1)) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_SPACE))
        pos = glm::rotate(glm::mat4(1), glm::radians(0.75f), glm::vec3(1, 1, 1)) * glm::vec4(pos, 1.0);


    setup(); // recompute (I know this shouldn't be called all the time, whatever lol)
};

// interface function
Handle interfaceFunc = []() {
    // window Size
    ImGui::SetNextWindowSize(ImVec2(480, 260), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(50, 470), ImGuiCond_Once);

    ImGui::Begin("Point Light Scene Controller", NULL, ImGuiWindowFlags_NoResize);

    ImGui::ColorEdit3("Light Color", lightcolor);
    ImGui::SliderFloat3("Attenuation", attenuation, 0.0f, 25.0f);
    ImGui::Checkbox("On Switch", &on);
    ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);
    ImGui::SliderFloat3("Position", &plightpos[0], -50000.0f, 50000.0f);

    ImGui::Separator();
    ImGui::Text("Position: (%f, %f, %f)", pos.x, pos.y, pos.z);
    ImGui::Text("Scale: %f", scale);
    ImGui::Text("Look at: (%f, %f, %f)", look.x, look.y, look.z);
    lightupdate = true;

    ImGui::End();
};
