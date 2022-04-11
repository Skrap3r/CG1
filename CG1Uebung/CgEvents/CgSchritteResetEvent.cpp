#include "CgSchritteResetEvent.h"

CgSchritteResetEvent::CgSchritteResetEvent(Cg::EventType type)
{
    m_type=type;
}

CgSchritteResetEvent::~CgSchritteResetEvent()
{

}

Cg::EventType CgSchritteResetEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgSchritteResetEvent::clone()
{
    return new CgSchritteResetEvent(m_type);
}
