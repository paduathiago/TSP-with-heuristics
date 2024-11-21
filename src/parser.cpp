#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Node.h"

std::vector<Node> parseTSPFile(const std::string& filename) {
    std::vector<Node> cities;
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }

    std::string line;
    bool readingNodes = false;

    while (std::getline(file, line)) {
        // remove trailing spaces to make parsing easier
        line.erase(line.find_last_not_of(" \n\r\t") + 1);

        // from this point on, we read the coordinates
        if (line == "NODE_COORD_SECTION")
        {
            readingNodes = true;
            continue;
        }
        else if (line == "EOF")
            break;

        if (readingNodes) {
            std::istringstream iss(line);
            Node city;  // check

            if (!(iss >> city.id >> city.x >> city.y))
                throw std::runtime_error("Error reading line number " + line);

            cities.push_back(city);
        }
    }

    file.close();
    return cities;
}

// int main() {
//     const std::string filename = "../kroA100.tsp";

//     try {
//         std::vector<Node> cities = parseTSPFile(filename);

//         // Exibe as cidades extraídas
//         std::cout << "Cidades lidas do arquivo:" << std::endl;
//         for (const Node& city : cities)
//         {
//             std::cout << "ID: " << city.id << ", X: " << city.x << ", Y: " << city.y << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Erro: " << e.what() << std::endl;
//     }

//     return 0;
// }