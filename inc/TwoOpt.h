#ifndef TWO_OPT_H
#define TWO_OPT_H

#include <vector>
#include <memory>

#include "DistanceMeasure.h"

class TwoOpt
{

public:
    TwoOpt() = default;
    TwoOpt(std::shared_ptr<DistanceMeasure> distanceMeasure);
    std::vector<Node> run(double totalDistance, const std::vector<Node>& solution);

    double getTotalDistance() const { return foundDistance; }

private:
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    double foundDistance;
};

#endif // TWO_OPT_H