#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>

#include "DistanceMeasure.h"
#include "KdTree.h"
#include "NearestNeighbourHeuristic.h"
#include "Node.h"
#include "parser.h"
#include "VND.h"

int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename> <mode>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string mode = argv[2];

    if (mode == "NN")
    {
        NearestNeighbour nn;
        nn.solve(filename);
        // nn.printSolution();
        std::cout << nn.getTotalDistance() << std::endl;
    }
    else if (mode == "VND")
    {
        VND vnd(filename);
    }
    else
    {
        std::cout << "Invalid mode" << std::endl;
        return 1;
    }

    return 0;
}