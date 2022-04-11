#include "CgSceneGraph/CgPolyline.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"

CgPolyline::CgPolyline():
    m_type(Cg::Polyline),
    m_id(44)
{
    m_vertices.push_back(glm::vec3(0.1,0.1,0.1));
    m_vertices.push_back(glm::vec3(-0.1,0.1,0.1));

    m_lineWidth = 1;
}

CgPolyline::CgPolyline(int id):
    m_type(Cg::Polyline),
    m_id(id)
{
    m_vertices.push_back(glm::vec3(0.1,0.1,0.1));
    m_vertices.push_back(glm::vec3(-0.1,0.1,0.1));
    m_vertices.push_back(glm::vec3(0.1,-0.1,0.1));

    m_lineWidth = 1;
}

CgPolyline::CgPolyline(int id, std::vector<glm::vec3> arg_verts):
    m_type(Cg::Polyline),
    m_id(id)
{
    m_vertices.push_back(arg_verts.at(0));
    m_vertices.push_back(arg_verts.at(1));

    m_lineWidth = 1;
}

void CgPolyline::startLaneRiesenfeldAlgo(int schritte)
{
    int old_size = m_vertices.size();
    int new_size = m_vertices.size() * 2;

    m_vertices.resize(new_size);

    for(int i = old_size - 1; i >= 0 ; i--)
    {
        m_vertices.at(i*2) = m_vertices.at(i);
        m_vertices.at(i*2+1) = m_vertices.at(i);
    }

    for(int i = 0; i < schritte; i++)
    {
        for(int j = 0; j < new_size; j++)
        {

        }
    }

    for(glm::vec3 s : m_vertices)
    {
        std::cout << glm::to_string(s) << std::endl;
    }
}

CgPolyline::~CgPolyline()
{
    m_vertices.clear();
}

glm::vec3 CgPolyline::getColor() const
{
    return m_color;
}

const std::vector<glm::vec3>& CgPolyline::getVertices() const
{
    return m_vertices;
}

unsigned int CgPolyline::getLineWidth() const
{
    return m_lineWidth;
}
