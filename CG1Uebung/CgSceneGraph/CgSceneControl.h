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

    void Uebung05();
    void Uebung04();

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

    CgPolyline* m_localX;
    CgPolyline* m_localY;
    CgPolyline* m_localZ;

    CgScenegraph* graph;

    //Uebung 05 Schachscene
    CgSceneGraphEntity* root;
    CgSceneGraphEntity* root_table;
    CgSceneGraphEntity* root_chair;
    CgSceneGraphEntity* root_board;
    CgSceneGraphEntity* root_chest;

    CgSceneGraphEntity* tableplate;
    CgSceneGraphEntity* leg_1;
    CgSceneGraphEntity* leg_2;
    CgSceneGraphEntity* leg_3;
    CgSceneGraphEntity* leg_4;



    CgSceneGraphEntity* root1;
    CgSceneGraphEntity* root2;
    CgSceneGraphEntity* e1;
    CgSceneGraphEntity* e2;
    CgSceneGraphEntity* e3;
    CgSceneGraphEntity* e4;

    CgSceneGraphEntity* eX;
    CgSceneGraphEntity* eY;
    CgSceneGraphEntity* eZ;

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
