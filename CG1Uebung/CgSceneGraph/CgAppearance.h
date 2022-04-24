#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include <glm/glm.hpp>

class CgAppearance
{
public:
    CgAppearance();

private:
    glm::vec3 object_color;
    glm::vec3 diffuse_matrix;
};

#endif // CGAPPEARANCE_H
