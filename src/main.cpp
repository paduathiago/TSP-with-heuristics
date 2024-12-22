#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>

#include "NearestNeighbourHeuristic.h"
#include "VND.h"
#include "ILS.h"

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
        std::cout << nn.getTotalDistance() << std::endl;
    }
    else if (mode == "VND")
    {
        VND vnd(filename);
        vnd.run();
        std::cout << vnd.getTotalDistance() << std::endl;
    }
    else if (mode == "ILS")
    {
        float initialTemperature = argc > 3 ? std::stof(argv[3]) : 600;
        float alpha = argc > 4 ? std::stof(argv[4]) : 0.99;

        ILS ils(filename);
        ils.run(initialTemperature, alpha);
        std::cout << ils.getTotalDistance() << std::endl;
    }
    else
    {
        std::cout << "Invalid mode" << std::endl;
        return 1;
    }

    return 0;
}