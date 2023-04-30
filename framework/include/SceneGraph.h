#include <string>
#include "Node.h"
//TODO make SceneGraph a Singleton (only one scenegraph should be allowed to exist)
class SceneGraph
{
public:
    SceneGraph();
    SceneGraph(std::string name, const Node& root);
    ~SceneGraph();

    std::string getName() const;
    Node getRoot() const;
    std::string printGraph() const;

private:
    std::string name_;
    Node root_;
    void setName(std::string name);
    void setRoot(const Node& new_node);
};