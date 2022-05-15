#include "CgTransaltionAusfuerenEvent.h"

CgTransaltionAusfuerenEvent::CgTransaltionAusfuerenEvent(Cg::EventType type, glm::vec3 arg_translation)
{
    m_type=type;
    m_translation = arg_translation;
}

CgTransaltionAusfuerenEvent::~CgTransaltionAusfuerenEvent()
{

}

glm::vec3 CgTransaltionAusfuerenEvent::getTranslation()
{
    return m_translation;
}

Cg::EventType CgTransaltionAusfuerenEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgTransaltionAusfuerenEvent::clone()
{
    return new CgTransaltionAusfuerenEvent(m_type, m_translation);
}
