#include "model.hpp"
#include "Node.h"

class GeometryNode: public Node
{
public:
    GeometryNode();
    ~GeometryNode() override;

    model getGeometry();
    void setGeometry(model geometry);

private:
    model geometry;
};