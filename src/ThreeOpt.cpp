#include "ThreeOpt.h"
#include "Node.h"

#include <algorithm>
#include <cmath>

ThreeOpt::ThreeOpt(std::shared_ptr<DistanceMeasure> distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

float ThreeOpt::gainExpected(int i, int j, int k, int t, const std::vector<Node>& solution)
{
    int size = solution.size();
    float gain = 0;

    if(i == 0 && k == size - 1)
    {
        return 0;
    }
    else if (j == i + 1 && k == size - 1)
    {
        return 0;
    }

    switch (t)
    {
    case 1:
        gain = - distanceMeasure->distance(solution[i], solution[(i + 1) % size])
               - distanceMeasure->distance(solution[k], solution[(k + 1) % size])
               + distanceMeasure->distance(solution[i], solution[k])
               + distanceMeasure->distance(solution[(i + 1) % size], solution[(k + 1) % size]);
        break;
    case 2:
        gain = - distanceMeasure->distance(solution[j], solution[(j + 1 % size)])
               - distanceMeasure->distance(solution[k], solution[(k + 1) % size])
               + distanceMeasure->distance(solution[j], solution[k])
               + distanceMeasure->distance(solution[(j + 1 % size)], solution[(k + 1 % size)]);

        break;
    case 3:
        gain = - distanceMeasure->distance(solution[i], solution[(i + 1) % size])
               - distanceMeasure->distance(solution[j], solution[(j + 1) % size])
               + distanceMeasure->distance(solution[i], solution[j])
               + distanceMeasure->distance(solution[(i + 1) % size], solution[(j + 1) % size]);
        break;
    case 4:
        gain = - distanceMeasure->distance(solution[i], solution[(i + 1) % size])
               - distanceMeasure->distance(solution[j], solution[(j + 1) % size])
               - distanceMeasure->distance(solution[k], solution[(k + 1) % size])
               + distanceMeasure->distance(solution[i], solution[j])
               + distanceMeasure->distance(solution[(i + 1) % size], solution[k])
               + distanceMeasure->distance(solution[(j + 1) % size], solution[(k + 1) % size]);
        break;
    case 5:
        gain = - distanceMeasure->distance(solution[i], solution[(i + 1) % size])
               - distanceMeasure->distance(solution[j], solution[(j + 1) % size])
               - distanceMeasure->distance(solution[k], solution[(k + 1) % size])
               + distanceMeasure->distance(solution[i], solution[k])
               + distanceMeasure->distance(solution[(i + 1) % size], solution[(j + 1) % size])
               + distanceMeasure->distance(solution[j], solution[(k + 1) % size]);
        break;
    case 6:
        gain = - distanceMeasure->distance(solution[i], solution[(i + 1) % size])
               - distanceMeasure->distance(solution[j], solution[(j + 1) % size])
               - distanceMeasure->distance(solution[k], solution[(k + 1) % size])
               + distanceMeasure->distance(solution[i], solution[(j + 1) % size])
               + distanceMeasure->distance(solution[j], solution[k])
               + distanceMeasure->distance(solution[(i + 1) % size], solution[(k + 1) % size]);
        break;
    case 7:
        gain = - distanceMeasure->distance(solution[i], solution[(i + 1) % size])
               - distanceMeasure->distance(solution[j], solution[(j + 1) % size])
               - distanceMeasure->distance(solution[k], solution[(k + 1) % size])
               + distanceMeasure->distance(solution[i], solution[(j + 1) % size])
               + distanceMeasure->distance(solution[k], solution[(i + 1) % size])
               + distanceMeasure->distance(solution[j], solution[(k + 1) % size]);
        break;
    default:
        break;
    }
    return gain;
}

void ThreeOpt::reverseSegment(std::vector<Node>& tour, int startIndex, int endIndex)
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

std::vector<Node> ThreeOpt::run(double totalDistance, const std::vector<Node>& solution)
{
    std::vector<Node> newSolution = solution;
    this->foundDistance = totalDistance;

    BestMove bestMove;
    bestMove.gain = 0;

    bool improvement = true;
    int size = newSolution.size();

    while (improvement)
    {
        improvement = false;
        for (int i = 0; i < size - 1; ++i)
        {
            for (int j = i + 1; j < size - 3; ++j)
            {
                for (int k = j + 1; k < size - 1; ++k)
                {
                    for (int t = 1; t < 8; ++t)
                    {
                        float gainX = gainExpected(i, j, k, t, newSolution);
                        if(-gainX > 0.01 && -gainX > bestMove.gain)
                        {
                            bestMove.i = i;
                            bestMove.j = j;
                            bestMove.k = k;
                            bestMove.t = t;
                            bestMove.gain = std::abs(gainX);
                            // std::cout << "i: " << i << " j: " << j << " k: " << k << " t: " << t << " gain: " << gainX << std::endl;
                            improvement = true;
                        }
                    }
                }
            }

        }
        if(improvement)
        {
            // std::cout << "Reverse: " << std::endl;
            switch (bestMove.t)
            {
            case 1:
                reverseSegment(newSolution, (bestMove.k + 1) % size, bestMove.i);
                break;
            case 2:
                reverseSegment(newSolution, (bestMove.j + 1) % size, bestMove.k);
                break;
            case 3:
                reverseSegment(newSolution, (bestMove.i + 1) % size, bestMove.j);
                break;
            case 4:
                reverseSegment(newSolution, (bestMove.j + 1) % size, bestMove.k);
                reverseSegment(newSolution, (bestMove.i + 1) % size, bestMove.j);
                break;
            case 5:
                reverseSegment(newSolution, (bestMove.k + 1) % size, bestMove.i);
                reverseSegment(newSolution, (bestMove.i + 1) % size, bestMove.j);
                break;
            case 6:
                reverseSegment(newSolution, (bestMove.k + 1) % size, bestMove.i);
                reverseSegment(newSolution, (bestMove.j + 1) % size, bestMove.k);
                break;
            case 7:
                reverseSegment(newSolution, (bestMove.k + 1) % size, bestMove.i);
                reverseSegment(newSolution, (bestMove.i + 1) % size, bestMove.j);
                reverseSegment(newSolution, (bestMove.j + 1) % size, bestMove.k);
                break;
            default:
                break;
            }
            std::cout << "Gain: " << bestMove.gain << std::endl;
            foundDistance -= bestMove.gain;
        }
    }
    return newSolution;
}