#include <glm/gtx/transform.hpp>

class CameraNode()
{
public:
    CameraNode();
    virtual ~CameraNode();

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