//
// Created by xxann on 30.04.2023.
//
#include "PointLightNode.h"
PointLightNode::PointLightNode():
        Node(){}

PointLightNode::~PointLightNode() = default;

float PointLightNode::getLightIntensity() {
    return LightIntensity_;
}

void PointLightNode::setLightIntensity(float new_LightIntensity) {
    LightIntensity_ = new_LightIntensity;
}

glm::vec3 PointLightNode::getLightColor() {
    return LightColor_;
}

void PointLightNode::setLightColor(glm::vec3 new_LightColor) {
    LightColor_ = new_LightColor;
}
