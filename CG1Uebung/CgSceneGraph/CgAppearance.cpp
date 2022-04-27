#include "CgAppearance.h"

CgAppearance::CgAppearance()
{
    object_color = glm::vec3(0.0,1.0,0.0);
    diffuse_matrix = glm::vec3(1,1,1);
}

CgAppearance::CgAppearance(glm::vec3 arg_color, glm::vec3 arg_diffMat)
{
    object_color = arg_color;
    diffuse_matrix = arg_diffMat;
}

glm::vec3 CgAppearance::getObject_color() const
{
    return object_color;
}

void CgAppearance::setObject_color(const glm::vec3 &value)
{
    object_color = value;
}

glm::vec3 CgAppearance::getDiffuse_matrix() const
{
    return diffuse_matrix;
}

void CgAppearance::setDiffuse_matrix(const glm::vec3 &value)
{
    diffuse_matrix = value;
}
