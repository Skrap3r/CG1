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

    void render(CgBaseRenderer* renderer);
private:
    CgSceneGraphEntity* m_root;
    std::stack <glm::mat4> m_modleview_matrix_stack;

    void pushMatrix() {m_modleview_matrix_stack.push(m_modleview_matrix_stack.top());}
    void popMatrix() {m_modleview_matrix_stack.pop();}
    void applyTransform(glm::mat4 arg) {m_modleview_matrix_stack.top()*=arg;}
};

#endif // CGSCENEGRAPH_H
