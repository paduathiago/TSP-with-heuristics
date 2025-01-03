#ifndef KD_TREE_H
#define KD_TREE_H

#include "Node.h"
#include "DistanceMeasure.h"

#include <vector>

class KdTree
{
public:
    KdTree(std::shared_ptr<DistanceMeasure> distanceMeasure);
    KdTree(std::vector<Node>& nodes, std::shared_ptr<DistanceMeasure> distanceMeasure);
    ~KdTree();

    void insert(const Node& node);
    std::shared_ptr<Node> remove(const Node& node);
    std::shared_ptr<Node> nearestNeighbour(const Node& node) const;

    std::shared_ptr<Node> findNodeById(int id) const;

    unsigned getSize() const { return size; }

    void print() const;
    void print_preorder() const;

    void clear();
    bool empty() const;

private:
    std::shared_ptr<Node> root;
    unsigned size;
    std::shared_ptr<DistanceMeasure> distanceMeasure;

    void insert(std::shared_ptr<Node>& currentNode, const Node& newNode, int depth);
    std::shared_ptr<Node> remove(std::shared_ptr<Node>& root, const Node& node, int depth);
    std::shared_ptr<Node> findMin(const std::shared_ptr<Node>& current, int axis, int depth) const;
    void nearestNeighbour(const std::shared_ptr<Node>& root, const Node& target,
                                  std::shared_ptr<Node>& best, double& bestDist, int depth) const;

    std::shared_ptr<Node> findNodeById(const std::shared_ptr<Node>& currentNode, int id, int depth) const;
    void print(const std::shared_ptr<Node>& current, int depth) const;
    void print_preorder(const std::shared_ptr<Node>& current, char childType) const;
};

#endif // KD_TREE_H
