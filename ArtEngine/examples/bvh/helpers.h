#include "../../include/pch.h"
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

// bounding volumes and bounding volume hierarchy
bool use_bvh = false;
bool use_aabb = true;
bool use_sphere = false;
Sphere::sphere_type sphere_type = Sphere::sphere_type::centroid;

glm::vec3 bv_color = color::lime;

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
std::function<void()> eventHandler = []() {
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
        pos = glm::rotate(glm::mat4(1), glm::radians(0.75f), glm::vec3(0,0,1)) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_SPACE))
        pos += glm::vec3(1, 0, 0);

    setup(); // recompute (I know this shouldn't be called all the time, whatever lol)
};

// interface function
Handle interfaceFunc = []() {
    // window Size
    ImGui::SetNextWindowSize(ImVec2(318, 335), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);

    ImGui::Begin("Bounding Volume Controller", NULL, ImGuiWindowFlags_NoResize);

    ImGui::BeginTabBar("tabs");
    if (ImGui::BeginTabItem("Bounding Volume"))
    {
        use_bvh = false;
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("None", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = false;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("AABB", ImVec2(-1, 0)))
        {
            use_aabb = true;
            use_sphere = false;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Centroid", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::centroid;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Ritter", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::ritter;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS6", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson6;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS14", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson14;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS26", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson26;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS98", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson98;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("PCA", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::pca;
        }
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Bounding Volume Hierarchy"))
    {
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

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
