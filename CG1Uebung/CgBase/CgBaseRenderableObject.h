#ifndef CGBASERENDERABLEOBJECT
#define CGBASERENDERABLEOBJECT


#include "CgBase/CgEnums.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>


class CgBaseRenderableObject
{

public:

    virtual ~CgBaseRenderableObject(){};


    virtual Cg::ObjectType getType() const  =0;
    virtual unsigned int getID() const  =0;

    virtual const std::vector<glm::vec3>& getVertices() const =0;

protected:
    static unsigned int nextID;
};

//int CgBaseRenderableObject::nextID = 0;

#endif // CGBASERENDERABLEOBJECT

