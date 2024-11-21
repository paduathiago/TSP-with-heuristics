#ifndef NODE_H
#define NODE_H

#include <memory>
#include <iostream>

class Node
{
public:
    int id;
    double x;
    double y;

    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node() : id(0), x(0), y(0), left(nullptr), right(nullptr) {}
    Node(int id, double x, double y) : id(id), x(x), y(y), left(nullptr), right(nullptr) {}
};

#endif // NODE_H
