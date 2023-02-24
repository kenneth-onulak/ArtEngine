#include "pch.h"
#include "model.h"

Model::Model()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

Model::~Model()
{
    glDisableVertexAttribArray(vao);
    glDeleteVertexArrays(1, &vao);
    // delete owned buffers
    for (auto const &b : buffers)
        delete b.second;
}

/*M+M***********************************************************************//*!
 \method:   Model::Model

 \summary:  non-default constructor to generate a model based on a list of
            defined bindings

 \args:     binding - defined list of bindings

 \modifies: [bindings]
 ************************************************************************//*M-M*/
Model::Model(std::vector<std::string> binding)
    : Model()
{
    for (auto const &b : binding)
    {
        bindings[b] = bindings.size();          // provide the named binding point an index
        glEnableVertexAttribArray(bindings[b]); // enable the binding point
    }
}

void Model::index(Buffer *buffer, bool owned)
{
    indexed = true;
    size = buffer->size;
    idx = buffer->index;
    if (owned)
        buffers["index"] = buffer;
}

void Model::render(GLenum mode)
{
    glBindVertexArray(vao);
    if (indexed)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx);
        glDrawElements(mode, size, GL_UNSIGNED_INT, 0);
    }
    else
        glDrawArrays(mode, 0, size);
}

////////////////////////////////////////////////////////////////////////////////
//// POINT
////////////////////////////////////////////////////////////////////////////////

Point::Point()
    : Model({"vert"})
    , vertex({0.0f, 0.0f, 0.0f}) // single (x, y, z) point
{
    bind<glm::vec3>("vert", &vertex);
    size = 1;
}

////////////////////////////////////////////////////////////////////////////////
//// TRIANGLE
////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle()
    : Model({"vert"})
    , vertex({1.0f, 0.0f, 0.0f, 0.0f,  // 0 - 4 (x, y, z, w) points
              0.0f, 1.0f, 0.0f, 0.0f,  // 1
              0.0f, 0.0f, 1.0f, 0.0f,  // 2
              1.0f, 0.0f, 0.0f, 0.0f}) // 3

{
    bind<glm::vec4>("vert", &vertex);
    size = 4;
}

////////////////////////////////////////////////////////////////////////////////
//// SQUARE2D
////////////////////////////////////////////////////////////////////////////////

Square2D::Square2D()
    : Model({"in_Quad", "in_Tex"})
    , vertex({-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f}) // 4 (x, y) points
    , texture({0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f})    // 4 (x, y) points
{
    bind<glm::vec2>("in_Quad", &vertex);
    bind<glm::vec2>("in_Tex", &texture);
    size = 4;
}

////////////////////////////////////////////////////////////////////////////////
//// SQUARE3D
////////////////////////////////////////////////////////////////////////////////

Square3D::Square3D()
    : Model({"in_Quad", "in_Text"})
    , vertex({-1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f}) // 4 (x, y, z) points
    , texture({0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f})                            // 4 (x, y) points
{
    bind<glm::vec3>("in_Quad", &vertex);
    bind<glm::vec2>("in_Tex", &texture);
    size = 4;
}

////////////////////////////////////////////////////////////////////////////////
//// CUBE
////////////////////////////////////////////////////////////////////////////////

Cube::Cube()
    : Model({"in_Quad", "in_Tex"})
    , vertex({
          1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  // front 36 (x, y, z) points
          -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  //
          -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, // back
          1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, //
          -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, // left
          -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  //
          1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  // right
          1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, //
          -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, // top
          1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  //
          1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  // bottom
          -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f  //
      })
    , texture({0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f}) // 4 (x, y) points
{
    bind<glm::vec3>("in_Quad", &vertex);
    bind<glm::vec2>("in_Tex", &texture);
    size = 36;
}

////////////////////////////////////////////////////////////////////////////////
//// GIZMO
////////////////////////////////////////////////////////////////////////////////

Gizmo::Gizmo()
    : Model({"in_Quad", "in_Tex"})
    , vertex({0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 6 (x, y, z) points
              0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
              0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f})
    , texture({1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 4 (x, y, z) points
               0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //
               0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f})
{
    bind<glm::vec3>("in_Quad", &vertex);
    bind<glm::vec3>("in_Tex", &texture);
    size = 6;
}

////////////////////////////////////////////////////////////////////////////////
//// ICOSPHERE
////////////////////////////////////////////////////////////////////////////////

