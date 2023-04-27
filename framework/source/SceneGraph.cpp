#include "../include/SceneGraph.h"

SceneGraph::SceneGraph(std::string name, Node *root)
{
    this->name = name;
    this->root = root;
}

SceneGraph::~SceneGraph() {}

std::string SceneGraph::getName()
{
}

void SceneGraph::setName(std::string name)
{
    this->name = name;
}

Node *SceneGraph::getRoot()
{
}

void SceneGraph::setRoot(Node *node)
{
    root = node;
}

std::string SceneGraph::printGraph()
{
}