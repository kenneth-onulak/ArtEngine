#include "../pch.h"

namespace image
{

SDL_Surface *load(std::string path)
{
    SDL_Surface *loaded = IMG_Load(path.c_str());
    if (!loaded)
        std::cout << "Error: Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError()
                  << std::endl;
    SDL_Surface *optimized = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(loaded);
    return optimized;
}

void save(SDL_Surface *surface, std::string path)
{
    IMG_SavePNG(surface, path.c_str());
}

void save(Target target, std::string path)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, target.m_width, target.m_height, 32, 0, 0, 0, 0);
    SDL_LockSurface(surface);

    target.sample(surface->pixels, glm::vec2(0), glm::vec2(target.m_width, target.m_height));
    SDL_UnlockSurface(surface);
    save(surface, path);

    delete surface;
}

SDL_Surface *make(std::function<glm::vec4(int)> handle, glm::vec2 size)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, size.x, size.y, 32, 0, 0, 0, 0);
    SDL_LockSurface(surface);

    unsigned char *image_raw = static_cast<unsigned char *>(surface->pixels);
    for (int i = 0; i < size.x * size.y; ++i)
    {
        glm::vec4 color = handle(i);
        *(image_raw + 4 * i) = static_cast<unsigned char>(255 * color.r);
        *(image_raw + 4 * i + 1) = static_cast<unsigned char>(255 * color.g);
        *(image_raw + 4 * i + 2) = static_cast<unsigned char>(255 * color.b);
        *(image_raw + 4 * i + 3) = static_cast<unsigned char>(255 * color.a);
    }

    SDL_UnlockSurface(surface);
    return surface;
}

glm::vec4 color(SDL_Surface *surface, int x, int y)
{
    // out of bounds checking
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
        return {0, 0, 0, 1};

    SDL_PixelFormat *format = surface->format;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    SDL_LockSurface(surface);
    Uint32 pixels = static_cast<Uint32 *>(surface->pixels)[y * surface->w + x];
    SDL_UnlockSurface(surface);

    r = static_cast<Uint8>(((pixels & format->Rmask) >> format->Rshift) << format->Rloss);
    g = static_cast<Uint8>(((pixels & format->Gmask) >> format->Gshift) << format->Gloss);
    b = static_cast<Uint8>(((pixels & format->Bmask) >> format->Bshift) << format->Bloss);
    a = static_cast<Uint8>(((pixels & format->Amask) >> format->Ashift) << format->Aloss);

    return {r, g, b, a};
}

glm::vec4 color(SDL_Surface *surface, float x, float y)
{
    return color(surface, static_cast<int>(x * surface->w), static_cast<int>(y * surface->h));
}

} // namespace image