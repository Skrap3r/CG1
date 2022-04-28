#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <vector>

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

private:
    CgExampleTriangle* m_triangle;
    CgBaseRenderer* m_renderer;
    CgDice* m_dice;
    CgPolyline* m_polyline;
    CgRotation* m_rotation;

    std::vector<CgPolyline*> m_normalsRotation;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;

};

#endif // CGSCENECONTROL_H
