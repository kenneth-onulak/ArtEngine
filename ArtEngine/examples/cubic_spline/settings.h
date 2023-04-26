#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

// camera data
glm::vec3 pos = glm::vec3(1);
glm::vec3 up = glm::vec3(0, 1, 0);
glm::vec3 xz = glm::vec3(1, 0, 1);
glm::vec3 look = glm::vec3(0, 1, 0);
glm::mat4 proj;
glm::mat4 view;
float scale = 8.5f;

// cubic spline data
bool draw_polygonal_line = true;
bool draw_control_points = true;
std::deque<glm::vec3> control_points;
int constexpr line_points = 400;
std::vector<glm::vec3> curve_points(line_points);

// plot data
ImPlotFlags plot_flags = ImPlotFlags_NoLegend |                         //
                         ImPlotFlags_NoMenus |                          //
                         ImPlotFlags_NoBoxSelect |                      //
                         ImPlotFlags_NoMouseText;                       //
ImPlotDragToolFlags drag_flags = ImPlotDragToolFlags_Delayed;           // drag point flags
ImPlotAxisFlags axis_flags = ImPlotAxisFlags_NoTickLabels |             //
                             ImPlotAxisFlags_NoSideSwitch |             //
                             ImPlotAxisFlags_NoHighlight |              //
                             ImPlotAxisFlags_Lock |                     //
                             ImPlotAxisFlags_NoTickMarks;               //
ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_CollapsingHeader | //
                                  ImGuiTreeNodeFlags_DefaultOpen;       //
static double constexpr x_min = -50;
static double constexpr x_max = 50;
static double constexpr y_min = -50;
static double constexpr y_max = 50;

namespace ImPlot
{

bool DragControlPoint(int n_id, float *x, float *y, const ImVec4 &col, float radius, ImGuiMouseButton button,
                      ImPlotDragToolFlags flags, bool draw)
{
    ImGui::PushID("#IMPLOT_DRAG_POINT");
    IM_ASSERT_USER_ERROR(GImPlot->CurrentPlot != nullptr,
                         "DragControlPoint() needs to be called between BeginPlot() and EndPlot()!");
    SetupLock();

    if (!ImHasFlag(flags, ImPlotDragToolFlags_NoFit) && FitThisFrame())
    {
        FitPoint(ImPlotPoint(*x, *y));
    }

    const bool input = !ImHasFlag(flags, ImPlotDragToolFlags_NoInputs);
    const bool show_curs = !ImHasFlag(flags, ImPlotDragToolFlags_NoCursors);
    const bool no_delay = !ImHasFlag(flags, ImPlotDragToolFlags_Delayed);
    const float grab_half_size = ImMax(4.0f, radius);
    const ImVec4 color = IsColorAuto(col) ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : col;
    const ImU32 col32 = ImGui::ColorConvertFloat4ToU32(color);

    ImVec2 pos = PlotToPixels(*x, *y, IMPLOT_AUTO, IMPLOT_AUTO);
    const ImGuiID id = ImGui::GetCurrentWindow()->GetID(n_id);
    ImRect rect(pos.x - grab_half_size, pos.y - grab_half_size, pos.x + grab_half_size, pos.y + grab_half_size);
    bool hovered = false, held = false;

    ImGui::KeepAliveID(id);
    if (input)
        ImGui::ButtonBehavior(rect, id, &hovered, &held);

    bool dragging = false;
    if (held && ImGui::IsMouseDragging(button))
    {
        *x = static_cast<float>(ImPlot::GetPlotMousePos(IMPLOT_AUTO, IMPLOT_AUTO).x);
        *y = static_cast<float>(ImPlot::GetPlotMousePos(IMPLOT_AUTO, IMPLOT_AUTO).y);
        dragging = true;
    }

    ImDrawList &DrawList = *GetPlotDrawList();
    if ((hovered || held) && show_curs)
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    if (dragging && no_delay)
        pos = PlotToPixels(*x, *y, IMPLOT_AUTO, IMPLOT_AUTO);
    // fill control point on hover
    if (hovered)
        DrawList.AddCircleFilled(pos, radius / 2,
                                 ImGui::ColorConvertFloat4ToU32(ImVec4(color.x, color.y, color.z, color.w)));
    // draw the control point outline
    if (draw || hovered)
        DrawList.AddCircle(pos, radius, col32, 0, 1);
    // draw an open diamond
    // DrawList.AddNgon(pos, radius, col32, 4, 2);

    ImGui::PopID();
    return dragging;
}

} // namespace ImPlot

// compute matrices
void setup()
{
    proj = glm::ortho(-(float)Art::view.width() / scale, (float)Art::view.width() / scale,
                      -(float)Art::view.height() / scale, (float)Art::view.height() / scale, -50000.0f, 50000.0f);
    view = glm::lookAt(pos, look, up);
}

// Event Handler
std::function<void()> const eventHandler = []() {
    if (Art::event.key_down(SDLK_w))
        scale /= 0.99f;
    if (Art::event.key_down(SDLK_a))
        pos = glm::rotate(glm::mat4(1), -glm::radians(0.75f), up) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_s))
        scale *= 0.99f;
    if (Art::event.key_down(SDLK_d))
        pos = glm::rotate(glm::mat4(1), glm::radians(0.75f), up) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_LSHIFT))
        pos = glm::rotate(glm::mat4(1), -glm::radians(0.75f), glm::vec3(1, 1, 1)) * glm::vec4(pos, 1.0);
    if (Art::event.key_down(SDLK_SPACE))
        pos = glm::rotate(glm::mat4(1), glm::radians(0.75f), glm::vec3(1, 1, 1)) * glm::vec4(pos, 1.0);

    setup(); // recompute (I know this shouldn't be called all the time, whatever lol)
};

