#ifndef CGROTATIONSKOERPERERSTELLENEVENT_H
#define CGROTATIONSKOERPERERSTELLENEVENT_H

#include "../CgBase/CgBaseEvent.h"

class CgRotationskoerperErstellenEvent : public CgBaseEvent
{
public:
    CgRotationskoerperErstellenEvent(Cg::EventType type, int segmente);
    ~CgRotationskoerperErstellenEvent();

    Cg::EventType  getType();
    CgBaseEvent* clone();

    int getSegmente();

private:
    Cg::EventType m_type;
    int m_segmente;
};

#endif // CGROTATIONSKOERPERERSTELLENEVENT_H
