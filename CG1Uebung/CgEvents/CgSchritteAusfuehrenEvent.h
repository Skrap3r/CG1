#ifndef CGSCHRITTEAUSFUEHRENEVENT_H
#define CGSCHRITTEAUSFUEHRENEVENT_H

#include "../CgBase/CgBaseEvent.h"

class CgSchritteAusfuehrenEvent : public CgBaseEvent
{
public:
    CgSchritteAusfuehrenEvent(Cg::EventType type, int schritte);
    ~CgSchritteAusfuehrenEvent();

    Cg::EventType  getType();
    CgBaseEvent* clone();

    int getSchritte();

private:
    Cg::EventType m_type;
    int m_schritte;
};

#endif // CGSCHRITTEAUSFUEHRENEVENT_H
