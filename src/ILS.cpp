#include "ILS.h"

#include <algorithm>
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

double ILS::computeTotalDistance()
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
    std::vector<Node> newSolution = solution;

    pos[0] = random_int(1, solution.size() / 3);
    pos[1] = random_int(solution.size() / 3 + 1, solution.size()* 2/3);
    pos[2] = random_int(solution.size() * 2 / 3 + 1, solution.size());

    std::sort(pos, pos + 4);

    // std::vector<Node> seg1(solution.begin(), solution.begin() + pos[0]);
    // std::vector<Node> seg2(solution.begin() + pos[0], solution.begin() + pos[1]);
    // std::vector<Node> seg3(solution.begin() + pos[1], solution.begin() + pos[2]);
    // std::vector<Node> seg4(solution.begin() + pos[2], solution.end());

    std::vector<Node> newSolution;
    newSolution.clear();

    newSolution.insert(newSolution.end(), solution.begin(), solution.begin() + pos[0]);
    newSolution.insert(newSolution.end(), solution.begin() + pos[2], solution.end());
    newSolution.insert(newSolution.end(), solution.begin() + pos[1], solution.begin() + pos[2]);
    newSolution.insert(newSolution.end(), solution.begin() + pos[0], solution.begin() + pos[1]);

    return newSolution;
}

void ILS::run()
{
    // Solução inicial: Heurística construtiva com Nearest Neighbors.

    for (const auto& node : solution) {
        std::cout << node.id << " ";
    }
    std::cout << std::endl;

    std::vector<Node> newSolution = doubleBridgeMove();
    for (const auto& node : newSolution) {
        std::cout << node.id << " ";
    }
    std::cout << std::endl;

    // Busca Local: 3-opt
    solution = threeOpt.run(totalDistance, solution);
    totalDistance = threeOpt.getTotalDistance();

    // Perturbação: Simples troca de dois vértices ou remoção e reinserção de um subcaminho.
    // Critério de Aceitação: boltzmann distribution

}
