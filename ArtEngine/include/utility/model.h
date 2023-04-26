#ifndef ARTENGINE_MODEL_H
#define ARTENGINE_MODEL_H

struct Model
{
    Model();
    ~Model();
    Model(std::vector<std::string> binding, std::string name = "none");

    template <typename T>
    void bind(std::string binding, Buffer *buffer, bool owned = false);
    void index(Buffer *buffer, bool owned = false);
    void render(GLenum mode = GL_TRIANGLE_STRIP);

    GLuint vao; //!< vertex array
    GLuint idx;
    bool indexed = false;
    size_t size = 0;                                   //!< number of vertices
    glm::mat4 model = glm::mat4(1.0f);                 //!< model matrix
    std::unordered_map<std::string, int> bindings;     //!< binding points of attributes
    std::unordered_map<std::string, Buffer *> buffers; //!< owned buffers
    std::string name;                                  //!< model name

    std::vector<glm::vec4> color; //!< USED ONLY FOR BSP

    // boundary information
    AABB aabb{};
    Sphere sphere{};

}; // struct Model

template <typename T>
void Model::bind(std::string binding, Buffer *buffer, bool owned)
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->index);
    glBindVertexBuffer(bindings[binding], buffer->index, 0, sizeof(T));
    glVertexAttribFormat(bindings[binding], sizeof(T) / sizeof(GL_FLOAT), GL_FLOAT, GL_FALSE, 0);
    if (owned)
        buffers[binding] = buffer;
}

struct Point : public Model
{
    Buffer vertex;

    Point();
};

struct Line : public Model
{
    Buffer vertex;

    Line(glm::vec3 const &p0, glm::vec3 const &p1);
};

struct Triangle : public Model
{
    Buffer vertex;

    Triangle();
};

struct Square2D : public Model
{
    Buffer vertex;
    Buffer texture;

    Square2D();
};

struct Square3D : public Model
{
    Buffer vertex;
    Buffer texture;

    Square3D();
};

struct Cube : public Model
{
    Buffer vertex;
    Buffer texture;

    Cube();
};

struct Gizmo : public Model
{
    Buffer vertex;
    Buffer texture;

    Gizmo();
};

// Icosphere inspired by Song Ho
// source: https://www.songho.ca/opengl/gl_sphere.html
struct Icosphere : public Model
{
    Icosphere(float radius, int subdivisions);

  private:
    std::vector<float> compute_vertices() const;
    void add_vertex(float x, float y, float z);
    void add_vertices(float const v1[3], float const v2[3], float const v3[3]);
    void add_indices(unsigned i1, unsigned i2, unsigned i3);

    static float compute_scale_for_length(float const v[3], float length);
    static void compute_half_vertex(float const v1[3], float const v2[3], float length, float new_v[3]);

    void build();
    void subdivide();

    float radius;    //!< circumscribed radius
    int subdivision; //!< number of subdivisions

    std::vector<float> vertices;
    std::vector<unsigned> indices;
};

#endif // ARTENGINE_MODEL_H
