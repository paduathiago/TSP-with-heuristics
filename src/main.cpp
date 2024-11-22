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

int main() {
    std::string filename = "instances/att48.tsp";

    NearestNeighbour nn;
    nn.solve(filename);
    nn.printSolution();

    return 0;
}