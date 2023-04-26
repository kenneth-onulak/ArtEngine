#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

// Camera Data
extern glm::vec3 pos;
extern glm::vec3 up;
extern glm::vec3 xz;
extern glm::vec3 look;
extern glm::mat4 proj;
extern glm::mat4 view;
extern float scale;

// Pointlight Data
extern float pointnear;
extern float pointfar;
extern std::vector<glm::mat4> views;
extern glm::mat4 pointproj;
extern glm::vec3 plightpos;
extern bool lightupdate;

// Pointlight Properties
extern bool on;
extern float lightcolor[3];
extern float brightness;
extern float attenuation[3];

// bounding volumes
extern bool use_single_bv;
extern bool use_aabb;
extern AABB::bb_type bb_type;
extern bool use_sphere;
extern Sphere::sphere_type sphere_type;
extern size_t model_index;
extern size_t model_size;

// color options
static std::array<glm::vec3, 7> const colors = {color::red,  color::orange,  color::yellow, color::lime,
                                                color::cyan, color::magenta, color::white};

// octree
extern bool use_octree;
// bsp
extern bool use_bsp;

extern bool needs_update;

// compute matrices
void setup();

// Event Handler
extern Handle eventHandler;

// interface function
extern Handle interfaceFunc;

glm::mat4 scale_matrix(float r);

glm::mat4 scale_matrix(glm::vec3 v);