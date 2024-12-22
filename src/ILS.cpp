#include "ILS.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>
#include <string>
#include <vector>


ILS::ILS(std::string inputFile)
{
    initialNN.solve(inputFile);

    distanceMeasure = initialNN.getDistanceMeasure();
    solution = initialNN.getSolution();
    totalDistance = float(initialNN.getTotalDistance());

    threeOpt = ThreeOpt(distanceMeasure);
}

double ILS::computeTotalDistance(std::vector<Node> solution) const
{
    double dist = 0.0;
    for (int i = 0; i < int(solution.size() - 1); i++)
    {
        dist += distanceMeasure->distance(solution[i], solution[i + 1]);
    }
    dist += distanceMeasure->distance(solution[solution.size() - 1], solution[0]);
    return dist;
}

int random_int(int low, int high)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

std::pair<std::vector<Node>, double> ILS::doubleBridgeMove() const
{
    unsigned pos[3];
    std::vector<Node> newSolution;
    double newDistance = totalDistance;

    pos[0] = random_int(1, solution.size() / 3);
    pos[1] = random_int(solution.size() / 3 + 1, solution.size()* 2/3);
    pos[2] = random_int(solution.size() * 2 / 3 + 1, solution.size() - 1);

    std::sort(std::begin(pos), std::end(pos));

    newDistance -= distanceMeasure->distance(solution[pos[0] - 1], solution[pos[0]]);
    newDistance -= distanceMeasure->distance(solution[pos[1] - 1], solution[pos[1]]);
    newDistance -= distanceMeasure->distance(solution[pos[2] - 1], solution[pos[2]]);
    newDistance -= distanceMeasure->distance(solution.back(), solution.front());

    newDistance += distanceMeasure->distance(solution[pos[0] - 1], solution[pos[2]]);
    newDistance += distanceMeasure->distance(solution.back(), solution[pos[1]]);
    newDistance += distanceMeasure->distance(solution[pos[2] - 1], solution[pos[0]]);
    newDistance += distanceMeasure->distance(solution[pos[1] - 1], solution.front());

    newSolution.reserve(solution.size());

    newSolution.insert(newSolution.end(), solution.begin(), solution.begin() + pos[0]);
    newSolution.insert(newSolution.end(), solution.begin() + pos[2], solution.end());
    newSolution.insert(newSolution.end(), solution.begin() + pos[1], solution.begin() + pos[2]);
    newSolution.insert(newSolution.end(), solution.begin() + pos[0], solution.begin() + pos[1]);

    return std::make_pair(newSolution, newDistance);
}

bool ILS::acceptSolution(float temperature, double newDistance)
{
    double deltaE = newDistance - totalDistance;

    if (deltaE <= 0)
    {
        return true; // Always accept better solutions
    }
    double probability = exp(-deltaE / temperature);
    double randomValue = ((double) rand() / RAND_MAX);
    return randomValue < probability;
}

float ILS::coolingSchedule(float currentTemperature, float alpha)
{
    return currentTemperature * alpha;
}

void ILS::run(float initialTemperature, float alpha)
{
    float temperature = initialTemperature;
    float minTemperature = 0.0001;

    solution = threeOpt.run(totalDistance, solution);
    totalDistance = threeOpt.getTotalDistance();

    std::vector<Node> bestSolution = solution;
    double bestDistance = totalDistance;

    while (temperature > minTemperature)
    {
        auto [perturbedSolution, perturbedDistance] = doubleBridgeMove();

        std::vector<Node> newSolution = threeOpt.run(perturbedDistance, perturbedSolution);
        double newDistance = threeOpt.getTotalDistance();

        if (acceptSolution(temperature, newDistance))
        {
            solution = newSolution;
            totalDistance = newDistance;
            if (totalDistance < bestDistance)
            {
                bestDistance = totalDistance;
                bestSolution = solution;
            }
        }
        temperature = coolingSchedule(temperature, alpha);  // Acceptance criteria: boltzmann distribution
    }
    solution = bestSolution;
    totalDistance = bestDistance;
}
