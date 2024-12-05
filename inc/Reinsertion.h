#ifndef REINSERTION_H
#define REINSERTION_H

#include "DistanceMeasure.h"
#include "Node.h"

#include <memory>
#include <vector>

class Reinsertion
{
public:
    Reinsertion() = default;
    Reinsertion(std::shared_ptr<DistanceMeasure> distanceMeasure);
    std::vector<Node> run(double totalDistance, const std::vector<Node>& solution);

    double getTotalDistance() const { return foundDistance; }

private:
    std::shared_ptr<DistanceMeasure> distanceMeasure;
    double foundDistance;

    double calculateDelta(const std::vector<Node>& solution, int removeIndex, int insertIndex);
};

#endif // REINSERTION_H