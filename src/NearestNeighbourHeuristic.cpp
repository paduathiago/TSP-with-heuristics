#include "NearestNeighbourHeuristic.h"

#include <random>

void NearestNeighbor::solve(std::string inputFile)
{
    std::vector<Node> cities = parser.parseTSPFile(inputFile);
    KdTree tree(cities);

    std::random_device rd;
    std::mt19937 gen(42);

    std::uniform_int_distribution<> dist(1, 6);

    int randomId = dist(gen);

    // First Node, chosen randomly
    std::shared_ptr<Node> newNodeInSolution = tree.findNodeById(randomId);
    std::shared_ptr<Node> oldNodeInSolution;
    std::cout << "First Node: " << newNodeInSolution->id << std::endl;
    while (!tree.empty())
    {
        solution.push_back(*newNodeInSolution);
        std::cout << "sol " << std::endl;
        printSolution();
        std::cout << "sol " << std::endl;
        oldNodeInSolution = tree.remove(*newNodeInSolution);
        tree.print_preorder();
        newNodeInSolution = tree.nearestNeighbour(*oldNodeInSolution);
        std::cout << "New Node: " << newNodeInSolution->id << std::endl;
    }
}

void NearestNeighbor::printSolution() const
{
    for (const Node& node : solution)
    {
        std::cout << node.id << " " << node.x << " " << node.y << std::endl;
    }
}