// interface function
Handle const interfaceFunc = []() {
    // window Size
    ImGui::SetNextWindowSize(ImVec2(350, 780), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);

    ImGui::Begin("Cubic Spline Controller", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::Spacing();
    ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::SmallButton("CLEAR"))
    {
        control_points.clear();
        draw_control_points = true;
        draw_polygonal_line = true;
        curve_points = std::vector<glm::vec3>(line_points);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // view
    ImGui::Checkbox("Draw Polygonal Line", &draw_polygonal_line);
    ImGui::Spacing();
    ImGui::Checkbox("Draw Control Points", &draw_control_points);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // controls
    ImGui::TextWrapped("WASD - rotate left/right and zoom");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // plots
    ImGui::TextWrapped("Left Click a plot to add control points");
    ImGui::TextWrapped("Left Click and drag a plotted control point to move it");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::BeginChild("##Plots", ImVec2(-1, -1));

    // xy plane
    if (ImGui::CollapsingHeader("XY Plane Plot", header_flags))
    {

        if (ImPlot::BeginPlot("##XY PLANE", ImVec2(300, 300), ImPlotFlags_CanvasOnly))
        {
            // setup
            ImPlot::SetupAxes("X", "Y", axis_flags, axis_flags);
            ImPlot::SetupAxesLimits(x_min, x_max, y_min, y_max);
            ImPlot::SetupFinish();

            // add points on left click
            if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                if (control_points.size() == 21) // degree 20 control points
                    control_points.pop_front();
                control_points.emplace_back(static_cast<float>(ImPlot::GetPlotMousePos().x),
                                            static_cast<float>(ImPlot::GetPlotMousePos().y),
                                            static_cast<float>(ImPlot::GetPlotMousePos().x));
            }

            // drag control points
            for (int i = 0; i < control_points.size(); ++i)
                ImPlot::DragControlPoint(i, &control_points[i].x, &control_points[i].y, ImVec4(0, 0.9f, 0, 1), 6,
                                         ImGuiMouseButton_Left, drag_flags, true);

            // x-axis and y-axis limits
            for (auto &p : control_points)
            {
                p.x = (p.x < x_min) ? static_cast<float>(x_min) : p.x;
                p.x = (p.x > x_max) ? static_cast<float>(x_max) : p.x;
                p.y = (p.y < y_min) ? static_cast<float>(y_min) : p.y;
                p.y = (p.y > y_max) ? static_cast<float>(y_max) : p.y;
            }

            // cleanup
            ImPlot::EndPlot();
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::CollapsingHeader("XZ Plane Plot", header_flags))
    {
        // xz plane
        if (ImPlot::BeginPlot("##XZ PLANE", ImVec2(300, 300), ImPlotFlags_CanvasOnly))
        {
            // setup
            ImPlot::SetupAxes("X", "Z", axis_flags, axis_flags);
            ImPlot::SetupAxesLimits(x_min, x_max, y_min, y_max);
            ImPlot::SetupFinish();

            // add points on left click
            if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                if (control_points.size() == 21) // degree 20 control points
                    control_points.pop_front();
                control_points.emplace_back(static_cast<float>(ImPlot::GetPlotMousePos().x),
                                            static_cast<float>(ImPlot::GetPlotMousePos().y),
                                            static_cast<float>(ImPlot::GetPlotMousePos().y));
            }

            // drag control points
            for (int i = 0; i < control_points.size(); ++i)
                ImPlot::DragControlPoint(i, &control_points[i].x, &control_points[i].z, ImVec4(0, 0.9f, 0, 1), 6,
                                         ImGuiMouseButton_Left, drag_flags, true);

            // x-axis and y-axis limits
            for (auto &p : control_points)
            {
                p.x = (p.x < x_min) ? static_cast<float>(x_min) : p.x;
                p.x = (p.x > x_max) ? static_cast<float>(x_max) : p.x;
                p.z = (p.z < y_min) ? static_cast<float>(y_min) : p.z;
                p.z = (p.z > y_max) ? static_cast<float>(y_max) : p.z;
            }

            // cleanup
            ImPlot::EndPlot();
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // yz plane
    if (ImGui::CollapsingHeader("YZ Plane Plot", header_flags))
    {
        // xz plane
        if (ImPlot::BeginPlot("##YZ PLANE", ImVec2(300, 300), ImPlotFlags_CanvasOnly))
        {
            // setup
            ImPlot::SetupAxes("Y", "Z", axis_flags, axis_flags);
            ImPlot::SetupAxesLimits(x_min, x_max, y_min, y_max);
            ImPlot::SetupFinish();

            // add points on left click
            if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                if (control_points.size() == 21) // degree 20 control points
                    control_points.pop_front();
                control_points.emplace_back(static_cast<float>(ImPlot::GetPlotMousePos().x),
                                            static_cast<float>(ImPlot::GetPlotMousePos().x),
                                            static_cast<float>(ImPlot::GetPlotMousePos().y));
            }

            // drag control points
            for (int i = 0; i < control_points.size(); ++i)
                ImPlot::DragControlPoint(i, &control_points[i].y, &control_points[i].z, ImVec4(0, 0.9f, 0, 1), 6,
                                         ImGuiMouseButton_Left, drag_flags, true);

            // x-axis and y-axis limits
            for (auto &p : control_points)
            {
                p.y = (p.y < x_min) ? static_cast<float>(x_min) : p.y;
                p.y = (p.y > x_max) ? static_cast<float>(x_max) : p.y;
                p.z = (p.z < y_min) ? static_cast<float>(y_min) : p.z;
                p.z = (p.z > y_max) ? static_cast<float>(y_max) : p.z;
            }

            // cleanup
            ImPlot::EndPlot();
        }
    }

    ImGui::EndChild();
    ImGui::End();
};
