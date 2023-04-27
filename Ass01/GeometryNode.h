#include "../framework/include/model.hpp"

class GeometryNode
{
public:
    GeometryNode();
    virtual ~GeometryNode();

    model getGeometry();
    void setGeometry(model geometry);

private:
    model geometry;
};