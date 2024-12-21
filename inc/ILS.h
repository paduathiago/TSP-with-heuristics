#ifndef ILS_H
#define ILS_H

#include "NearestNeighbourHeuristic.h"
#include "Node.h"
#include "ThreeOpt.h"

class ILS
{
public:
    ILS(std::string inputFile);
    void run(float initialTemperature, float alpha);
    double computeTotalDistance(std::vector<Node> solution);
    double getTotalDistance() const { return totalDistance; }
    std::vector<Node> doubleBridgeMove() const;

private:
    NearestNeighbour initialNN;
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    std::vector<Node> solution;
    double totalDistance;

    ThreeOpt threeOpt;

    bool acceptSolution(float temperature, double newDistance, bool alwaysAcceptBetterSolutions);
    float coolingSchedule(float temperature, float alpha);
};

#endif // ILS_H