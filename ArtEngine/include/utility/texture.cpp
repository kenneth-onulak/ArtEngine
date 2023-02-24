#include "pch.h"
#include "texture.h"

////////////////////////////////////////////////////////////////////////////////
//// TEXTURE
////////////////////////////////////////////////////////////////////////////////

Texture::Texture()
{
    glGenTextures(1, &m_texture);
}

Texture::Texture(SDL_Surface * surface)
    : Texture()
{
    raw(surface);
}

Texture::Texture(int width, int height, bool use_depth)
    : Texture()
{
    if (!use_depth)
        empty(width, height);
    else
        depth(width, height);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

tfunc Texture::parameter = [](Texture *texture) {
    glTexParameteri(texture->m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texture->m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texture->m_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(texture->m_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(texture->m_type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
};

void Texture::empty(int width, int height, tfunc param, GLenum format)
{
    glBindTexture(m_type, m_texture);
    glTexImage2D(m_type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
    param(this);
}

void Texture::depth(int width, int height, tfunc param)
{
    empty(width, height, param, GL_DEPTH_COMPONENT);
}

void Texture::raw(SDL_Surface *surface, tfunc param)
{
    glBindTexture(m_type, m_texture);
    glTexImage2D(m_type, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    param(this);
    SDL_FreeSurface(surface);
}

GLuint Texture::texture() const
{
    return m_texture;
}

GLenum Texture::type() const
{
    return m_type;
}

////////////////////////////////////////////////////////////////////////////////
//// CUBETEXTURE
////////////////////////////////////////////////////////////////////////////////

Cubetexture::Cubetexture()
    : Texture()
{
    m_type = GL_TEXTURE_CUBE_MAP;
}

Cubetexture::Cubetexture(int width, int height, bool use_depth)
    : Cubetexture()
{
    if (!use_depth)
        empty(width, height);
    else
        depth(width, height);
}

void Cubetexture::empty(int width, int height, tfunc param, GLenum format)
{
    glBindTexture(m_type, m_texture);
    for (unsigned i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
    param(this);
}

void Cubetexture::depth(int width, int height, tfunc param)
{
    empty(width, height, param, GL_DEPTH_COMPONENT);
}