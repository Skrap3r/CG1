#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include <stack>
#include <glm/glm.hpp>
#include "CgSceneGraphEntity.h"
#include "CgBase/CgBaseRenderer.h"

class CgScenegraph
{
public:
    CgScenegraph();
    CgScenegraph(CgSceneGraphEntity* arg_root);

    //~CgScenegraph();

    void render(CgBaseRenderer* renderer);
    void render(CgBaseRenderer* renderer, CgSceneGraphEntity* arg_child); //, glm::mat4 arg_mat

    CgSceneGraphEntity *getRoot() const;
    void setRoot(CgSceneGraphEntity *getRoot);

    std::stack<glm::mat4> GetModel_view_matrix_stack() const;
    void setModleview_matrix_stack(const std::stack<glm::mat4> &GetModel_view_matrix_stack);

private:
    CgSceneGraphEntity* m_root;
    std::stack <glm::mat4> m_modleview_matrix_stack;

    void pushMatrix() {m_modleview_matrix_stack.push(m_modleview_matrix_stack.top());}
    void popMatrix() {m_modleview_matrix_stack.pop();}
    void applyTransform(glm::mat4 arg) {m_modleview_matrix_stack.top()*=arg;}
};

#endif // CGSCENEGRAPH_H
