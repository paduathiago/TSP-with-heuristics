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
    // nn.printSolution();
    std::cout << nn.totalDistance() << std::endl;

    return 0;
}