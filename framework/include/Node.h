#include <string>
#include <vector>
#include <glm/gtx/transform.hpp>

class Node
{
public:
    Node();
    virtual ~Node();

    Node *getParent();
    void setParent(Node *node);
    Node *getChildren(std::string name);
    std::vector<Node *> getChildrenList();
    std::string getName();
    std::string getPath();
    int getDepth();
    glm::mat4 getLocalTransform();
    void setLocalTransform(glm::mat4 localTransform);
    glm::mat4 getWorldTransform();
    void setWorldTransform(glm::mat4 worldTransform);
    void addChildren(Node *node);
    Node *removeChildren(std::string name);

private:
    Node *parent;
    std::vector<Node *> children;
    std::string name;
    std::string path;
    int depth;
    glm::mat4 localTransform;
    glm::mat4 worldTransform;
};