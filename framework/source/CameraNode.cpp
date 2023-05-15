#include "CameraNode.h"

CameraNode::CameraNode():
        Node(),
        projectionMatrix{}{}

CameraNode::~CameraNode() = default;

bool CameraNode::getPerspective()
{
    return isPerspective;
}

bool CameraNode::getEnabled()
{
    return isEnabled;
}

void CameraNode::setEnabled(bool isEnabled)
{
    isEnabled = true;
}

glm::mat4 CameraNode::getProjectionMatrix()
{
    return projectionMatrix;
}

void CameraNode::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    this->projectionMatrix = projectionMatrix;
}