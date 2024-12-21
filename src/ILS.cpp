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
    totalDistance = initialNN.getTotalDistance();

    threeOpt = ThreeOpt(distanceMeasure);
}

double ILS::computeTotalDistance(std::vector<Node> solution)
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

std::vector<Node> ILS::doubleBridgeMove() const
{
    unsigned pos[3];
    std::vector<Node> newSolution;

    pos[0] = random_int(1, solution.size() / 3);
    pos[1] = random_int(solution.size() / 3 + 1, solution.size()* 2/3);
    pos[2] = random_int(solution.size() * 2 / 3 + 1, solution.size());

    std::sort(pos, pos + 4);

    // std::vector<Node> seg1(solution.begin(), solution.begin() + pos[0]);
    // std::vector<Node> seg2(solution.begin() + pos[0], solution.begin() + pos[1]);
    // std::vector<Node> seg3(solution.begin() + pos[1], solution.begin() + pos[2]);
    // std::vector<Node> seg4(solution.begin() + pos[2], solution.end());

    // newSolution.insert(newSolution.end(), seg1.begin(), seg1.end());
    // newSolution.insert(newSolution.end(), seg4.begin(), seg4.end());
    // newSolution.insert(newSolution.end(), seg3.begin(), seg3.end());
    // newSolution.insert(newSolution.end(), seg2.begin(), seg2.end());

    newSolution.reserve(solution.size());

    newSolution.insert(newSolution.end(), solution.begin(), solution.begin() + pos[0]);
    newSolution.insert(newSolution.end(), solution.begin() + pos[2], solution.end());
    newSolution.insert(newSolution.end(), solution.begin() + pos[1], solution.begin() + pos[2]);
    newSolution.insert(newSolution.end(), solution.begin() + pos[0], solution.begin() + pos[1]);

    return newSolution;
}

bool ILS::acceptSolution(float temperature, double newDistance, bool alwaysAcceptBetterSolutions = true)
{
    double deltaE = newDistance - totalDistance;

    if (deltaE <= 0 && alwaysAcceptBetterSolutions) // How inpactful is this?
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

void auxPrint(std::vector<Node> solution)
{
    for (const auto& node : solution) {
        std::cout << node.id << " ";
    }
    std::cout << std::endl;
}

void ILS::run(float initialTemperature, float alpha)
{
    // Solução inicial: Heurística construtiva com Nearest Neighbors.

    float temperature = initialTemperature;
    float minTemperature = 0.0001;

    solution = threeOpt.run(totalDistance, solution);
    totalDistance = threeOpt.getTotalDistance();

    while (temperature > minTemperature)
    {
        std::vector<Node> perturbedSolution = doubleBridgeMove();
        double perturbedDistance = computeTotalDistance(perturbedSolution);  // EXPENSIVE OPERATION

        std::vector<Node> newSolution = threeOpt.run(perturbedDistance, perturbedSolution);
        double newDistance = threeOpt.getTotalDistance();

        if (acceptSolution(temperature, newDistance))
        {
            solution = newSolution;
            totalDistance = newDistance;
        }

        temperature = coolingSchedule(temperature, alpha);  // Acceptance criteria: boltzmann distribution
    }
}
