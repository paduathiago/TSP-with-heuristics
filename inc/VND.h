#ifndef VND_H
#define VND_H

#include "NearestNeighbourHeuristic.h"
#include "parser.h"
#include "TwoOpt.h"
#include "ThreeOpt.h"

class VND
{

public:
    VND(std::string inputFile);
    void run();
    double computeTotalDistance();
    double getTotalDistance() const { return totalDistance; }

private:
    NearestNeighbour initialNN;
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    std::vector<Node> solution;
    double totalDistance;

    TwoOpt twoOpt;
    ThreeOpt threeOpt;

    void runN1();
    void runN2();

};

#endif // VND_H