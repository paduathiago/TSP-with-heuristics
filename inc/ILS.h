#ifndef ILS_H
#define ILS_H

#include "NearestNeighbourHeuristic.h"
#include "Node.h"
#include "ThreeOpt.h"

class ILS
{
public:
    ILS(std::string inputFile);
    void run();
    double computeTotalDistance();
    double getTotalDistance() const { return totalDistance; }
    std::vector<Node> doubleBridgeMove() const;

private:
    NearestNeighbour initialNN;
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    std::vector<Node> solution;
    double totalDistance;

    ThreeOpt threeOpt;
};

#endif // ILS_H