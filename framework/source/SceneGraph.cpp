#include <utility>
#include <iostream>

#include "../include/SceneGraph.h"

SceneGraph::SceneGraph() = default;

SceneGraph::SceneGraph(std::string name, const Node& root):
name_{std::move(name)}, root_{root}{}

SceneGraph::~SceneGraph() = default;

std::string SceneGraph::getName() const
{
    return name_;
}

void SceneGraph::setName(std::string new_name)
{
    this->name_ = std::move(new_name);
}

Node SceneGraph::getRoot() const
{
    return root_;
}

void SceneGraph::setRoot(const Node& node)
{
    root_ = node;
}

std::string SceneGraph::printGraph() const
{
    //TODO: implement for better debugging
    return "Root" + getRoot().getName() ;
    //print children on every layer?
}


