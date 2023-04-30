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
std::string printChild(const std::vector<std::shared_ptr<Node>>& children, bool hasChild){
    for ( auto const& i : children) {
        std::cout<< i->getName() << "  ->  ";
        if (!i->getChildrenList().empty()){
            printChild(i->getChildrenList(), false);
        }
        if (hasChild){
            std::cout<<std::endl;
        }

    }
}

std::string SceneGraph::printGraph() const
{
    std::cout<<"Root = " + getRoot().getName()<<std::endl;
    std::cout<<"Children:  "<<std::endl;
    std::vector<std::shared_ptr<Node>> children = root_.getChildrenList();
    printChild(children, true);

}


