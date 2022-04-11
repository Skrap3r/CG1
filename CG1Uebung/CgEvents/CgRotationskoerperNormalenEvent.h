#ifndef CGROTATIONSKOERPERNORMALENEVENT_H
#define CGROTATIONSKOERPERNORMALENEVENT_H

#include "../CgBase/CgBaseEvent.h"

class CgRotationskoerperNormalenEvent : public CgBaseEvent
{
public:
    CgRotationskoerperNormalenEvent(Cg::EventType type, bool zeichnen);
    ~CgRotationskoerperNormalenEvent();

    bool getZeichnen();

    Cg::EventType  getType();
    CgBaseEvent* clone();

private:
    Cg::EventType m_type;
    bool m_zeichnen;
};

#endif // CGROTATIONSKOERPERNORMALENEVENT_H
