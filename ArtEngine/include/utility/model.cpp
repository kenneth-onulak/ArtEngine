#include "../pch.h"

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
Model::Model(std::vector<std::string> binding, std::string name)
    : Model()
{
    for (auto const &b : binding)
    {
        bindings[b] = bindings.size();          // provide the named binding point an index
        glEnableVertexAttribArray(bindings[b]); // enable the binding point
    }
    this->name = name;
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
    : Model({"vert"}, "point")
    , vertex({0.0f, 0.0f, 0.0f}) // single (x, y, z) point
{
    bind<glm::vec3>("vert", &vertex);
    size = 1;
}

////////////////////////////////////////////////////////////////////////////////
//// TRIANGLE
////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle()
    : Model({"vert"}, "triangle")
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
    : Model({"in_Quad", "in_Tex"}, "square_2D")
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
    : Model({"in_Quad", "in_Text"}, "square_3D")
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
    : Model({"in_Quad", "in_Tex"}, "cube")
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
    : Model({"in_Quad", "in_Tex"}, "gizmo")
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

Icosphere::Icosphere(float radius, int subdivisions)
    : Model({"in_Position"}, "icosphere")
    , radius(radius)
    , subdivision(subdivisions)
{
    build();
    subdivide();

    bind<glm::vec3>("in_Position", new Buffer(vertices), true);
    index(new Buffer(std::vector<glm::uvec3>(indices.begin(), indices.end())));
    size = indices.size() * 3;
}

std::vector<float> Icosphere::compute_vertices() const
{
    static float constexpr pi = std::numbers::pi_v<float>;
    static float constexpr h_angle = pi / 180 * 72; // 72 degree = 360 / 5;
    static float const v_angle = atanf(1.0f / 2);   // elevation = 26.565 degree

    // compute once and reuse inside the loop
    static float const cos_v_angle = cosf(v_angle);
    static float const sin_v_angle = sinf(v_angle);

    std::vector<float> v(12 * 3);            // space for 12 vertices (x, y, z)
    int row_2, row_3;                        // indices
    float z, xy;                             // coords
    float h_angle_1 = -pi / 2 - h_angle / 2; // start from -126 degree at 2nd row
    float h_angle_2 = -pi / 2;               // start from -90 degree at 3rd row

    // top vertex (0, 0, r)
    v[0] = 0;
    v[1] = 0;
    v[2] = radius;

    // 10 vertices between 2nd and 3rd row
    for (int i = 1; i <= 5; ++i)
    {
        row_2 = i * 3;
        row_3 = (i + 5) * 3;

        // elevation
        z = radius * sin_v_angle;
        xy = radius * cos_v_angle;

        // 2nd row
        v[row_2] = xy * cosf(h_angle_1);     // xy
        v[row_2 + 1] = xy * sinf(h_angle_1); // xy
        v[row_2 + 2] = z;                    // z
        // 3rd row
        v[row_3] = xy * cosf(h_angle_2);     // xy
        v[row_3 + 1] = xy * sinf(h_angle_2); // xy
        v[row_3 + 2] = -z;                   // z

        // next horizontal angles
        h_angle_1 += h_angle;
        h_angle_2 += h_angle;
    }

    // bottom vertex (0, 0, -r)
    int i = 11 * 3;
    v[i] = 0;
    v[i + 1] = 0;
    v[i + 2] = -radius;

    return v;
}

void Icosphere::add_vertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void Icosphere::add_vertices(float const v1[3], float const v2[3], float const v3[3])
{
    add_vertex(v1[0], v1[1], v1[2]);
    add_vertex(v2[0], v2[1], v2[2]);
    add_vertex(v3[0], v3[1], v3[2]);
}

void Icosphere::add_indices(unsigned i1, unsigned i2, unsigned i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

float Icosphere::compute_scale_for_length(const float v[3], float length)
{
    // and normalize the vector then re-scale to new radius
    return length / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void Icosphere::compute_half_vertex(float const v1[3], float const v2[3], float length, float new_v[3])
{
    new_v[0] = v1[0] + v2[0];
    new_v[1] = v1[1] + v2[1];
    new_v[2] = v1[2] + v2[2];
    float scale = compute_scale_for_length(new_v, length);
    new_v[0] *= scale;
    new_v[1] *= scale;
    new_v[2] *= scale;
}

void Icosphere::build()
{
    // compute the 12 vertices of an icosahedron
    vertices = compute_vertices();

    // create 20 triangles from the vertices
    // flat example of the icosahedron vertices and triangles
    //   00  00  00  00  00
    //   /\  /\  /\  /\  /\
    //  /  \/  \/  \/  \/  \
    // 01--02--03--04--05--01
    //  \  /\  /\  /\  /\  /\
    //   \/  \/  \/  \/  \/  \
    //   06--07--08--09--10--06
    //    \  /\  /\  /\  /\  /
    //     \/  \/  \/  \/  \/
    //     11  11  11  11  11

    // track the vertices for splitting
    // 1st row (5 triangles)
    add_indices(0, 1, 2);
    add_indices(0, 2, 3);
    add_indices(0, 3, 4);
    add_indices(0, 4, 5);
    add_indices(0, 5, 1);
    // 2nd row (10 triangles)
    add_indices(1, 6, 2);
    add_indices(2, 6, 7);
    add_indices(2, 7, 3);
    add_indices(3, 7, 8);
    add_indices(3, 8, 4);
    add_indices(4, 8, 9);
    add_indices(4, 9, 5);
    add_indices(5, 9, 10);
    add_indices(5, 10, 1);
    add_indices(1, 10, 6);
    // 3rd row (5 triangles)
    add_indices(6, 11, 7);
    add_indices(7, 11, 8);
    add_indices(8, 11, 9);
    add_indices(9, 11, 10);
    add_indices(10, 11, 6);
}

void Icosphere::subdivide()
{
    std::vector<float> temp_vertices;
    std::vector<unsigned> temp_indices;
    int index_count;

    float const *v1, *v2, *v3;             // pointer to original vertices of a triangle
    float new_v1[3], new_v2[3], new_v3[3]; // new vertex positions
    unsigned index;                        // new index value

    for (int i = 1; i <= subdivision; ++i)
    {
        // copy previous information
        temp_vertices = vertices;
        temp_indices = indices;

        // clear previous information
        vertices.clear();
        indices.clear();

        index = 0;
        index_count = static_cast<int>(temp_indices.size());

        for (int j = 0; j < index_count; j += 3)
        {
            // get 3 vertices and texture coordinates of a triangle
            v1 = &temp_vertices[temp_indices[j] * 3];
            v2 = &temp_vertices[temp_indices[j + 1] * 3];
            v3 = &temp_vertices[temp_indices[j + 2] * 3];

            // compute 3 new vertices by splitting half on each edge
            //           v1
            //          / \
            //   newV1 *---* newV3
            //        / \ / \
            //      v2---*---v3
            //         newV2

            // split each edge in half and get 3 new vertices
            compute_half_vertex(v1, v2, radius, new_v1);
            compute_half_vertex(v2, v3, radius, new_v2);
            compute_half_vertex(v1, v3, radius, new_v3);

            // add new vertices
            add_vertices(v1, new_v1, new_v3);
            add_vertices(v2, new_v2, v3);

            //          0
            //         / \
            //        1---2
            //       / \ / \
            //      3---4---5

            // add 4 new triangles
            add_indices(index + 0, index + 1, index + 2);
            add_indices(index + 1, index + 3, index + 4);
            add_indices(index + 1, index + 4, index + 2);
            add_indices(index + 4, index + 5, index + 2);

            // next index
            index += 6;
        }
    }
}