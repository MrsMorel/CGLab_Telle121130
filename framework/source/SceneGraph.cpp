#include <utility>
#include <iostream>

#include "../include/SceneGraph.h"

SceneGraph::SceneGraph(std::string name, Node *root)
{
    this->name = std::move(name);
    this->root = root;
}

SceneGraph::~SceneGraph() = default;

std::string SceneGraph::getName()
{
    return name;
}

void SceneGraph::setName(std::string new_name)
{
    this->name = std::move(new_name);
}

Node *SceneGraph::getRoot()
{
    return root;
}

void SceneGraph::setRoot(Node *node)
{
    root = node;
}

std::string SceneGraph::printGraph()
{
    //TODO: implement for better debugging
    return "Root" + getRoot()->getName() ;
    //print children on every layer?
}