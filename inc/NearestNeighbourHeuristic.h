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
    unsigned totalDistance;

    unsigned numberOfNodes;
    std::vector<Node> solution;
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    void setDistanceMeasure(const std::shared_ptr<DistanceMeasure> distanceMeasure);

public:
    NearestNeighbour();
    void solve(std::string inputFile);
    void printSolution() const;
    double computeTotalDistance();

    unsigned getTotalDistance() const { return totalDistance; }
};

#endif // NEAREST_NEIGHBOUR_HEURISTIC_H