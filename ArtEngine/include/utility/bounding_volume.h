#ifndef ARTENGINE_BOUNDING_VOLUME_H
#define ARTENGINE_BOUNDING_VOLUME_H

class Model;

struct AABB
{
    AABB() = default;

    void compute();
    std::pair<float, float> get_extents(std::string axis);

    glm::vec3 min;         //!< min point position
    glm::vec3 max;         //!< max point position
    glm::vec3 center;      //!< center position
    glm::vec3 scale;       //!< vector pointing to max from center (half-extents)
    bool is_dirty = false; //!< recompute when dirty

    Model *model; //!< pointer to the model to access vertex info

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
    };

    Sphere() = default;

    void compute(sphere_type t);
    std::pair<float, float> get_extents(std::string axis);

    sphere_type type = sphere_type::centroid; //!< current type of sphere
    glm::vec3 center;                         //!< center position
    float radius;                             //!< radius
    bool is_dirty = false;                    //!< recompute when dirty

    Model *model; //!< pointer to the model to access vertex info

  private:
    void enclose(glm::vec3 p);
    std::pair<glm::vec3, glm::vec3> extreme_points_along_direction(glm::vec3 d, std::vector<glm::vec3> const &v);
    std::pair<glm::vec3, glm::vec3> extreme_points_along_xyz(std::vector<glm::vec3> const &v);
    glm::mat3 covariance_matrix(std::vector<glm::vec3> const &v);

    void centroid(std::vector<glm::vec3> const &v);
    void ritter(std::vector<glm::vec3> const &v);
    void symschur2(glm::mat3 const &m, int p, int q, float &s, float &c);
    void jacobi(glm::mat3 &m1, glm::mat3 &m2);
    void pca(std::vector<glm::vec3> const &v);
    void larsson(std::vector<glm::vec3> const &v);
}; // struct Sphere

#endif // ARTENGINE_BOUNDING_VOLUME_H
