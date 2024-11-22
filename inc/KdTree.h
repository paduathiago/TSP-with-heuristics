#include "Node.h"

#include <vector>

class KdTree
{
public:
    KdTree();
    KdTree(std::vector<Node>& nodes);
    ~KdTree();

    void insert(const Node& node);
    std::shared_ptr<Node> remove(const Node& node);
    Node nearestNeighbour(const Node& node) const;

    std::shared_ptr<Node> findNodeById(int id) const;

    void print() const;
    void print_preorder() const;

    void clear();
    bool empty() const;

private:
    std::shared_ptr<Node> root;
    void insert(std::shared_ptr<Node>& currentNode, const Node& newNode, int depth);
    std::shared_ptr<Node> remove(std::shared_ptr<Node>& root, const Node& node, int depth);
    Node findMin(const std::shared_ptr<Node>& current, int axis, int depth) const;
    void nearestNeighbour(const std::shared_ptr<Node>& root, const Node& target,
                                  Node*& best, double& bestDist, int depth) const;

    std::shared_ptr<Node> findNodeById(const std::shared_ptr<Node>& currentNode, int id, int depth) const;
    void print(const std::shared_ptr<Node>& current, int depth) const;
    void print_preorder(const std::shared_ptr<Node>& current) const;
};