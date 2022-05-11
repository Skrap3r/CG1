#include "CgScenegraph.h"
#include <iostream>

CgScenegraph::CgScenegraph()
{

}

CgScenegraph::CgScenegraph(CgSceneGraphEntity* arg_root)
{
    m_root = arg_root;
    m_modleview_matrix_stack.push(m_root->getCurrent_transformation());
}

void CgScenegraph::render(CgBaseRenderer *renderer)
{
    render(renderer, m_root);
}

void CgScenegraph::render(CgBaseRenderer* renderer, CgSceneGraphEntity *arg_child)
{
    applyTransform(arg_child->getCurrent_transformation());
    renderer->setUniformValue("modelviewMatrix", m_modleview_matrix_stack.top());
    renderer->setUniformValue("mycolor",glm::vec4(arg_child->getAppearance().getObject_color(),1.0));

    for(auto obj : arg_child->getList_of_objects())
    {
        if(obj != NULL)
        {
            renderer->render(obj);
            //std::cout << obj->getType() << std::endl;
        }
    }



    for(auto ent : arg_child->getChildren())
    {
        if(ent != NULL)
        {
            pushMatrix();
            render(renderer, ent);
            popMatrix();
        }
    }
}

void CgScenegraph::createListOfEntitys(CgSceneGraphEntity *arg_child)
{
    listOfEntitys.push_back(arg_child);

    for(auto ent : arg_child->getChildren())
    {
        if(ent != NULL)
        {
            createListOfEntitys(ent);
        }
    }
}

void CgScenegraph::clearListOfEntitys()
{
    listOfEntitys.clear();
}



CgSceneGraphEntity *CgScenegraph::getRoot() const
{
    return m_root;
}

void CgScenegraph::setRoot(CgSceneGraphEntity *root)
{
    m_root = root;
}

std::stack<glm::mat4> CgScenegraph::GetModel_view_matrix_stack() const
{
    return m_modleview_matrix_stack;
}

void CgScenegraph::setModleview_matrix_stack(const std::stack<glm::mat4> &modleview_matrix_stack)
{
    m_modleview_matrix_stack = modleview_matrix_stack;
}

std::vector<CgSceneGraphEntity *> CgScenegraph::getListOfEntitys() const
{
    return listOfEntitys;
}
