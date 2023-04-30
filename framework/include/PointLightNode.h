//
// Created by xxann on 30.04.2023.
//

#ifndef OPENGL_FRAMEWORK_POINTLIGHTNODE_H
#define OPENGL_FRAMEWORK_POINTLIGHTNODE_H
#include "Node.h"

class PointLightNode: public Node {
public:
    PointLightNode();
    ~PointLightNode() override;
    float getLightIntensity();
    void setLightIntensity(float new_LightIntensity);
    glm::vec3 getLightColor();
    void setLightColor(glm::vec3 new_LightColor);
private:
    float LightIntensity_;
    glm::vec3 LightColor_;
};

#endif //OPENGL_FRAMEWORK_POINTLIGHTNODE_H
