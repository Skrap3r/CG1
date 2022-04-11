#include "CgRotationskoerperNormalenEvent.h"

CgRotationskoerperNormalenEvent::CgRotationskoerperNormalenEvent(Cg::EventType type, bool zeichnen)
{
    m_type=type;
    m_zeichnen=zeichnen;
}

CgRotationskoerperNormalenEvent::~CgRotationskoerperNormalenEvent()
{

}

bool CgRotationskoerperNormalenEvent::getZeichnen()
{
    return m_zeichnen;
}

Cg::EventType CgRotationskoerperNormalenEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgRotationskoerperNormalenEvent::clone()
{
    return new CgRotationskoerperNormalenEvent(m_type, m_zeichnen);
}
