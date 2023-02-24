#ifndef ARTENGINE_TEXTURE_H
#define ARTENGINE_TEXTURE_H

class Texture;
using tfunc = std::function<void(Texture *)>; //!< arbitrary function operating on texture pointer

////////////////////////////////////////////////////////////////////////////////
//// TEXTURE
////////////////////////////////////////////////////////////////////////////////

class Texture
{
  public:
    Texture();
    Texture(SDL_Surface *surface);
    Texture(int width, int height, bool use_depth = false);
    ~Texture();

    static tfunc parameter;

    void empty(int width, int height, tfunc param = parameter, GLenum format = GL_RGBA);
    void depth(int width, int height, tfunc param = parameter);
    void raw(SDL_Surface *surface, tfunc param = parameter);

    GLuint texture() const;
    GLenum type() const;

  protected:
    GLuint m_texture;              //!< texture location
    GLenum m_type = GL_TEXTURE_2D; //!< texture type

}; // class Texture

////////////////////////////////////////////////////////////////////////////////
//// CUBETEXTURE
////////////////////////////////////////////////////////////////////////////////

class Cubetexture : public Texture
{
  public:
    Cubetexture();
    Cubetexture(int width, int height, bool use_depth = false);

    void empty(int width, int height, tfunc param = parameter, GLenum format = GL_RGBA);
    void depth(int width, int height, tfunc param = parameter);

}; // class Cubetexture

#endif // ARTENGINE_TEXTURE_H
