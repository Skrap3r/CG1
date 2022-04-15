#include "CgSceneGraph/CgPolyline.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"

CgPolyline::CgPolyline():
    m_type(Cg::Polyline),
    m_id(++nextID)
{
    m_vertices.push_back(glm::vec3(0.5,1.0,0.0));
    m_vertices.push_back(glm::vec3(1.0,0.5,0));
    m_vertices.push_back(glm::vec3(1.0,-0.5,0));
    m_vertices.push_back(glm::vec3(0.5,-1.0,0.0));
    //m_vertices.push_back(glm::vec3(1.0,-1.5,0.0));

    m_lineWidth = 1;
    //std::cout << m_id << std::endl;
}

CgPolyline::CgPolyline(int id):
    m_type(Cg::Polyline),
    m_id(id)
{
    m_vertices.push_back(glm::vec3(0.5,1.0,0.0));
    m_vertices.push_back(glm::vec3(1.0,0.5,0));
    m_vertices.push_back(glm::vec3(1.0,-0.5,0));
    m_vertices.push_back(glm::vec3(0.5,-1.0,0.0));
    //m_vertices.push_back(glm::vec3(1.0,-1.5,0.0));

    m_lineWidth = 1;
    //std::cout << m_id << std::endl;
}

CgPolyline::CgPolyline(std::vector<glm::vec3> arg_verts):
    m_type(Cg::Polyline),
    m_id(++nextID)
{
    for(auto s : arg_verts)
    {
        m_vertices.push_back(s);
    }

    m_lineWidth = 1;
    //std::cout << m_id << std::endl;
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

    /*
    for(glm::vec3 s : m_vertices)
    {
        std::cout << glm::to_string(s) << std::endl;
    }
    std::cout << std::endl;
    */


    for(int i = 0; i < schritte; i++)
    {
        //std::cout << "Mittlungsschritt nr. " < i+1 << std::endl;
        for(int j = 0; j < new_size - 1; j++)
        {
            //std::cout << "Mitteln nr. " << j+1 << std::endl;
            m_vertices.at(j) = 0.5f*m_vertices.at(j) + 0.5f*m_vertices.at(j+1);
        }
        m_vertices.pop_back();
        new_size--;
    }


    /*
    for(glm::vec3 s : m_vertices)
    {
        std::cout << glm::to_string(s) << std::endl;
    }
    std::cout << std::endl << std::endl;
    */
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
