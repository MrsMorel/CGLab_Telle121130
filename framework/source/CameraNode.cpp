#include "CameraNode.h"

CameraNode::CameraNode():
        Node(){}

CameraNode::~CameraNode() = default;

bool CameraNode::getPerspective()
{
}

bool CameraNode::getEnabled()
{
}

void CameraNode::setEnabled(bool isEnabled)
{
    isEnabled = true;
}

glm::mat4 CameraNode::getProjectionMatrix()
{
}

void CameraNode::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    this->projectionMatrix = projectionMatrix;
}