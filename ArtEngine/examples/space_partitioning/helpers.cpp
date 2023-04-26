#include "../../include/pch.h"
#include "helpers.h"

// Camera Data
glm::vec3 pos = glm::vec3(20);
glm::vec3 up = glm::vec3(0, 1, 0);
glm::vec3 xz = glm::vec3(1, 0, 1);
glm::vec3 look = glm::vec3(0, 15, 0);
glm::mat4 proj;
glm::mat4 view;
float scale = 0.015f;

// Pointlight Data
float pointnear = 0.1f;
float pointfar = 6000.0f;
std::vector<glm::mat4> views;
glm::mat4 pointproj;
glm::vec3 plightpos = glm::vec3(4022, 32758, 50000);
bool lightupdate = true;

// Pointlight Properties
bool on = true;
float lightcolor[3] = {1.0, 0.9, 0.8};
float brightness = 1.0;
float attenuation[3] = {0.5, 1.0, 5.0};

// bounding volumes
size_t model_index = 0;
size_t model_size;

// octree
bool use_octree = false;
// bsp
bool use_bsp = false;

bool needs_update = false;


// compute matrices
void setup()
{
    proj = glm::ortho(-(float)Art::view.width() / scale, (float)Art::view.width() / scale,
                      -(float)Art::view.height() / scale, (float)Art::view.height() / scale, -100000.0f, 100000.0f);
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
Handle eventHandler = []() {
    if (Art::event.key_down(SDLK_w))
        scale /= 0.99;
    if (Art::event.key_down(SDLK_a))
    {
        pos = glm::rotate(glm::mat4(1), -glm::radians(0.75f), up) * glm::vec4(pos, 1.0);
        xz = glm::rotate(glm::mat4(1), -glm::radians(0.75f), up) * glm::vec4(xz, 1.0);
    }
    if (Art::event.key_down(SDLK_s))
        scale *= 0.99;
    if (Art::event.key_down(SDLK_d))
    {
        pos = glm::rotate(glm::mat4(1), glm::radians(0.75f), up) * glm::vec4(pos, 1.0);
        xz = glm::rotate(glm::mat4(1), glm::radians(0.75f), up) * glm::vec4(xz, 1.0);
    }
    if (Art::event.key_down(SDLK_LSHIFT))
        look.y -= 0.5f;
    if (Art::event.key_down(SDLK_SPACE))
        look.y += 0.5f;

    // model transitions
    if (Art::event.key_up() == SDLK_LEFT)
        if (model_index > 0)
            --model_index;
    if (Art::event.key_up() == SDLK_RIGHT)
        if (model_index < model_size)
            ++model_index;

    setup(); // recompute (I know this shouldn't be called all the time, whatever lol)
};

// interface function
Handle interfaceFunc = []() {
    // window Size
    ImGui::SetNextWindowSize(ImVec2(318, -1), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);

    ImGui::Begin("Space Partitioning Controller", NULL, ImGuiWindowFlags_NoResize);
    ImGui::Spacing();
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Separator();

    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::Checkbox("Octree", &use_octree))
    {
        use_bsp = false;
        needs_update = true;
    }

    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::Checkbox("BSP", &use_bsp))
    {
        use_octree = false;
        needs_update = true;
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::End();
};

glm::mat4 scale_matrix(float r)
{
    glm::mat3 m(r);
    return glm::mat4(m);
}

glm::mat4 scale_matrix(glm::vec3 v)
{
    glm::mat4 m(1);
    m[0][0] = v.x;
    m[1][1] = v.y;
    m[2][2] = v.z;
    return m;
}