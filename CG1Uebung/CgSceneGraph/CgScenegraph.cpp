#include "CgScenegraph.h"

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

}

void CgScenegraph::render(CgSceneGraphEntity *arg_child, glm::mat4 arg_mat)
{
    for(int i = 0; i < arg_child->getList_of_objects().size(); i++)
    {

    }

    for(int i = 0; arg_child->getChildren().size(); i++)
    {
        render(arg_child->getChildren().at(i), m_modleview_matrix_stack.top());
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
