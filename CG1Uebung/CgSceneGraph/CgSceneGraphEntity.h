#ifndef CGSCENEGRAPHENTITY_H
#define CGSCENEGRAPHENTITY_H

#include <glm/glm.hpp>
#include <vector>
#include "CgBase/CgBaseRenderableObject.h"
#include "CgAppearance.h"

class CgSceneGraphEntity
{
public:
    CgSceneGraphEntity();
    CgSceneGraphEntity(CgSceneGraphEntity* arg_parent);

    //~CgSceneGraphEntity();

    void calculateCenter();

    void deleteLastChild();
    void deleteLastListOfObject();

    void addChild(CgSceneGraphEntity* arg_child);
    void addListObject(CgBaseRenderableObject* arg_obj);

    std::vector<CgBaseRenderableObject *> getList_of_objects() const;
    void setList_of_objects(const std::vector<CgBaseRenderableObject *> &value);

    glm::mat4 getCurrent_transformation() const;
    void setCurrent_transformation(const glm::mat4 &current_transformation);

    CgAppearance& getAppearance();
    void setAppearance(const CgAppearance &appearance);

    CgSceneGraphEntity *getParent() const;
    void setParent(CgSceneGraphEntity *parent);

    std::vector<CgSceneGraphEntity *> getChildren() const;
    void setChildren(const std::vector<CgSceneGraphEntity *> &children);

    glm::vec3 getCenter() const;
    void setCenter(const glm::vec3 &center);

private:
    std::vector<CgBaseRenderableObject*> list_of_objects;
    glm::mat4 m_current_transformation;

    CgAppearance m_appearance;

    glm::vec3 m_center;

    CgSceneGraphEntity* m_parent;
    std::vector<CgSceneGraphEntity*> m_children;
};

#endif // CGSCENEGRAPHENTITY_H
