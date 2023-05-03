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
    //PointLightNode(const glm::vec3& position, const glm::vec3& lightColor, float lightIntensity);
    ~PointLightNode() override; //destructor
    
    //getter and setter
    float getLightIntensity() const;
    void setLightIntensity(float new_LightIntensity);
    glm::vec3 getLightColor() const;
    void setLightColor(const glm::vec3& new_LightColor);
    //void setPosition(const glm::vec3& position);
    //glm::vec3 getPosition() const;
    
private:
    float lightIntensity_{};
    glm::vec3 lightColor_;
    //glm::vec3 
};

#endif //OPENGL_FRAMEWORK_POINTLIGHTNODE_H
