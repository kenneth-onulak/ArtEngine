#ifndef ARTENGINE_TARGET_H
#define ARTENGINE_TARGET_H

class Target
{
  public:
    Target(int width, int height, bool color = false, bool depth = true);
    ~Target();

    template <typename T>
    void bind(T &texture, bool use_depth);
    template <typename T>
    void setup(T &color, T &depth);

    void target(bool use_depth = true);

    template <typename T>
    void target(T color);
    template <typename T>
    void sample(T *n, glm::vec2 p, glm::vec2 d, GLenum attach = GL_COLOR_BUFFER_BIT, GLenum format = GL_RGBA);

    unsigned int m_width;        //!< framebuffer width
    unsigned int m_height;       //!< framebuffer height
    bool m_depth_attach = false; //!< use depth attachment
    bool m_color_attach = true;  //!< use color attachment
    GLuint m_fbo;                //!< framebuffer object

}; // class Target

template <typename T>
void Target::bind(T &texture, bool use_depth)
{
    if (use_depth)
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture.m_texture, 0);
    else
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture.m_texture, 0);
}

template <typename T>
void Target::setup(T &color, T &depth)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    if (m_depth_attach)
        bind(depth, true);
    if (m_color_attach)
        bind(color, false);
    else // no color attachment, don't draw it
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Error: Framebuffer Incomplete." << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

template <typename T>
void Target::target(T color)
{
    glClearColor(color[0], color[1], color[2], 1.0f);
    target();
}

template <typename T>
void Target::sample(T *n, glm::vec2 p, glm::vec2 d, GLenum attach, GLenum format)
{
    // bounds check
    if (d.x <= 0 || d.y <= 0 || p.x + d.x > m_width || p.y + d.y > m_height)
        return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glReadBuffer(attach);
    glReadPixels(p.x, p.y, d.x, d.y, format, GL_UNSIGNED_BYTE, n);
}

////////////////////////////////////////////////////////////////////////////////
//// BILLBOARD
////////////////////////////////////////////////////////////////////////////////

class Billboard : public Target
{
  public:
    Billboard(int width, int height, bool use_color = true, bool use_depth = true);
    Billboard(SDL_Surface* surface);

    Texture m_texture;
    Texture m_depth;

}; // class Billboard

////////////////////////////////////////////////////////////////////////////////
//// CUBEMAP
////////////////////////////////////////////////////////////////////////////////

class Cubemap : public Target
{
  public:
    Cubemap(int width, int height, bool color = true, bool depth = true);

    Cubetexture m_texture;
    Cubetexture m_depth;

}; // class Cubemap

#endif // ARTENGINE_TARGET_H
