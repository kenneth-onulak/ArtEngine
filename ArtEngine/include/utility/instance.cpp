#include "pch.h"
#include "instance.h"

Instance::Instance(Model *model)
    : m_model(model)
{
}

void Instance::render(GLenum mode, int size)
{
    glBindVertexArray(m_model->vao);
    if (m_model->indexed)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->idx);
        glDrawElementsInstanced(mode, m_model->size, GL_UNSIGNED_INT, 0, size);
    }
    else
        glDrawArraysInstanced(mode, 0, m_model->size, m_size);
}

void Instance::render(GLenum mode)
{
    render(mode, m_size);
}

size_t Instance::size() const
{
    return m_size;
}

void Instance::size(size_t size)
{
    m_size = size;
}