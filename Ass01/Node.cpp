#include "Node.h"

Node::Node()
{
}

Node::~Node() {}

Node *Node::getParent()
{
}

void Node::setParent(Node *node)
{
    parent = node;
}

Node *Node::getChildren(std::string name)
{
    this->name = name;
}

std::vector<Node *> Node::getChildrenList()
{
}

std::string Node::getName()
{
}

std::string Node::getPath()
{
}

int Node::getDepth()
{
}

glm::mat4 Node::getLocalTransform()
{
}

void Node::setLocalTransform(glm::mat4 localTransform)
{
    this->localTransform = localTransform;
}

glm::mat4 Node::getWorldTransform()
{
}

void Node::setWorldTransform(glm::mat4 worldTransform)
{
    this->worldTransform = worldTransform;
}

void Node::addChildren(Node *node)
{
}

Node *Node::removeChildren(std::string name)
{
    this->name = name;
}