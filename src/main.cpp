#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>

#include "Node.h"
#include "parser.h"
#include "KdTree.h"
#include "NearestNeighbourHeuristic.h"
#include "DistanceMeasure.h"

int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    NearestNeighbour nn;
    nn.solve(filename);
    nn.printSolution();
    // Parser parser;
    // std::unique_ptr<DistanceMeasure> distanceMeasure = parser.getDistanceMeasure(filename);
    // std::vector<Node> cities = parser.parseTSPFile(filename);
    // KdTree tree(cities, std::move(distanceMeasure));

    // tree.remove(cities[2]);
    // tree.print_preorder();

    return 0;
}