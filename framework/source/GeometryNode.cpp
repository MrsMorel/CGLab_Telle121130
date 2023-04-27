#include "../include/GeometryNode.h"

GeometryNode::GeometryNode
{
}

GeometryNode::~GeometryNode() {}

model GeometryNode::getGeometry()
{
    return geometry;
}

void GeometryNode::setGeometry(model new_geometry)
{
    this->geometry = new_geometry;
}