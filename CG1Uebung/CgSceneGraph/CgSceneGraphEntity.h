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

    const CgSceneGraphEntity& getParent() const;
    const std::vector<CgSceneGraphEntity*>& getChild() const;
    const CgAppearance& getApperance() const;
    const glm::mat4& getCurrentTransformation() const;
    const std::vector<CgBaseRenderableObject*>& getListOfObejcts() const;

    void deleteLastChild();
    void deleteLastListOfObject();

    void addChild(CgSceneGraphEntity arg_child);
    void addListObject(CgBaseRenderableObject& arg_obj);

//    void setParent(CgSceneGraphEntity& arg_parent);
//    void setTransformationMat(glm::mat4 arg_mat);

private:
    std::vector<CgBaseRenderableObject*> list_of_objects;
    glm::mat4 m_current_transformation;

    CgAppearance m_appearance;

    CgSceneGraphEntity* m_parent;
    std::vector<CgSceneGraphEntity*> m_children;
};

#endif // CGSCENEGRAPHENTITY_H
