#include <glm/gtx/transform.hpp>
#include "Node.h"

class CameraNode: public Node{
public:
    CameraNode();
    ~CameraNode() override;

    bool getPerspective();
    bool getEnabled();
    void setEnabled(bool isEnabled);
    glm::mat4 getProjectionMatrix();
    void setProjectionMatrix(glm::mat4 projectionMatrix);

private:
    bool isPerspective;
    bool isEnabled;
    glm::mat4 projectionMatrix;
};