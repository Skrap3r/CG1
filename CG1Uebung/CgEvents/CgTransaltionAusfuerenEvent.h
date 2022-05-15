#ifndef CGTRANSALTIONAUSFUERENEVENT_H
#define CGTRANSALTIONAUSFUERENEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include <glm/gtc/matrix_transform.hpp>

class CgTransaltionAusfuerenEvent : public CgBaseEvent
{
public:
    CgTransaltionAusfuerenEvent(Cg::EventType type, glm::vec3 arg_translation);
    ~CgTransaltionAusfuerenEvent();

    glm::vec3 getTranslation();

    Cg::EventType  getType();
    CgBaseEvent* clone();
private:
    Cg::EventType m_type;
    glm::vec3 m_translation;
};

#endif // CGTRANSALTIONAUSFUERENEVENT_H
