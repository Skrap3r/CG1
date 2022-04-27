#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include <glm/glm.hpp>

class CgAppearance
{
public:
    CgAppearance();
    CgAppearance(glm::vec3 arg_color, glm::vec3 arg_diffMat);

    //~CgAppearance();

    glm::vec3 getObject_color() const;
    void setObject_color(const glm::vec3 &value);

    glm::vec3 getDiffuse_matrix() const;
    void setDiffuse_matrix(const glm::vec3 &value);

private:
    glm::vec3 object_color;
    glm::vec3 diffuse_matrix;
};

#endif // CGAPPEARANCE_H
