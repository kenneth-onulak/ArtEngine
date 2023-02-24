#ifndef ARTENGINE_INSTANCE_H
#define ARTENGINE_INSTANCE_H

class Instance
{
  public:
    Instance(Model *model);

    template <typename T>
    void bind(std::string name, Buffer *buffer);
    template <typename T>
    void configure(Buffer *buffer);

    void render(GLenum mode = GL_TRIANGLE_STRIP);
    void render(GLenum mode, int size);

    size_t size() const;
    void size(size_t size);

  private:
    Model *m_model;                                   //!< model pointer
    std::unordered_map<std::string, int> m_instances; //!< binding points of attributes
    size_t m_size;                                    //!< number of instances

}; // class Instance

template <typename T>
void Instance::bind(std::string name, Buffer *buffer)
{
    m_size = buffer->size;
    glBindVertexArray(m_model->vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->index);
    configure<T>(buffer);
    m_instances[name] = buffer->index;
}

template <typename T>
void Instance::configure(Buffer *buffer)
{
    glEnableVertexAttribArray(m_model->bindings.size() + m_instances.size());
    glVertexAttribPointer(m_model->bindings.size() + m_instances.size(), sizeof(T) / sizeof(GLfloat), GL_FLOAT,
                          GL_FALSE, 0, (void *)0);
    glVertexAttribDivisor(m_model->bindings.size() + m_instances.size(), 1);
}

template <>
inline void Instance::configure<glm::mat4>(Buffer *buffer)
{
    for (int i = 0; i < 4; ++i)
    {
        glEnableVertexAttribArray(m_model->bindings.size() + m_instances.size() + i);
        glVertexAttribPointer(m_model->bindings.size() + m_instances.size() + i, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(i * sizeof(glm::vec4)));
        glVertexAttribDivisor(m_model->bindings.size() + m_instances.size() + i, 1);
    }
}

#endif // ARTENGINE_INSTANCE_H
