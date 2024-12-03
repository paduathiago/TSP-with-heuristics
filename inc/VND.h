#ifndef VND_H
#define VND_H

#include "NearestNeighbourHeuristic.h"
#include "parser.h"
#include "TwoOpt.h"

class VND
{

public:
    VND(std::string inputFile);
    void run();

    double getTotalDistance() const { return totalDistance; }

private:
    NearestNeighbour initialNN;
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    std::vector<Node> solution;
    double totalDistance;

    TwoOpt twoOpt;


};

#endif // VND_H