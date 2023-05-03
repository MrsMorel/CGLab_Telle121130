//
// Created by anne on 30.04.2023.
//
#include "PointLightNode.h"
PointLightNode::PointLightNode():
        Node(){}

PointLightNode::~PointLightNode() = default;

float PointLightNode::getLightIntensity() const {
    return lightIntensity_;
}

void PointLightNode::setLightIntensity(float new_LightIntensity) {
    lightIntensity_ = new_LightIntensity;
}

glm::vec3 PointLightNode::getLightColor() const {
    return lightColor_;
}

void PointLightNode::setLightColor(const glm::vec3& new_LightColor) {
    lightColor_ = new_LightColor;
}


//void PointLightNode::setLightPosition(const glm::vec3& new_Position) {
    //position_ = new_Position;
//}

//glm::vec3 PointLightNode::getLightPosition() const {
    //return position_;
//}

PointLightNode::PointLightNode(const glm::vec3& lightColor):
lightColor_{lightColor}
{}

PointLightNode::PointLightNode(const glm::vec3& lightColor, float lightIntensity):
lightIntensity_{lightIntensity}, lightColor_{lightColor}{}
