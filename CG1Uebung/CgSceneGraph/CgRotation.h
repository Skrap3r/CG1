#ifndef CGROTATION_H
#define CGROTATION_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "../CgBase/CgBaseTriangleMesh.h"

class CgRotation : public CgBaseTriangleMesh
{
public:
    CgRotation();
    CgRotation(std::vector<glm::vec3> line_vertices, int segmente);
    ~CgRotation();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    void init (std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices);
    void init( std::string filename);

    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec3>& getFaceCenters() const;

    void addFaceNormals(glm::vec3&);

    void calculateFaceNormals();
    void calculateFaceCenters();
    void calculateVertexNormals();

    const std::vector<glm::vec2>& getVertexTexCoords() const;

    // ein Dreieck hat immer 3 Indices, also ist die Index-Liste 3 mal so lang wie die Anzahl der Dreiecke
    const std::vector<unsigned int>& getTriangleIndices() const;

    // Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
    const std::vector<glm::vec3>& getFaceNormals() const;

    // Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau dieser Farbe, also auch #Farben=#Faces
    const std::vector<glm::vec3>& getFaceColors() const;


private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_centers;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;

    int line_points_size;
};

inline Cg::ObjectType  CgRotation::getType() const {return m_type;}
inline unsigned int CgRotation::getID() const {return m_id;}

#endif // CGROTATION_H
