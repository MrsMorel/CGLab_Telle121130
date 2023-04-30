//
// Created by xxann on 30.04.2023.
//

#ifndef OPENGL_FRAMEWORK_POINTLIGHTNODE_H
#define OPENGL_FRAMEWORK_POINTLIGHTNODE_H
#include "Node.h"

class PointLightNode: public Node {
public:
    PointLightNode();
    PointLightNode(const glm::vec3& lightColor);
    PointLightNode(const glm::vec3& lightColor, float lightIntensity);
    ~PointLightNode() override;
    float getLightIntensity() const;
    void setLightIntensity(float new_LightIntensity);
    glm::vec3 getLightColor() const;
    void setLightColor(const glm::vec3& new_LightColor);
private:
    float lightIntensity_{};
    glm::vec3 lightColor_;
};

#endif //OPENGL_FRAMEWORK_POINTLIGHTNODE_H
