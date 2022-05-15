#include "CgLokKoordZeichnenEvent.h"

CgLokKoordZeichnenEvent::CgLokKoordZeichnenEvent(Cg::EventType type, bool zeichnen)
{
    m_type=type;
    m_zeichnen=zeichnen;
}

CgLokKoordZeichnenEvent::~CgLokKoordZeichnenEvent()
{

}

bool CgLokKoordZeichnenEvent::getZeichnen()
{
    return m_zeichnen;
}

Cg::EventType CgLokKoordZeichnenEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgLokKoordZeichnenEvent::clone()
{
    return new CgLokKoordZeichnenEvent(m_type, m_zeichnen);
}
