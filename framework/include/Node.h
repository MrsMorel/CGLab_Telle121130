#ifndef OPENGL_FRAMEWORK_NODE_H
#define OPENGL_FRAMEWORK_NODE_H
#include <string>
#include <vector>
#include <glm/gtx/transform.hpp>
#include <memory>

class Node
{
public:
    Node();
    virtual ~Node();
    Node(std::string name);
    Node(std::string name, glm::mat4 localTransform);
    Node(std::string name, glm::mat4 localTransform, glm::mat4 worldTransform);
    Node(std::string name, glm::mat4 localTransform, glm::mat4 worldTransform, std::shared_ptr<Node> parent);

    Node(std::string name, glm::mat4 localTransform, glm::mat4 worldTransform, int depth);

    std::shared_ptr<Node> getParent() const;
    void setParent(std::shared_ptr<Node> new_node);
    std::shared_ptr<Node> getChildren(const std::string& name) const;
    std::vector<std::shared_ptr<Node>> getChildrenList() const;
    std::string getName() const;
    std::string getPath() const;
    int getDepth() const;
    glm::mat4 getLocalTransform() const;
    void setLocalTransform(const glm::mat4& localTransform);
    glm::mat4 getWorldTransform() const;
    void setWorldTransform(const glm::mat4& worldTransform);
    void addChild(const std::shared_ptr<Node>& new_node);
    Node removeChild(std::string name);

private:
    std::shared_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> children_;
    std::string name_;
    std::string path_;
    int depth_;
    glm::mat4 localTransform_;
    glm::mat4 worldTransform_;
};
#endif //OPENGL_FRAMEWORK_NODE_H