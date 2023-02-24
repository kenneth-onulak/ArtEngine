#ifndef ARTENGINE_IAMGE_H
#define ARTENGINE_IAMGE_H

#include "../ArtEngine.h"

namespace image
{

SDL_Surface *load(std::string path);

void save(SDL_Surface *surface, std::string path);
void save(Target target, std::string path);

SDL_Surface *make(std::function<glm::vec4(int)> handle,
                  glm::vec2 size = glm::vec2(Art::view.width(), Art::view.height()));

glm::vec4 color(SDL_Surface *surface, int x, int y);
glm::vec4 color(SDL_Surface *surface, float x, float y);

} // namespace image

#endif // ARTENGINE_IAMGE_H
