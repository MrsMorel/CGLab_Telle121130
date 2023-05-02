#include <utility>

#include "../include/GeometryNode.h"
//default constructor
GeometryNode::GeometryNode():
Node(){}

GeometryNode::~GeometryNode() = default;
//getter
model GeometryNode::getGeometry()
{
    return geometry_;
}
//setter
void GeometryNode::setGeometry(model new_geometry)
{
    this->geometry_ = std::move(new_geometry);
}
//constructor with model
GeometryNode::GeometryNode(model geo):
Node(), geometry_{std::move(geo)}{}
