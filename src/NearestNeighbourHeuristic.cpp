#include "NearestNeighbourHeuristic.h"

#include <random>

void NearestNeighbor::solve(std::string inputFile)
{
    std::vector<Node> cities = parser.parseTSPFile(inputFile);
    numberOfNodes = parser.getNumberOfNodes(inputFile);
    KdTree tree(cities);

    std::random_device rd;
    std::mt19937 gen(42);

    // ATENTION
    std::uniform_int_distribution<> dist(1, numberOfNodes);

    int randomId = dist(gen);

    // First Node, chosen randomly
    std::shared_ptr<Node> newNodeInSolution = tree.findNodeById(randomId);
    std::shared_ptr<Node> oldNodeInSolution;
    while (!tree.empty())
    {
        solution.push_back(*newNodeInSolution);
        oldNodeInSolution = tree.remove(*newNodeInSolution);
        if (!tree.empty())
            newNodeInSolution = tree.nearestNeighbour(*oldNodeInSolution);
    }
}

void NearestNeighbor::printSolution() const
{
    for (const Node& node : solution)
    {
        std::cout << node.id << " " << node.x << " " << node.y << std::endl;
    }
}

float NearestNeighbor::totalDistance() const
{
    float distance = 0.0;
    for (int i = 0; i < solution.size() - 1; i++)
    {
        distance += solution[i].distance(solution[i + 1]);
    }
    distance += solution[solution.size() - 1].distance(solution[0]);
    return distance;
}