#ifndef OPENGL_FRAMEWORK_CAMERANODE_H
#define OPENGL_FRAMEWORK_CAMERANODE_H
#include <glm/gtx/transform.hpp>
#include "Node.h"
/* for camera derived from node*/
class CameraNode: public Node{
public:
    //constructor and destructor
    CameraNode();
    ~CameraNode() override;
//getter and setter
    bool getPerspective();
    bool getEnabled();
    void setEnabled(bool isEnabled);
    glm::mat4 getProjectionMatrix();
    void setProjectionMatrix(glm::mat4 projectionMatrix);

private:
    bool isPerspective; //
    bool isEnabled; //is camera on?
    glm::mat4 projectionMatrix; //Projection matrix for transformation
};
#endif //OPENGL_FRAMEWORK_CAMERANODE_H