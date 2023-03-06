#include "../../include/pch.h"
#include "helpers.h"

#include "bounding_volume_hierarchy.h"

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
bool use_single_bv = false;
bool use_aabb = true;
AABB::bb_type bb_type = AABB::bb_type::aabb;
bool use_sphere = false;
Sphere::sphere_type sphere_type = Sphere::sphere_type::centroid;
size_t model_index = 0;
size_t model_size;

glm::vec3 bv_color = color::lime;

// bounding volume hierarchy
bool use_bvh = false;
bool use_bottom_up = false;
int tree_type = 0;
bool recompute_tree = false;
int depth = 0;

// bottom up variables
float neighbor_weight = 0.6f;
float combined_weight = 0.3f;
float volume_weight = 0.1f;

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

    ImGui::Begin("Bounding Volume Controller", NULL, ImGuiWindowFlags_NoResize);
    ImGui::Spacing();
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::BeginTabBar("tabs");
    if (ImGui::BeginTabItem("Bounding Volume"))
    {
        use_bvh = false;

        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Render Single Bounding Volume", ImVec2(-1, 0)))
            use_single_bv = true;
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Previous Model", ImVec2(ImGui::GetWindowWidth() * 0.46f, 0)))
        {
            if (model_index > 0)
                --model_index;
        }
        ImGui::SameLine();
        if (ImGui::Button("Next Model", ImVec2(-1, 0)))
        {
            if (model_index < model_size)
                ++model_index;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Render All Bounding Volumes", ImVec2(-1, 0)))
            use_single_bv = false;
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
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
            bb_type = AABB::bb_type::aabb;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("OBB", ImVec2(-1, 0)))
        {
            use_aabb = true;
            use_sphere = false;
            bb_type = AABB::bb_type::obb;
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
        if (ImGui::Button("Larsson EPOS-6", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson6;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS-14", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson14;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS-26", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::larsson26;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Larsson EPOS-98", ImVec2(-1, 0)))
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
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Ellipsoid", ImVec2(-1, 0)))
        {
            use_aabb = false;
            use_sphere = true;
            sphere_type = Sphere::sphere_type::ellipsoid;
        }
        ImGui::Spacing();

        ImGui::EndTabItem();
    }

    ////////////////////////////////////////////////////////////////////////////////
    //// BVH
    ////////////////////////////////////////////////////////////////////////////////

    if (ImGui::BeginTabItem("Bounding Volume Hierarchy"))
    {
        use_bvh = true;
        use_single_bv = false;
        int old_tree_type = tree_type;

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("Bounding Volume:");
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("AABB", ImVec2(-1, 0)))
        {
            if (!use_aabb)
                recompute_tree = true;
            use_aabb = true;
            use_sphere = false;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Sphere", ImVec2(-1, 0)))
        {
            if (!use_sphere)
                recompute_tree = true;
            use_aabb = false;
            use_sphere = true;
        }
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Separator();

        ImGui::Spacing();
        ImGui::Text("Tree:");
        ImGui::Spacing();
        if (ImGui::Button("Top Down - Median Split", ImVec2(-1, 0)))
        {
            tree_type = 0;
            use_bottom_up = false;
        }
        ImGui::Spacing();
        ImGui::Spacing();
//        if (ImGui::Button("Top Down - K-even Split", ImVec2(-1, 0)))
//        {
//            tree_type = 1;
//            use_bottom_up = false;
//        }
//        ImGui::Spacing();
//        ImGui::Spacing();
        if (ImGui::Button("Top Down - Median Extent Split", ImVec2(-1, 0)))
        {
            tree_type = 2;
            use_bottom_up = false;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Bottom Up", ImVec2(-1, 0)))
        {
            tree_type = 3;
            use_bottom_up = true;
        }
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Separator();

        ImGui::Spacing();
        ImGui::Text("Render Depth");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::PushItemWidth(80);
        ImGui::InputInt("##depth", &depth, 1, 1);
        ImGui::PopItemWidth();
        if (depth < 0)
            depth = 0;
        if (depth > 6)
            depth = 6;
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Separator();

        ImGui::Spacing();
        ImGui::Text("Bottom Up Tree Heuristics:");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("Nearest Neighbor Weight");
        if (ImGui::SliderFloat("##Nearest Neighbor Weight", &neighbor_weight, 0.0f, 1.0f, "%.2f"))
        {
            if (neighbor_weight + combined_weight + volume_weight < 1.0f)
            {
                combined_weight = 1.0f - neighbor_weight - volume_weight;
                volume_weight = 1.0f - neighbor_weight - combined_weight;
            }
            else
            {
                combined_weight = 0.0f;
                volume_weight = 0.0f;
            }
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("Combined Volume Weight");
        if (ImGui::SliderFloat("##Combined Volume Weight", &combined_weight, 0.0f, 1.0f, "%.2f"))
        {
            if (neighbor_weight + combined_weight + volume_weight < 1.0f)
            {
                neighbor_weight = 1.0f - combined_weight - volume_weight;
                volume_weight = 1.0f - neighbor_weight - combined_weight;
            }
            else
            {
                neighbor_weight = 0.0f;
                volume_weight = 0.0f;
            }
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("Relative Weight Increase");
        if (ImGui::SliderFloat("##Relative Weight Increase", &volume_weight, 0.0f, 1.0f, "%.2f"))
        {
            if (neighbor_weight + combined_weight + volume_weight < 1.0f)
            {
                neighbor_weight = 1.0f - combined_weight - volume_weight;
                combined_weight = 1.0f - neighbor_weight - volume_weight;
            }
            else
            {
                neighbor_weight = 0.0f;
                combined_weight = 0.0f;
            }
        }
        ImGui::Spacing();
        ImGui::Spacing();

        // reset the tree when a new option was selected
        if (old_tree_type != tree_type && bvh::tree || recompute_tree)
        {
            bvh::clear_tree(*bvh::tree);
            delete bvh::tree;
            bvh::tree = nullptr;
            recompute_tree = false;
        }

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