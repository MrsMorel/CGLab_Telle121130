//
// Created by xxann on 30.04.2023.
//

#ifndef OPENGL_FRAMEWORK_POINTLIGHTNODE_H
#define OPENGL_FRAMEWORK_POINTLIGHTNODE_H
#include "Node.h"

/* derived node class for a point light (sun) */
class PointLightNode: public Node {
public:
    //constructor
    PointLightNode();
    PointLightNode(const glm::vec3& lightColor);
    PointLightNode(const glm::vec3& lightColor, float lightIntensity); 
    //Do we need to add const glm::vec3 position
    ~PointLightNode() override; //destructor
    //getter and setter
    float getLightIntensity() const;
    void setLightIntensity(float new_LightIntensity);
    glm::vec3 getLightColor() const;
    void setLightColor(const glm::vec3& new_LightColor);
private:
    float lightIntensity_{};
    glm::vec3 lightColor_;
};

#endif //OPENGL_FRAMEWORK_POINTLIGHTNODE_H
