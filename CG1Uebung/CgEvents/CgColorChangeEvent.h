#ifndef CGCOLORCHANGEEVENT_H
#define CGCOLORCHANGEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include <iostream>

class CgColorChangeEvent : public CgBaseEvent
{
public:
    CgColorChangeEvent(Cg::EventType type, int red, int green, int blue);
    ~CgColorChangeEvent();

    Cg::EventType  getType();
    CgBaseEvent* clone();

    int red();
    int blue();
    int green();

private:
    Cg::EventType m_type;
    int m_red;
    int m_green;
    int m_blue;
};

#endif // CGCOLORCHANGEEVENT_H
