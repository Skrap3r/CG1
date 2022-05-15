#ifndef CGLOKKOORDZEICHNENEVENT_H
#define CGLOKKOORDZEICHNENEVENT_H

#include "../CgBase/CgBaseEvent.h"

class CgLokKoordZeichnenEvent : public CgBaseEvent
{
public:
    CgLokKoordZeichnenEvent(Cg::EventType type, bool zeichnen);
    ~CgLokKoordZeichnenEvent();

    bool getZeichnen();

    Cg::EventType  getType();
    CgBaseEvent* clone();

private:
    Cg::EventType m_type;
    bool m_zeichnen;
};

#endif // CGLOKKOORDZEICHNENEVENT_H
