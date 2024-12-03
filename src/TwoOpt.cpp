#include "TwoOpt.h"
#include "Node.h"
#include "NearestNeighbourHeuristic.h"
#include "DistanceMeasure.h"

#include <vector>
#include <algorithm>

TwoOpt::TwoOpt(std::shared_ptr<DistanceMeasure> distanceMeasure, double totalDistance)
{
    this->distanceMeasure = distanceMeasure;
    this->totalDistance = totalDistance;
}

// Params should come from a NearestNeighbour object
std::vector<Node> TwoOpt::run(double totalDistance, const std::vector<Node>& solution)
{
    std::vector<Node> newSolution = solution;
    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        int size = newSolution.size();
        for (int i = 0; i < size - 1; ++i)
        {
            for (int k = i + 1; k < size - 1; ++k)
            {
                double deltaLength = -distanceMeasure->distance(newSolution[i], newSolution[i + 1])
                                     -distanceMeasure->distance(newSolution[k], newSolution[k + 1])
                                     + distanceMeasure->distance(newSolution[i], newSolution[k])
                                     + distanceMeasure->distance(newSolution[i + 1], newSolution[k + 1]);

                if (deltaLength < 0)
                {
                    std::reverse(newSolution.begin() + i, newSolution.begin() + k + 1);  // ATENTION
                    totalDistance += deltaLength;  // deltaLength is negative
                    improvement = true;
                }
            }
        }
    }
    return newSolution;
}