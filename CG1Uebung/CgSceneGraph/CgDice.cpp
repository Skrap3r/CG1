#include "CgDice.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include "CgPolyline.h"
#include <iostream>

CgDice::CgDice():
    m_type(Cg::TriangleMesh),
    m_id(42)
{
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.5,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
}

CgDice::CgDice(int id):
    m_type(Cg::TriangleMesh),
    m_id(id)
{
    m_vertices.push_back(glm::vec3(-0.5,-0.5,-0.5));
    m_vertices.push_back(glm::vec3(-0.5,0.5,-0.5));
    m_vertices.push_back(glm::vec3(0.5,0.5,-0.5));
    m_vertices.push_back(glm::vec3(0.5,-0.5,-0.5));

    m_vertices.push_back(glm::vec3(-0.5,-0.5,0.5));
    m_vertices.push_back(glm::vec3(-0.5,0.5,0.5));
    m_vertices.push_back(glm::vec3(0.5,0.5,0.5));
    m_vertices.push_back(glm::vec3(0.5,-0.5,0.5));

    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(0);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);

    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(7);

    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(5);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,-1.0));

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));


}

void CgDice::calculate_normals(void)
{
    //normalen Zeichnen
    glm::vec3 schwerpunkt;
    glm::vec3 normal;
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;

    for(int i = 0; i < getTriangleIndices().size(); i+=3){
        a = m_vertices.at(m_triangle_indices.at(i));
        b = m_vertices.at(m_triangle_indices.at(i+1));
        c = m_vertices.at(m_triangle_indices.at(i+2));

        schwerpunkt = (a + b + c)/glm::vec3(3.0,3.0,3.0);

        normal = (glm::cross((a-b), (a-c)));
        normal = (1/glm::length(normal)) * normal;

        std::vector<glm::vec3> temp;
        temp.push_back(schwerpunkt);
        temp.push_back(normal + schwerpunkt);

        m_normals.push_back(new CgPolyline(i, temp));
    }
}

CgDice::~CgDice()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgDice::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgDice::init( std::string filename)
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
const std::vector<CgPolyline*>& CgDice::getNormals() const
{
    return m_normals;
}

const std::vector<glm::vec3>& CgDice::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgDice::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgDice::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2>& CgDice:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgDice::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgDice::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgDice::getFaceColors() const
{
    return m_face_colors;
}
