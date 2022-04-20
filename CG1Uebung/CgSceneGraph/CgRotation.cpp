#include "CgRotation.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"

CgRotation::CgRotation():
    m_type(Cg::TriangleMesh),
    m_id(++nextID)
{

}

CgRotation::CgRotation(std::vector<glm::vec3> line_vertices, int segmente):
    m_type(Cg::TriangleMesh),
    m_id(++nextID),
    line_points_size(line_vertices.size())
{
    int size_line = line_vertices.size();

    float angle_per_segment = (2*M_PI)/segmente;
    glm::mat3x3 rotmat_y = glm::mat3x3(glm::vec3(cos(angle_per_segment), 0.0 , -1*sin(angle_per_segment)), glm::vec3(0.0, 1.0, 0.0), glm::vec3(sin(angle_per_segment), 0.0, cos(angle_per_segment)));

    //Kopiere die ersten Punkte ins Objekt
    for(int i = 0; i < size_line; i++)
    {
        m_vertices.push_back(line_vertices.at(i));
    }

    /*
    for(auto s : m_vertices)
    {
        std::cout << glm::to_string(s) << std::endl;
    }
    std::cout << std::endl;
    */

    //Berechen alle weitere Punkte und speichere im Objekt
    for(int i = 1; i < segmente+1; i++)
    {
        for(int j = i*size_line; j < i*size_line+size_line; j++)
        {
            m_vertices.push_back(m_vertices.at(j - size_line) * rotmat_y);
        }
    }

    /*
    for(auto s : m_vertices)
    {
        std::cout << glm::to_string(s) << std::endl;
    }
    */

    //Bilde Dreiecke gegen den Uhrzeigersinn
    for(int i = 0; i < m_vertices.size()-size_line; i++)
    {
        if((i+1)%size_line != 0){
            m_triangle_indices.push_back(i);
            m_triangle_indices.push_back(i+size_line);
            m_triangle_indices.push_back(i+1);
            m_triangle_indices.push_back(i+1);
            m_triangle_indices.push_back(i+size_line);
            m_triangle_indices.push_back(i+size_line+1);
        }
    }


    //std::cout << m_id << std::endl;
    //std::cout << m_vertices.size() << " " << m_triangle_indices.size() << std::endl;
}

CgRotation::~CgRotation()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgRotation::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgRotation::init( std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
}

void CgRotation::addFaceNormals(glm::vec3& normal)
{
    m_face_normals.push_back(normal);
}

const void CgRotation::calculateVertexNormals()
{
    m_vertex_normals.clear();
    m_face_normals.clear();
    calculateFaceNormals();
    glm::vec3 temp;
    float count;

    //std::cout << line_points_size << std::endl;
    for(int i = 0; i < m_vertices.size() - line_points_size; i++)
    {
        count = 0;
        temp = glm::vec3(0,0,0);
        for(int j = 0; j < m_triangle_indices.size(); j+=3)
        {
            if(m_triangle_indices.at(j) == i || m_triangle_indices.at(j+1) == i|| m_triangle_indices.at(j+2) == i)
            {
                temp += m_face_normals.at(j/3);
                count++;
            }
        }
        m_vertex_normals.push_back(temp/count);
    }
}

const void CgRotation::calculateFaceCenters()
{
    for(int i = 0; i < m_triangle_indices.size(); i+=3)
    {
        m_face_centers.push_back((m_vertices.at(m_triangle_indices.at(i)) + m_vertices.at(m_triangle_indices.at(i+1)) + m_vertices.at(m_triangle_indices.at(i+2)))/3.0f);
    }
}

const void CgRotation::calculateFaceNormals()
{
    glm::vec3 normal;
    for(int i = 0; i < m_triangle_indices.size(); i+=3)
    {
        normal = (glm::cross((m_vertices.at(m_triangle_indices.at(i)) - m_vertices.at(m_triangle_indices.at(i+1))) , (m_vertices.at(m_triangle_indices.at(i)) - m_vertices.at(m_triangle_indices.at(i+2)))));
        normal = (1/glm::length(normal)) * normal; //Normieren Länge = 1
        m_face_normals.push_back(normal);
    }
}

const std::vector<glm::vec3>& CgRotation::getFaceCenters() const
{
    return m_face_centers;
}

const std::vector<glm::vec3>& CgRotation::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgRotation::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgRotation::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2>& CgRotation:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgRotation::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgRotation::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgRotation::getFaceColors() const
{
    return m_face_colors;
}
