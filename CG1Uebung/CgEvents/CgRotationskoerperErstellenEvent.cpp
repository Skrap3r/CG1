#include "CgRotationskoerperErstellenEvent.h"

CgRotationskoerperErstellenEvent::CgRotationskoerperErstellenEvent(Cg::EventType type, int segmente)
{
    m_type=type;
    m_segmente=segmente;
}

CgRotationskoerperErstellenEvent::~CgRotationskoerperErstellenEvent()
{

}

int CgRotationskoerperErstellenEvent::getSegmente()
{
    return m_segmente;
}

Cg::EventType CgRotationskoerperErstellenEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgRotationskoerperErstellenEvent::clone()
{
    return new CgRotationskoerperErstellenEvent(m_type, m_segmente);
}
