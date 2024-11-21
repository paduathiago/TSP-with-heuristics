#include "Node.h"

#include <vector>

class KdTree
{
public:
    KdTree();
    KdTree(std::vector<Node>& nodes);
    ~KdTree();

    void insert(const Node& node);
    void remove(const Node& node);
    Node nearestNeighbour(const Node& node) const;

    void clear();
    bool empty() const;

private:
    std::shared_ptr<Node> root;
    void insert(std::shared_ptr<Node>& currentNode, const Node& newNode, int depth);
    void remove(std::shared_ptr<Node>& root, const Node& node, int depth);
    Node findMin(const std::shared_ptr<Node>& current, int axis, int depth) const;
    void nearestNeighbour(const std::shared_ptr<Node>& root, const Node& target,
                                  Node*& best, double& bestDist, int depth) const;
};