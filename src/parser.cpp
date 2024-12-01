#include "parser.h"

#include <regex>
#include <algorithm>
#include <random>

std::vector<Node> Parser::parseTSPFile(const std::string& filename, bool shuffle)
{
    std::vector<Node> cities;
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }

    std::string line;
    bool readingNodes = false;

    while (std::getline(file, line))
    {
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

    if (shuffle)  // experimental
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cities.begin(), cities.end(), g);
    }

    return cities;
}

unsigned Parser::getNumberOfNodes(const std::string& filename) const
{
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }

    std::string line;

    while (std::getline(file, line))
    {
        // remove trailing spaces to make parsing easier
        line.erase(line.find_last_not_of(" \n\r\t") + 1);

        std::regex dimension_regex(R"(DIMENSION\s*:\s*(\d+))");
        std::smatch match;
        if (std::regex_search(line, match, dimension_regex) && match.size() > 1)
        {
            unsigned dimension = std::stoi(match.str(1));
            file.close();
            return dimension;
        }
    }
    throw std::runtime_error("Error reading DIMENSION line.");
    return 0;
}

std::unique_ptr<DistanceMeasure> Parser::getDistanceMeasure(const std::string& filename) const
{
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }

    std::string line;

    while (std::getline(file, line))
    {
        // remove trailing spaces to make parsing easier
        line.erase(line.find_last_not_of(" \n\r\t") + 1);

        std::regex euc_2d_regex(R"(EDGE_WEIGHT_TYPE\s*:\s*EUC_2D)");
        std::regex att_regex(R"(EDGE_WEIGHT_TYPE\s*:\s*ATT)");
        if (std::regex_search(line, euc_2d_regex))
        {
            return std::make_unique<EuclideanDistance>();
        }
        else if (std::regex_search(line, att_regex))
        {
            return std::make_unique<PseudoEuclideanDistance>();
        }
    }

    throw std::runtime_error("Could not determine distance measure.");
    return nullptr;
}