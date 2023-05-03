#include <utility>

#include "Node.h"
//default constructor
Node::Node():
name_{"default node"}
{
}
//destructor
Node::~Node() {}
//constructors
Node::Node(std::string name):
name_{std::move(name)}
{}

Node::Node(std::string name, glm::mat4 localTransform):
name_(),
localTransform_{localTransform}{
}

Node::Node(std::string name, glm::mat4 localTransform, glm::mat4 worldTransform):
name_{name}, localTransform_{localTransform}, worldTransform_{worldTransform}{}

Node::Node(std::string name, glm::mat4 localTransform, glm::mat4 worldTransform, int depth):
name_{name}, localTransform_{localTransform}, worldTransform_{worldTransform}{}
Node::Node(std::string name, glm::mat4 localTransform, glm::mat4 worldTransform, std::shared_ptr<Node> parent):
        parent_{parent}, name_{name}, localTransform_{localTransform}, worldTransform_{worldTransform}{

}

//getter for parent node
std::shared_ptr<Node> Node::getParent() const {
    if (parent_ != nullptr) {
        return parent_;
    }
    else {
        return std::make_shared<Node>("error no parent");
    }
}
//setter for parent node
void Node::setParent(std::shared_ptr<Node> new_node) {
    parent_ = std::move(new_node);
}
//returns child of one node
std::shared_ptr<Node> Node::getChildren(const std::string& name) const {
    if (children_.empty()){
        return nullptr;
    }
    for (auto const& i : children_) {
        if (i->getName() == name){
            return i;
        }
        else if (i->getChildren(name) == nullptr) continue;
        else return i->getChildren(name);

    }
    return nullptr;
}
//getter
std::vector<std::shared_ptr<Node>> Node::getChildrenList() const {
    return children_;
}

std::string Node::getName() const {
    return name_;
}
//TODO Test
//is the get path also setting the path?
std::string Node::getPath() const {
    std::string temp_path;
    temp_path = this->getName();
    for (auto const& i : this->getChildrenList()) {
        i->getPath();
        temp_path += "  ->  " + i->getName();
    }
    return temp_path;
}
//Todo test
int Node::getDepth() const {
    int depth = 1;
    for (auto const& i : this->getChildrenList()) {
        if ( !i->getChildrenList().empty()){
            depth += 1;
        }
        for (auto const& j : i->getChildrenList()) {
            if (!i->getChildrenList().empty()){
                depth += 1;
            }
        }
    }
    return depth;
}
//getter
glm::mat4 Node::getLocalTransform() const {
    return localTransform_;
}

void Node::setLocalTransform(const glm::mat4& localTransform) {
    localTransform_ = localTransform;
}

// worldTransform = parent.worldTransform * localTransform
glm::mat4 Node::getWorldTransform() const {
    if (parent_ == nullptr){
        return localTransform_;
    }
    return parent_->getWorldTransform() * localTransform_;
}
//setter
void Node::setWorldTransform(const glm::mat4& worldTransform) {
    worldTransform_ = worldTransform;
}
//adding child node
void Node::addChild(const std::shared_ptr<Node>& node) {
    children_.push_back(node);
}
//remove child node
Node Node::removeChild(const std::string& name) {
    Node temp;
    Node temp2;
    for (auto const& i : children_) {
        if (i->getName() == name){
            temp = *i;
        }
        getChildren(name);
        temp2 = temp;
    }
    return temp2;
}

Node::Node(std::string name, const glm::mat4& localTransform, std::shared_ptr<Node> parent):
parent_{std::move(parent)}, name_{std::move(name)}, localTransform_{localTransform}{

}






