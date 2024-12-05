#ifndef THREE_OPT_H
#define THREE_OPT_H

#include <vector>
#include <memory>

#include "DistanceMeasure.h"

class ThreeOpt
{
public:
    ThreeOpt() = default;
    ThreeOpt(std::shared_ptr<DistanceMeasure> distanceMeasure);
    std::vector<Node> run(double totalDistance, const std::vector<Node>& solution);

    double getTotalDistance() const { return foundDistance; }

private:
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    double foundDistance;

    float gainExpected(int i, int j, int k, int t, const std::vector<Node>& solution);
    void reverseSegment(std::vector<Node>& tour, int startIndex, int endIndex);
};

struct BestMove
{
    int i;
    int j;
    int k;
    int t;  // type of move
    float gain;
};

#endif // THREE_OPT_H