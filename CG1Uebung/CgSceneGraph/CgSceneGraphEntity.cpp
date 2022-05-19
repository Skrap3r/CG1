#include "CgSceneGraphEntity.h"

CgSceneGraphEntity::CgSceneGraphEntity()
{
    m_current_transformation = glm::mat4(1.);
    m_appearance = *new CgAppearance();
}

CgSceneGraphEntity::CgSceneGraphEntity(CgSceneGraphEntity *arg_parent)
{
    m_parent = arg_parent;
    m_current_transformation = glm::mat4(1.);
    m_appearance = *new CgAppearance();
}

void CgSceneGraphEntity::calculateCenter()
{
    glm::vec3 center = glm::vec3(0,0,0);
    int count = 0;
    for(auto obj : list_of_objects)
    {
        for(auto vert: obj->getVertices())
        {
            center += vert;
            count++;
        }
    }
    m_center = center /glm::vec3(count);
}

void CgSceneGraphEntity::deleteLastChild()
{
    m_children.pop_back();
}

void CgSceneGraphEntity::deleteLastListOfObject()
{
    list_of_objects.pop_back();
}

void CgSceneGraphEntity::addChild(CgSceneGraphEntity* arg_child)
{
    m_children.push_back(arg_child);
}

void CgSceneGraphEntity::addListObject(CgBaseRenderableObject* arg_obj)
{
    list_of_objects.push_back(arg_obj);
}

std::vector<CgBaseRenderableObject *> CgSceneGraphEntity::getList_of_objects() const
{
    return list_of_objects;
}

void CgSceneGraphEntity::setList_of_objects(const std::vector<CgBaseRenderableObject *> &value)
{
    list_of_objects = value;
}

glm::mat4 CgSceneGraphEntity::getCurrent_transformation() const
{
    return m_current_transformation;
}

void CgSceneGraphEntity::setCurrent_transformation(const glm::mat4 &current_transformation)
{
    m_current_transformation = current_transformation;
}

CgAppearance& CgSceneGraphEntity::getAppearance()
{
    return m_appearance;
}

void CgSceneGraphEntity::setAppearance(const CgAppearance &appearance)
{
    m_appearance = appearance;
}

CgSceneGraphEntity *CgSceneGraphEntity::getParent() const
{
    return m_parent;
}

void CgSceneGraphEntity::setParent(CgSceneGraphEntity *parent)
{
    m_parent = parent;
}


std::vector<CgSceneGraphEntity *> CgSceneGraphEntity::getChildren() const
{
    return m_children;
}

void CgSceneGraphEntity::setChildren(const std::vector<CgSceneGraphEntity *> &children)
{
    m_children = children;
}

glm::vec3 CgSceneGraphEntity::getCenter() const
{
    return m_center;
}

void CgSceneGraphEntity::setCenter(const glm::vec3 &center)
{
    m_center = center;
}

std::string CgSceneGraphEntity::getName() const
{
    return m_name;
}

void CgSceneGraphEntity::setName(const std::string &name)
{
    m_name = name;
}

