#include "CgSchritteAusfuehrenEvent.h"

CgSchritteAusfuehrenEvent::CgSchritteAusfuehrenEvent(Cg::EventType type, int schritte)
{
    m_type=type;
    m_schritte=schritte;
}

CgSchritteAusfuehrenEvent::~CgSchritteAusfuehrenEvent()
{

}

int CgSchritteAusfuehrenEvent::getSchritte()
{
    return m_schritte;
}

Cg::EventType CgSchritteAusfuehrenEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgSchritteAusfuehrenEvent::clone()
{
    return new CgSchritteAusfuehrenEvent(m_type, m_schritte);
}