Icosphere::Icosphere()
    : Model({"in_Position", "in_Tex"})
{
    build();
    split();

    pos.fill(positions);
    ind.fill(indices);

    bind<glm::vec3>("in_Position", &pos);
    index(&ind);
    size = indices.size();
}

void Icosphere::build()
{
    const float r = 1.0f;
    const float a = 72.0f / 360.0f * 2.0f * std::numbers::pi_v<float>;

    // helper to add positions
    auto add_pos = [&](float a, float b, float c) { positions.emplace_back(a, b, c); };

    // helper to form triangle indices
    auto triangle = [&](int a, int b, int c) { indices.emplace_back(a, b, c); };

    // top cap
    add_pos(0, r, 0);

    // top
    for (int i = 0; i < 5; ++i)
    {
        float x1 = r * cos(atan(0.5)) * cos(a * i);
        float y1 = r * cos(atan(0.5)) * sin(a * i);
        float z1 = r * sin(atan(0.5));
        add_pos(x1, z1, y1);
    }

    // bottom
    for (int i = 0; i < 5; ++i)
    {
        float x2 = r * cos(atan(0.5)) * cos(a * i + a / 2.0f);
        float y2 = r * cos(atan(0.5)) * sin(a * i + a / 2.0f);
        float z2 = -r * sin(atan(0.5));
        add_pos(x2, z2, y2);
    }

    // bottom cap
    add_pos(0, -r, 0);

    // top triangles
    triangle(1, 0, 2);
    triangle(2, 0, 3);
    triangle(3, 0, 4);
    triangle(4, 0, 5);
    triangle(5, 0, 1);

    // bottom triangles
    triangle(6, 7, 11);
    triangle(7, 8, 11);
    triangle(8, 9, 11);
    triangle(9, 10, 11);
    triangle(10, 6, 11);

    // connecting triangles (bottom)
    triangle(6, 2, 7);
    triangle(7, 3, 8);
    triangle(8, 4, 9);
    triangle(9, 5, 10);
    triangle(10, 1, 6);

    // connecting triangles (top)
    triangle(2, 3, 7);
    triangle(1, 2, 6);
    triangle(3, 4, 8);
    triangle(4, 5, 9);
    triangle(5, 1, 10);
}

void Icosphere::split()
{
    std::vector<glm::uvec3> new_indices;

    // helper to add positions
    auto add_pos = [&](glm::vec3 p) { positions.push_back(p); };

    // helper to form triangle indices
    auto triangle = [&](int a, int b, int c) { new_indices.emplace_back(a, b, c); };

    auto split_triangle = [&](int i) {
        // indices of the old triangle
        GLuint k1 = indices[i][0];
        GLuint k2 = indices[i][1];
        GLuint k3 = indices[i][2];

        // positions of the old triangle
        glm::vec3 a = positions[k1];
        glm::vec3 b = positions[k2];
        glm::vec3 c = positions[k3];

        // starting indices
        int const n_i = positions.size();

        // compute the split points
        glm::vec3 d = glm::normalize(0.5f * (a + b));
        glm::vec3 e = glm::normalize(0.5f * (b + c));
        glm::vec3 f = glm::normalize(0.5f * (c + a));

        // add new positions to the model
        add_pos(d);
        add_pos(e);
        add_pos(f);

        triangle(k1, n_i + 0, n_i + 2);
        triangle(k2, n_i + 1, n_i + 0);
        triangle(k3, n_i + 2, n_i + 1);
        triangle(n_i + 0, n_i + 1, n_i + 2);
    };

    for (size_t j = 0; j < 6; ++j)
    {
        new_indices.clear();
        // loop over old triangles
        for (int i = 0; i < indices.size(); ++i)
            split_triangle(i);
        indices = new_indices;
    }
}

void Icosphere::sort()
{
    std::sort(indices.begin(), indices.end(), [&](glm::uvec3 const &a, glm::uvec3 const &b) {
        glm::vec3 const ap =
            camera::view_projection * glm::vec4((positions[a.x] + positions[a.y] + positions[a.z]) / 3.0f, 1.0);
        glm::vec3 const bp =
            camera::view_projection * glm::vec4((positions[b.x] + positions[b.y] + positions[b.z]) / 3.0f, 1.0);
        return ap.z > bp.z;
    });
    ind.fill(indices);
}