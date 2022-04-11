#ifndef CGSCHRITTERESETEVENT_H
#define CGSCHRITTERESETEVENT_H

#include "../CgBase/CgBaseEvent.h"

class CgSchritteResetEvent : public CgBaseEvent
{
public:
    CgSchritteResetEvent(Cg::EventType type);
    ~CgSchritteResetEvent();

    Cg::EventType  getType();
    CgBaseEvent* clone();

private:
    Cg::EventType m_type;
};

#endif // CGSCHRITTERESETEVENT_H
