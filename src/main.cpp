#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Node.h"
#include "parser.h"
#include "KdTree.h"

int main() {
    std::string filename = "kroA100.tsp";

    Parser parser;
    std::vector<Node> cities = parser.parseTSPFile(filename);

    KdTree tree(cities);

    return 0;
}