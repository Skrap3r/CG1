#include "CgRotation.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include <iostream>

CgRotation::CgRotation():
    m_type(Cg::TriangleMesh),
    m_id(44)
{

}

CgRotation::CgRotation(int id, std::vector<glm::vec3> line_vertices, int segmente):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    int size_line = line_vertices.size();
    int size_vertices = segmente * (size_line+1);
    m_vertices.resize(size_vertices);

    float angle_per_segment = (2*M_PI)/segmente;
    glm::mat3x3 rotmat_y = glm::mat3x3(glm::vec3(cos(angle_per_segment), 0.0 , -1*sin(angle_per_segment)), glm::vec3(0.0, 1.0, 0.0), glm::vec3(sin(angle_per_segment), 0.0, cos(angle_per_segment)));

    for(int i = 0; i < size_line; i++)
    {
        m_vertices.push_back(line_vertices.at(i));
    }

    for(int i = 1; i < segmente+1; i++)
    {
        for(int j = i*size_line; j < i*size_line+size_line; j++)
        {
            m_vertices.push_back(m_vertices.at(j - size_line) * rotmat_y);
        }
    }
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
