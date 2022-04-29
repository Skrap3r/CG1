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

    for(auto obj : arg_child->getList_of_objects())
    {
        renderer->render(obj);
        std::cout << obj->getType() << std::endl;
    }



    for(auto ent : arg_child->getChildren())
    {
        pushMatrix();
        render(renderer, ent);
        popMatrix();
    }
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
