#include "../pch.h"

namespace object
{

std::unordered_map<std::string, glm::vec3> materials(std::string file)
{
    std::unordered_map<std::string, glm::vec3> material;

    std::ifstream in(file + ".mtl", std::ios::in);
    if (!in.is_open())
    {
        std::cout << "Error: Failed to open file " << file << ".mtl" << std::endl;
        return material;
    }

    std::string line;
    std::string material_name;

    while (std::getline(in, line))
    {
        // ignore comments
        if (line[0] == '#')
            continue;

        if (line.substr(0, 6) == "newmtl")
            material_name = line.substr(7);
        else if (line.substr(0, 2) == "Kd")
        {
            float r;
            float g;
            float b;
            int n = sscanf_s(line.substr(3).c_str(), "%f %f %f\n", &r, &g, &b);
            if (n != 3)
                std::cout << "Error: Material Color Data was not read correctly." << std::endl;
            else
                material[material_name] = glm::vec3(r, g, b);
        }
    }
    in.close();

    return material;
}

Model *load(std::string file, glm::vec3 color)
{
    std::ifstream in(file + ".obj", std::ios::in);
    if (!in.is_open())
    {
        std::cout << "Error: Failed to open file " << file << ".obj" << std::endl;
        return nullptr;
    }

    std::unordered_map<std::string, glm::vec3> material = materials(file);

    std::vector<glm::vec3> vertex_buffer;
    std::vector<glm::vec3> normal_buffer;

    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> colors;

    bool vt = false;

    static float constexpr f_max = std::numeric_limits<float>::max();
    static float constexpr f_min = -f_max;

    // min max for aabb
    glm::vec3 min(f_max);
    glm::vec3 max(f_min);

    std::string line;
    while (std::getline(in, line))
    {
        // ignore comments
        if (line[0] == '#')
            continue;
        // ignore material file
        if (line.substr(0, 6) == "mtllib")
            continue;
        // ignore geometry name
        if (line[0] == 'o')
            continue;
        // vertex data
        else if (line.substr(0, 2) == "v ")
        {
            std::istringstream s(line.substr(2));
            glm::vec3 v;
            s >> v.x >> v.y >> v.z;
            vertex_buffer.push_back(v);

            // compute aabb extremes
            min.x = std::min(min.x, v.x);
            min.y = std::min(min.y, v.y);
            min.z = std::min(min.z, v.z);
            max.x = std::max(max.x, v.x);
            max.y = std::max(max.y, v.y);
            max.z = std::max(max.z, v.z);
        }
        // texture data - not handled
        else if (line.substr(0, 3) == "vt ")
            vt = true;
        // normal data
        else if (line.substr(0, 3) == "vn ")
        {
            std::istringstream s(line.substr(3));
            glm::vec3 n;
            s >> n.x >> n.y >> n.z;
            normal_buffer.push_back(n);
        }
        // color data
        else if (line.substr(0, 6) == "usemtl")
        {
            color = material[line.substr(7)];
            continue;
        }
        // map index information
        else if (line.substr(0, 2) == "f ")
        {
            unsigned vi[3];
            unsigned ui[3];
            unsigned ni[3];

            if (normal_buffer.empty() && !vt)
            {
                int n = sscanf_s(line.substr(2).c_str(), "%d %d %d", &vi[0], &vi[1], &vi[2]);
                if (n != 3)
                {
                    std::cout << "Error: Face data could not be read correctly." << std::endl;
                    return nullptr;
                }
            }
            else // parse face data normally
            {
                int n = sscanf_s(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", //
                                 &vi[0], &ui[0], &ni[0],                                 //
                                 &vi[1], &ui[1], &ni[1],                                 //
                                 &vi[2], &ui[2], &ni[2]);
                if (n != 9)
                {
                    n = sscanf_s(line.substr(2).c_str(), "%d//%d %d//%d %d//%d\n", //
                                 &vi[0], &ni[0],                                   //
                                 &vi[1], &ni[1],                                   //
                                 &vi[2], &ni[2]);
                    if (n != 6)
                    {
                        std::cout << "Error: Face data could not be read correctly." << std::endl;
                        return nullptr;
                    }
                }
            }
            // copy over vertices based on face data
            for (int i = 0; i < 3; ++i)
            {
                positions.push_back(vertex_buffer[vi[i] - 1].x);
                positions.push_back(vertex_buffer[vi[i] - 1].y);
                positions.push_back(vertex_buffer[vi[i] - 1].z);
            }
            // copy over normals based on face data
            if (!normals.empty() && !normal_buffer.empty())
            {
                for (int i = 0; i < 3; ++i)
                {
                    normals.push_back(normal_buffer[ni[i] - 1].x);
                    normals.push_back(normal_buffer[ni[i] - 1].y);
                    normals.push_back(normal_buffer[ni[i] - 1].z);
                }
            }
            else // no normals "vn" in file
            {    // construct normals based on vertices
                glm::vec3 const a = vertex_buffer[vi[0] - 1];
                glm::vec3 const b = vertex_buffer[vi[1] - 1];
                glm::vec3 const c = vertex_buffer[vi[2] - 1];
                glm::vec3 const n = glm::normalize(glm::cross(b - a, c - a));
                for (int i = 0; i < 3; ++i)
                {
                    normals.push_back(n.x);
                    normals.push_back(n.y);
                    normals.push_back(n.z);
                }
            }
            // copy over color
            for (int i = 0; i < 3; ++i)
            {
                colors.push_back(color.r);
                colors.push_back(color.g);
                colors.push_back(color.b);
                colors.push_back(1.0f);
            }
        }
    }

    in.close();

    // compute centroid sphere
    float distance = f_min;
    glm::vec3 center((max + min) * 0.5f);
    for (auto const & v : vertex_buffer)
    {
        float d = glm::distance(center, v);
        distance = std::max(distance, d);
    }

    // construct the model from the buffer data
    Model *model = new Model({"in_Position", "in_Normal", "in_Color"}, file);
    model->bind<glm::vec3>("in_Position", new Buffer(positions), true);
    model->bind<glm::vec3>("in_Normal", new Buffer(normals), true);
    model->bind<glm::vec4>("in_Color", new Buffer(colors), true);
    model->size = positions.size() / 3;
    // construct aabb
    model->aabb.center = center;
    model->aabb.min = min;
    model->aabb.max = max;
    model->aabb.scale = max - center;
    model->aabb.model = model;
    // construct bounding sphere
    model->sphere.center = center;
    model->sphere.radius = distance;
    model->sphere.model = model;

    return model;
}

std::vector<Model *> load_all(std::string file, glm::vec3 color)
{
    std::ifstream in(file + ".txt", std::ios::in);
    if (!in.is_open())
    {
        std::cout << "Error: Failed to open file " << file << ".txt" << std::endl;
        return {};
    }

    std::vector<Model *> models;
    std::string line;

    while (std::getline(in, line))
    {
        // append the object folder if trying to load a model without it
        if (line.substr(0, 7) != "object/")
            line = "object/" + line;
        // load and save the model
        Model *model = load(line.substr(0, line.length() - 4), color);
        if (!model)
            continue;
        models.push_back(model);
    }

    in.close();
    return models;
}

} // namespace object