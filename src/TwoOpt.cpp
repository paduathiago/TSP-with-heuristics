#include "TwoOpt.h"
#include "Node.h"
#include "NearestNeighbourHeuristic.h"
#include "DistanceMeasure.h"

#include <vector>
#include <algorithm>

TwoOpt::TwoOpt(std::shared_ptr<DistanceMeasure> distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

// Params should come from a NearestNeighbour object
std::vector<Node> TwoOpt::run(double totalDistance, const std::vector<Node>& solution)
{
    std::vector<Node> newSolution = solution;
    this->foundDistance = totalDistance;
    bool improvement = true;
    while (improvement)
    {
        improvement = false;
        int size = newSolution.size();
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = i + 2; j < size; ++j)
            {
                double deltaLength = -distanceMeasure->distance(newSolution[i], newSolution[i + 1])
                                     -distanceMeasure->distance(newSolution[j], newSolution[(j + 1) % size])
                                     + distanceMeasure->distance(newSolution[i], newSolution[j])
                                     + distanceMeasure->distance(newSolution[i + 1], newSolution[(j + 1) % size]);

                if (i == (j + 1) % size)  // This case might cause problems due to numerical errors
                {
                    continue;
                }
                if (deltaLength < 0)
                {
                    std::reverse(newSolution.begin() + i + 1, newSolution.begin() + j + 1);  // ATENTION
                    foundDistance += deltaLength;  // deltaLength is negative
                    improvement = true;
                }
            }
        }
    }
    return newSolution;
}