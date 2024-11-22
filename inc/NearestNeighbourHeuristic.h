#ifndef NEAREST_NEIGHBOR_HEURISTIC_H
#define NEAREST_NEIGHBOR_HEURISTIC_H

#include <vector>

#include "Node.h"
#include "parser.h"
#include "KdTree.h"
#include "Node.h"

class NearestNeighbor
{
private:
    Parser parser;

    unsigned numberOfNodes;
    std::vector<Node> solution;

public:
    NearestNeighbor() : numberOfNodes(0) {}
    void solve(std::string inputFile);
    void printSolution() const;
    float totalDistance() const;
};

#endif // NEAREST_NEIGHBOR_HEURISTIC_H