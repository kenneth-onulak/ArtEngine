#ifndef ARTENGINE_MODEL_H
#define ARTENGINE_MODEL_H

struct Model
{
    GLuint vao;      //!< vertex array
    size_t size = 0; //!< number of vertices

    std::unordered_map<std::string, int> bindings;     //!< binding points of attributes
    std::unordered_map<std::string, Buffer *> buffers; //!< owned buffers

    Model();
    ~Model();
    Model(std::vector<std::string> binding);

    template <typename T>
    void bind(std::string binding, Buffer *buffer, bool owned = false);

    GLuint idx;
    bool indexed = false;

    void index(Buffer *buffer, bool owned = false);

    glm::mat4 model = glm::mat4(1.0f); //!< model matrix

    void render(GLenum mode = GL_TRIANGLE_STRIP);

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

struct Icosphere : public Model
{
    std::vector<glm::vec3> positions;
    std::vector<glm::uvec3> indices;
    Buffer pos;
    Buffer ind;

    Icosphere();

    void build();
    void split();
    void sort();
};

#endif // ARTENGINE_MODEL_H
