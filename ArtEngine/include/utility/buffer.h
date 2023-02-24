#ifndef ARTENGINE_BUFFER_H
#define ARTENGINE_BUFFER_H

struct Buffer
{
    GLuint index;
    size_t size;

    Buffer();
    ~Buffer();

    template <typename T>
    Buffer(std::vector<T> buffer);

    template <typename T>
    Buffer(std::initializer_list<T> buffer);

    template <typename T>
    Buffer(size_t size, T *data);

    template <typename T>
    void fill(size_t n, T *data);

    template <typename T>
    void fill(std::vector<T> buffer);

    template <typename T>
    void fill(T value);

    template <typename T>
    void retrieve(size_t n, T *data);

    template <typename T>
    void retrieve(std::vector<T> &buffer);

    template <typename T>
    void retrieve(T &value);

}; // struct buffer

template <typename T>
Buffer::Buffer(std::vector<T> buffer)
    : Buffer()
{
    fill(buffer);
}

template <typename T>
Buffer::Buffer(std::initializer_list<T> buffer)
    : Buffer()
{
    fill<T>(buffer);
}

template <typename T>
Buffer::Buffer(size_t size, T *data)
    : Buffer()
{
    fill(size, data);
}

template <typename T>
void Buffer::fill(size_t n, T *data)
{
    glBindBuffer(GL_ARRAY_BUFFER, index);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(T), data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    size = n;
}

template <typename T>
void Buffer::fill(std::vector<T> buffer)
{
    fill(buffer.size(), &buffer[0]);
}

template <typename T>
void Buffer::fill(T value)
{
    fill(1, &value);
}

template <typename T>
void Buffer::retrieve(size_t n, T *data)
{
    glBindBuffer(GL_ARRAY_BUFFER, index);
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, n * sizeof(T), data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <typename T>
void Buffer::retrieve(std::vector<T> &buffer)
{
    retrieve(buffer.size(), &buffer[0]);
}

template <typename T>
void Buffer::retrieve(T &value)
{
    retrieve(1, &value);
}

#endif // ARTENGINE_BUFFER_H
