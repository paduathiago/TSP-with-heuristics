#include "NearestNeighbourHeuristic.h"

#include <random>

NearestNeighbour::NearestNeighbour()
{
    totalDistance = 0.0;
    numberOfNodes = 0;
}

void NearestNeighbour::solve(std::string inputFile)
{
    this->inputFile = inputFile;

    std::vector<Node> cities = parser.parseTSPFile(inputFile);
    numberOfNodes = parser.getNumberOfNodes(inputFile);
    std::shared_ptr<DistanceMeasure> distanceMeasure = parser.getDistanceMeasure(inputFile);
    setDistanceMeasure(distanceMeasure);

    KdTree tree(cities, distanceMeasure);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(5, 5);

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
        totalDistance += distanceMeasure->distance(*newNodeInSolution, *oldNodeInSolution);
    }
    totalDistance += distanceMeasure->distance(solution[solution.size() - 1], solution[0]);
}

void NearestNeighbour::printSolution() const
{
    for (const Node& node : solution)
    {
        std::cout << node.id << " " << node.x << " " << node.y << std::endl;
    }
}

void NearestNeighbour::setDistanceMeasure(std::shared_ptr<DistanceMeasure> distanceMeasure)
{
    this->distanceMeasure = distanceMeasure;
}

double NearestNeighbour::computeTotalDistance()
{
    double distance = 0.0;

    for (int i = 0; i < int(solution.size() - 1); i++)
    {
        distance += distanceMeasure->distance(solution[i], solution[i + 1]);
    }
    distance += distanceMeasure->distance(solution[solution.size() - 1], solution[0]);
    return distance;
}