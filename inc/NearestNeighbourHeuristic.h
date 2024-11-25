#ifndef NEAREST_NEIGHBOUR_HEURISTIC_H
#define NEAREST_NEIGHBOUR_HEURISTIC_H

#include <vector>

#include "Node.h"
#include "parser.h"
#include "KdTree.h"
#include "Node.h"
#include "DistanceMeasure.h"

class NearestNeighbour
{
private:
    Parser parser;
    std::string inputFile;

    unsigned numberOfNodes;
    std::vector<Node> solution;
    std::unique_ptr<DistanceMeasure> distanceMeasure;
    void setDistanceMeasure(const std::unique_ptr<DistanceMeasure> distanceMeasure);

public:
    NearestNeighbour() : numberOfNodes(0) {}
    void solve(std::string inputFile);
    void printSolution() const;
    double totalDistance();
};

#endif // NEAREST_NEIGHBOUR_HEURISTIC_H