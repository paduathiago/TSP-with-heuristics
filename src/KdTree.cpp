#include "KdTree.h"

#include <limits>

KdTree::KdTree(std::unique_ptr<DistanceMeasure> distanceMeasure)
{
    root = nullptr;
    size = 0;
    this->distanceMeasure = std::move(distanceMeasure);
}

KdTree::KdTree(std::vector<Node>& nodes, std::unique_ptr<DistanceMeasure> distanceMeasure)
    : KdTree(std::move(distanceMeasure))
{
    for (const Node& node : nodes)
        insert(node);
}

KdTree::~KdTree() {}

void KdTree::insert(const Node& node)
{
    insert(root, node, 0);
    ++size;
}

void KdTree::insert(std::shared_ptr<Node>& currentNode, const Node& newNode, int depth) {
    if (currentNode == nullptr) {
        currentNode = std::make_unique<Node>(newNode);
        return;
    }

    if (depth % 2 == 0)
    {
        if (newNode.x < currentNode->x)
            insert(currentNode->left, newNode, depth + 1);
        else
            insert(currentNode->right, newNode, depth + 1);
    }
    else
    {
        if (newNode.y < currentNode->y)
            insert(currentNode->left, newNode, depth + 1);
        else
            insert(currentNode->right, newNode, depth + 1);
    }
}

std::shared_ptr<Node> KdTree::remove(const Node& node)
{
    std::shared_ptr<Node> removedNode = remove(root, node, 0);
    if (removedNode)
    {
        --size;
    }
    return removedNode;
}

std::shared_ptr<Node> KdTree::remove(std::shared_ptr<Node>& current, const Node& target, int depth)
{
    /*
    Removes node with id = target.id and returns the removed node
    */

    if (!current)
    {
        throw std::runtime_error("Node not found");
    }

    // Current node will be removed
    if (current->id == target.id)
    {
        std::shared_ptr<Node> removedNode = std::make_shared<Node>(*current);

        // Case 1: Leaf node (node has no children)
        if (!current->left && !current->right)
        {
            current.reset();  // Remove the node
            return removedNode;
        }

        // Case 2: Node with subtrees
        int axis = depth % 2;

        if (current->right)
        {
            // Replace with the smallest node in the right subtree
            std::shared_ptr<Node> replacement = findMin(current->right, axis, depth + 1);
            current->id = replacement->id;
            current->x = replacement->x;
            current->y = replacement->y;
            remove(current->right, *replacement, depth + 1);
        }
        else if (current->left)
        {
            // Replace with the smallest node in the left subtree
            std::shared_ptr<Node> replacement = findMin(current->left, axis, depth + 1);
            current->id = replacement->id;
            current->x = replacement->x;
            current->y = replacement->y;
            current->right = std::move(current->left);
            remove(current->right, *replacement, depth + 1);
        }
        return removedNode;
    }

    // Continue searching for the node to remove
    int axis = depth % 2;
    if ((axis == 0 && target.x < current->x) || (axis == 1 && target.y < current->y))
    {
        return remove(current->left, target, depth + 1);
    }
    else
    {
        return remove(current->right, target, depth + 1);
    }
}

std::shared_ptr<Node> KdTree::findMin(const std::shared_ptr<Node>& current, int axis, int depth) const
{
    if (!current) {
        throw std::runtime_error("Subtree is empty");
    }

    int currentAxis = depth % 2;

    if (currentAxis == axis) {
        // Encontrar o menor nó no eixo atual
        if (current->left) {
            return findMin(current->left, axis, depth + 1);
        }
        return current;
    }

    // Comparar recursivamente com os menores das subárvores
    std::shared_ptr<Node> leftMin = current->left ? findMin(current->left, axis, depth + 1) : current;
    std::shared_ptr<Node> rightMin = current->right ? findMin(current->right, axis, depth + 1) : current;

    std::shared_ptr<Node> minNode = current;
    if (leftMin->x < minNode->x || (axis == 1 && leftMin->y < minNode->y)) {
        minNode = leftMin;
    }
    if (rightMin->x < minNode->x || (axis == 1 && rightMin->y < minNode->y)) {
        minNode = rightMin;
    }

    return minNode;
}

std::shared_ptr<Node> KdTree::findNodeById(int id) const {
    return findNodeById(root, id, 0);
}

std::shared_ptr<Node> KdTree::findNodeById(const std::shared_ptr<Node>& currentNode, int id, int depth) const {
    if (!currentNode)
    {
        return nullptr;
    }

    if (currentNode->id == id)
    {
        return currentNode;
    }

    std::shared_ptr<Node> leftResult = findNodeById(currentNode->left, id, depth + 1);
    if (leftResult)
    {
        return leftResult;
    }

    return findNodeById(currentNode->right, id, depth + 1);
}

std::shared_ptr<Node> KdTree::nearestNeighbour(const Node& node) const {
    std::shared_ptr<Node> best = nullptr;
    double bestDist = std::numeric_limits<double>::max();

    nearestNeighbour(root, node, best, bestDist, 0);

    if (best) return best;
    throw std::runtime_error("No nearest neighbour found.");
}

void KdTree::nearestNeighbour(const std::shared_ptr<Node>& root,
                              const Node& target,
                              std::shared_ptr<Node>& best,
                              double& bestDist,
                              int depth
                             ) const
{
    if (!root) return;

    double dist = distanceMeasure->distance(*root, target);

    if (dist < bestDist)
    {
        bestDist = dist;
        best = root;
    }

    // Defines the comparison axis (0 -> x, 1 -> y)
    int axis = depth % 2;
    bool leftFirst = (axis == 0 && target.x < root->x) || (axis == 1 && target.y < root->y);

    // Search the side of the splitting plane that the target is located
    const std::shared_ptr<Node>& first = leftFirst ? root->left : root->right;
    const std::shared_ptr<Node>& second = leftFirst ? root->right : root->left;

    nearestNeighbour(first, target, best, bestDist, depth + 1);

    // Check if the distance to the splitting plane could contain a closer node
    double planeDist = (axis == 0 ? target.x - root->x : target.y - root->y);
    if (planeDist * planeDist < bestDist)
    {
        nearestNeighbour(second, target, best, bestDist, depth + 1);
    }
}

bool KdTree::empty() const {
    return size == 0;
}

void KdTree::print() const {
    print(root, 0);
}

void KdTree::print(const std::shared_ptr<Node>& current, int depth) const {
    if (!current) return;

    print(current->left, depth + 1);

    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }

    std::cout << current->id << " (" << current->x << ", " << current->y << ")" << std::endl;

    print(current->right, depth + 1);
}

void KdTree::print_preorder() const {
    print_preorder(root);
}

void KdTree::print_preorder(const std::shared_ptr<Node>& current) const {
    if (!current) return;

    std::cout << current->id << " (" << current->x << ", " << current->y << ")" << std::endl;

    print_preorder(current->left);
    print_preorder(current->right);
}
