#include <vector>
#include <memory>

#include "DistanceMeasure.h"

class TwoOpt {

public:
    TwoOpt(std::shared_ptr<DistanceMeasure> distanceMeasure, double totalDistance);
    std::vector<Node> run(double totalDistance, const std::vector<Node>& solution);

private:
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    double totalDistance;
};