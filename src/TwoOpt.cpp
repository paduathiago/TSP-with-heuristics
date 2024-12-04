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

void TwoOpt::reverseSegment(std::vector<Node>& tour, int startIndex, int endIndex)
{
    /*
    Reverses the order of elements in the segment [startIndex, endIndex] of the tour.
    Handles circular indexing with modular arithmetic.
    */

    int N = tour.size();

    int inversionSize = ((N + endIndex - startIndex + 1) % N) / 2;

    int left = startIndex;
    int right = endIndex;

    for (int counter = 0; counter < inversionSize; ++counter) {
        std::swap(tour[left], tour[right]);
        left = (left + 1) % N;           // Move left forward, wrapping around
        right = (N + right - 1) % N;    // Move right backward, wrapping around
    }
}


// Params should come from a NearestNeighbour object
std::vector<Node> TwoOpt::run(double totalDistance, const std::vector<Node>& solution)
{
    std::vector<Node> newSolution = solution;
    this->foundDistance = totalDistance;
    int size = newSolution.size();

    bool improvement = true;
    while (improvement)
    {
        improvement = false;
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
                    reverseSegment(newSolution, (i + 1) % size, j);
                    foundDistance += deltaLength;  // deltaLength is negative
                    improvement = true;
                }
            }
        }
    }
    return newSolution;
}