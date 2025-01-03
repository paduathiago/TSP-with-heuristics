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
    double totalDistance;

    unsigned numberOfNodes;
    std::vector<Node> solution;
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    void setDistanceMeasure(const std::shared_ptr<DistanceMeasure> distanceMeasure);

public:
    NearestNeighbour();
    void solve(std::string inputFile);
    void printSolution() const;
    double computeTotalDistance();

    double getTotalDistance() const { return totalDistance; }
    std::vector<Node> getSolution() const { return solution; }
    std::shared_ptr<DistanceMeasure> getDistanceMeasure() const { return distanceMeasure; }
};

#endif // NEAREST_NEIGHBOUR_HEURISTIC_H