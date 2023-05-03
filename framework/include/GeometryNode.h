#ifndef OPENGL_FRAMEWORK_GEOMETRYNODE_H
#define OPENGL_FRAMEWORK_GEOMETRYNODE_H
#include "model.hpp"
#include "Node.h"

/* class for the geometry of a planet */
class GeometryNode: public Node
{
public:
    //constructor
    GeometryNode();
    GeometryNode(model geo);
    //constructor
    ~GeometryNode() override;
    //getter and setter
    model getGeometry();
    void setGeometry(model geometry);

private:
    model geometry_;
};
#endif //OPENGL_FRAMEWORK_GEOMETRYNODE_H