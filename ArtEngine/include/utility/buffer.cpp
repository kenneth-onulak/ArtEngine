#include "pch.h"
#include "buffer.h"

Buffer::Buffer()
{
    glGenBuffers(1, &index);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &index);
}