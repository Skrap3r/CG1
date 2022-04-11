#include "CgColorChangeEvent.h"
#include "glm/glm.hpp"

CgColorChangeEvent::CgColorChangeEvent(Cg::EventType type, int red, int green, int blue)
{
    m_type=type;
    m_red=red;
    m_green=green;
    m_blue=blue;
}

CgColorChangeEvent::~CgColorChangeEvent()
{

}

int CgColorChangeEvent::red()
{
    return m_red;
}
int CgColorChangeEvent::green()
{
    return m_green;
}
int CgColorChangeEvent::blue()
{
    return m_blue;
}

Cg::EventType CgColorChangeEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgColorChangeEvent::clone()
{
    return new CgColorChangeEvent(m_type, m_red, m_green, m_blue);
}
