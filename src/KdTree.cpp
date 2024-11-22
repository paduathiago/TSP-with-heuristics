#include "KdTree.h"

#include <limits>

KdTree::KdTree() {
    root = nullptr;
    size = 0;
}

KdTree::KdTree(std::vector<Node>& nodes) {
    KdTree();
    for (const Node& node : nodes)
        insert(node);
}

KdTree::~KdTree() {}

void KdTree::insert(const Node& node) {
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
    return remove(root, node, 0);
}

std::shared_ptr<Node> KdTree::remove(std::shared_ptr<Node>& current, const Node& target, int depth)
{
    /*
    Removes node with id = target.id and returns the removed node
    */

    if (!current)
        return nullptr;

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
            Node replacement = findMin(current->right, axis, 0);
            current->id = replacement.id;
            current->x = replacement.x;
            current->y = replacement.y;
            remove(current->right, replacement, depth + 1);
        }
        else if (current->left)
        {
            // Replace with the smallest node in the left subtree
            Node replacement = findMin(current->left, axis, 0);
            current->id = replacement.id;
            current->x = replacement.x;
            current->y = replacement.y;
            remove(current->left, replacement, depth + 1);
        }
        --size;
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

Node KdTree::findMin(const std::shared_ptr<Node>& current, int axis, int depth) const {
    if (!current) {
        throw std::runtime_error("Subtree is empty");
    }

    int currentAxis = depth % 2;

    if (currentAxis == axis) {
        // Encontrar o menor nó no eixo atual
        if (current->left) {
            return findMin(current->left, axis, depth + 1);
        }
        return *current;
    }

    // Comparar recursivamente com os menores das subárvores
    Node leftMin = current->left ? findMin(current->left, axis, depth + 1) : *current;
    Node rightMin = current->right ? findMin(current->right, axis, depth + 1) : *current;

    Node minNode = *current;
    if (leftMin.x < minNode.x || (axis == 1 && leftMin.y < minNode.y)) {
        minNode = leftMin;
    }
    if (rightMin.x < minNode.x || (axis == 1 && rightMin.y < minNode.y)) {
        minNode = rightMin;
    }

    return minNode;
}

double squaredDistance(const Node& a, const Node& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
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

Node KdTree::nearestNeighbour(const Node& node) const {
    Node* best = nullptr;
    double bestDist = std::numeric_limits<double>::max();

    nearestNeighbour(root, node, best, bestDist, 0);

    if (best) return *best;
    throw std::runtime_error("No nearest neighbour found.");
}

void KdTree::nearestNeighbour(const std::shared_ptr<Node>& root,
                              const Node& target,
                              Node*& best,
                              double& bestDist,
                              int depth
                             ) const
{
    if (!root) return;

    // Calcula a distância ao nó atual
    double dist = squaredDistance(*root, target);

    // Atualiza o melhor nó se a distância for menor
    if (dist < bestDist) {
        bestDist = dist;
        best = root.get();
    }

    // Define o eixo de comparação (0 -> x, 1 -> y)
    int axis = depth % 2;
    bool leftFirst = (axis == 0 && target.x < root->x) || (axis == 1 && target.y < root->y);

    // Busca no subárvore principal
    const std::shared_ptr<Node>& first = leftFirst ? root->left : root->right;
    const std::shared_ptr<Node>& second = leftFirst ? root->right : root->left;

    nearestNeighbour(first, target, best, bestDist, depth + 1);

    // Verifica se a distância ao plano divisor pode conter um nó mais próximo
    double planeDist = (axis == 0 ? target.x - root->x : target.y - root->y);
    if (planeDist * planeDist < bestDist) {
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
