#include "Reinsertion.h"

Reinsertion::Reinsertion(std::shared_ptr<DistanceMeasure> distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

double Reinsertion::calculateDelta(const std::vector<Node>& solution, int removeIndex, int insertIndex)
{
    int size = solution.size();
    int prev = (removeIndex - 1 + size) % size;
    int next = (removeIndex + 1) % size;
    int posPrev = insertIndex;
    int posNext = (insertIndex + 1) % size;

    // Distances removed
    double delta = - distanceMeasure->distance(solution[prev], solution[removeIndex])
                   - distanceMeasure->distance(solution[removeIndex], solution[next])
                   + distanceMeasure->distance(solution[prev], solution[next]);

    // Distances added
    delta += - distanceMeasure->distance(solution[posPrev], solution[posNext])
             + distanceMeasure->distance(solution[posPrev], solution[removeIndex])
             + distanceMeasure->distance(solution[removeIndex], solution[posNext]);

    return delta;
}

std::vector<Node> Reinsertion::run(double totalDistance, const std::vector<Node>& solution)
{
    std::vector<Node> newSolution = solution;

    int size = newSolution.size();
    this->foundDistance = totalDistance;

    bool improvement = true;
    while (improvement)
    {
        improvement = false;

        for (int removeIndex = 0; removeIndex < size; ++removeIndex)
        {
            for (int insertIndex = 0; insertIndex < size; ++insertIndex)
            {
                if (insertIndex == removeIndex || insertIndex == removeIndex - 1) continue;

                double deltaLength = calculateDelta(solution, removeIndex, insertIndex);

                if (deltaLength < 0)
                {
                    // Perform the move
                    Node node = newSolution[removeIndex];
                    newSolution.erase(newSolution.begin() + removeIndex);
                    if (insertIndex > removeIndex) --insertIndex; // Adjust for the removal
                    newSolution.insert(newSolution.begin() + insertIndex, node);

                    foundDistance += deltaLength;
                    improvement = true;
                }
            }
        }
    }
    return newSolution;
}