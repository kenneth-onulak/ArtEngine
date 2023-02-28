#ifndef ARTENGINE_OBJECT_H
#define ARTENGINE_OBJECT_H

namespace object
{

std::unordered_map<std::string, glm::vec3> materials(std::string file);

Model * load(std::string file, glm::vec3 color = color::magenta);

std::vector<Model*> load_all(std::string file, glm::vec3 color = color::magenta);

}

#endif // ARTENGINE_OBJECT_H
