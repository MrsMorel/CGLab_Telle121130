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