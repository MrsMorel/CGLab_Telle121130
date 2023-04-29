#include <utility>

#include "../include/GeometryNode.h"

GeometryNode::GeometryNode():
Node(){}

GeometryNode::~GeometryNode() = default;

model GeometryNode::getGeometry()
{
    return geometry;
}

void GeometryNode::setGeometry(model new_geometry)
{
    this->geometry = std::move(new_geometry);
}