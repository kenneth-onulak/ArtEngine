#ifndef ARTENGINE_BOUNDING_VOLUME_H
#define ARTENGINE_BOUNDING_VOLUME_H

class Model;

struct AABB
{
    enum class bb_type
    {
        aabb,
        obb
    };

    AABB() = default;
    AABB(glm::vec3 min, glm::vec3 max, bb_type type = bb_type::aabb);

    void compute(bb_type t);
    std::pair<float, float> get_extents(std::string axis);

    glm::vec3 min;                //!< min point position
    glm::vec3 max;                //!< max point position
    glm::vec3 center;             //!< center position
    glm::vec3 scale;              //!< vector pointing to max from center (half-extents)
    glm::mat4 T = glm::mat4(1);   //!< rotation matrix used for OBB
    bb_type type = bb_type::aabb; //!< current type of bounding box
    bool is_dirty = false;        //!< recompute when dirty

    Model *model = nullptr; //!< pointer to the model to access vertex info
  private:
    void aabb(std::vector<glm::vec3> const &v);
    void obb(std::vector<glm::vec3> const &v);

}; // struct AABB

struct Sphere
{
    enum class sphere_type
    {
        centroid,
        ritter,
        larsson6,
        larsson14,
        larsson26,
        larsson98,
        pca,
        ellipsoid
    };

    Sphere() = default;
    Sphere(glm::vec3 center, float radius, sphere_type type = sphere_type::centroid);

    void compute(sphere_type t);
    std::pair<float, float> get_extents(std::string axis);

    sphere_type type = sphere_type::centroid; //!< current type of sphere
    glm::vec3 center;                         //!< center position
    glm::vec3 scale;                          //!< used for ellipsoid only
    float radius;                             //!< radius
    bool is_dirty = false;                    //!< recompute when dirty

    Model *model = nullptr; //!< pointer to the model to access vertex info

  private:
    void enclose(glm::vec3 p);
    std::pair<glm::vec3, glm::vec3> extreme_points_along_direction(glm::vec3 d, std::vector<glm::vec3> const &v);
    std::pair<glm::vec3, glm::vec3> extreme_points_along_xyz(std::vector<glm::vec3> const &v);

    void centroid(std::vector<glm::vec3> const &v);
    void ritter(std::vector<glm::vec3> const &v);
    void larsson(std::vector<glm::vec3> const &v);
    void pca(std::vector<glm::vec3> const &v);
    void ellipsoid(std::vector<glm::vec3> const &v);

}; // struct Sphere

#endif // ARTENGINE_BOUNDING_VOLUME_H
