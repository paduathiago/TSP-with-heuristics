#include "NearestNeighbourHeuristic.h"

#include <random>

void NearestNeighbour::solve(std::string inputFile)
{
    std::vector<Node> cities = parser.parseTSPFile(inputFile);
    numberOfNodes = parser.getNumberOfNodes(inputFile);
    std::unique_ptr<DistanceMeasure> distanceMeasure = parser.getDistanceMeasure(inputFile);
    setDistanceMeasure(std::move(distanceMeasure));

    KdTree tree(cities, std::move(this->distanceMeasure));

    std::random_device rd;
    std::mt19937 gen(42);  // fixed seed

    std::uniform_int_distribution<> dist(1, numberOfNodes);

    int randomId = dist(gen);

    // First Node, chosen randomly
    std::shared_ptr<Node> newNodeInSolution = tree.findNodeById(randomId);
    std::shared_ptr<Node> oldNodeInSolution;
    while (!tree.empty())
    {
        solution.push_back(*newNodeInSolution);
        printSolution();  // REMOVE
        std:: cout << "------------------" << std::endl;
        oldNodeInSolution = tree.remove(*newNodeInSolution);
        if (!tree.empty())
            newNodeInSolution = tree.nearestNeighbour(*oldNodeInSolution);
    }
}

void NearestNeighbour::printSolution() const
{
    for (const Node& node : solution)
    {
        std::cout << node.id << " " << node.x << " " << node.y << std::endl;
    }
}

void NearestNeighbour::setDistanceMeasure(std::unique_ptr<DistanceMeasure> distanceMeasure)
{
    this->distanceMeasure = std::move(distanceMeasure);
}

double NearestNeighbour::totalDistance() const
{
    float distance = 0.0;
    for (int i = 0; i < int(solution.size() - 1); i++)
    {
        distance += distanceMeasure->distance(solution[i], solution[i + 1]);
    }
    distance += distanceMeasure->distance(solution[solution.size() - 1], solution[0]);
    return distance;
}