#include "pch.h"
#include "target.h"

////////////////////////////////////////////////////////////////////////////////
//// TARGET
////////////////////////////////////////////////////////////////////////////////

Target::Target(int width, int height, bool color, bool depth)
    : m_width(width)
    , m_height(height)
    , m_depth_attach(depth)
    , m_color_attach(color)
{
    glGenFramebuffers(1, &m_fbo);
}

Target::~Target()
{
    glDeleteFramebuffers(1, &m_fbo);
}

void Target::target(bool use_depth)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
    if (use_depth && m_depth_attach)
        glClear(GL_DEPTH_BUFFER_BIT);
    if (use_depth && m_color_attach)
        glClear(GL_COLOR_BUFFER_BIT);
}

unsigned Target::width() const
{
    return m_width;
}

unsigned Target::height() const
{
    return m_height;
}

////////////////////////////////////////////////////////////////////////////////
//// BILLBOARD
////////////////////////////////////////////////////////////////////////////////

Billboard::Billboard(int width, int height, bool use_color, bool use_depth)
    : Target(width, height, use_color, use_depth)
{
    if (m_depth_attach)
        m_depth.depth(m_width, m_height);
    if (m_color_attach)
        m_texture.empty(m_width, m_height);
    setup(m_texture, m_depth);
}

Billboard::Billboard(SDL_Surface *surface)
    : Billboard(surface->w, surface->h, true, false)
{
    m_texture.raw(surface);
    bind(m_texture, false);
}

Texture Billboard::texture() const
{
    return m_texture;
}

Texture Billboard::depth() const
{
    return m_depth;
}

////////////////////////////////////////////////////////////////////////////////
//// CUBEMAP
////////////////////////////////////////////////////////////////////////////////

Cubemap::Cubemap(int width, int height, bool color, bool depth)
    : Target(width, height, color, depth)
{
    if (m_depth_attach)
        m_depth.depth(m_width, m_height);
    if (m_color_attach)
        m_texture.empty(m_width, m_height);
    setup(m_texture, m_depth);
}

Cubetexture Cubemap::texture() const
{
    return m_texture;
}

Cubetexture Cubemap::depth() const
{
    return m_depth;
}