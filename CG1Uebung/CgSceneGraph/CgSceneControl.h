#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <vector>
#include "CgScenegraph.h"

class CgBaseEvent;
class CgBaseRenderer;
class CgExampleTriangle;
class CgDice;
class CgPolyline;
class CgRotation;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void renderObjects();

    void setCurrent_transformation(const glm::mat4 &current_transformation);
    void setCurrentMatrix();

    void iterate_graph(CgSceneGraphEntity* arg_child, glm::vec3 arg_color);

    void scale_obj(CgSceneGraphEntity* arg_entity, glm::vec3 arg_scale);
    void translate_obj(CgSceneGraphEntity* arg_entity, glm::vec3 arg_translation);
    void rotate_obj(CgSceneGraphEntity* arg_entity, glm::vec3 arg_rotation, float arg_angle);
private:
    CgExampleTriangle* m_triangle;
    CgBaseRenderer* m_renderer;
    CgDice* m_dice;
    CgPolyline* m_polyline;
    CgRotation* m_rotation;
    CgScenegraph* graph;
    CgSceneGraphEntity* e1;
    CgSceneGraphEntity* e2;
    CgSceneGraphEntity* e3;
    CgSceneGraphEntity* e4;

    CgSceneGraphEntity* current_Entity;

    std::vector<CgPolyline*> m_normalsRotation;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

    int count;
    glm::vec4 old_color;
};

#endif // CGSCENECONTROL_H
