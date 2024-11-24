#include "parser.h"

std::vector<Node> Parser::parseTSPFile(const std::string& filename) {
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

        if (line.find("DIMENSION:") != std::string::npos) {
            std::istringstream iss(line);
            std::string label;
            unsigned dimension;
            if (iss >> label >> dimension)
            {
                file.close();
                return dimension;
            }
            else
            {
                throw std::runtime_error("Error reading DIMENSION line.");
                return 0;
            }
        }
    }
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

        if (line.find("EDGE_WEIGHT_TYPE: EUC_2D") != std::string::npos or line.find("EDGE_WEIGHT_TYPE : EUC_2D") != std::string::npos)
        {
            return std::make_unique<EuclideanDistance>();
        }
        else if (line.find("EDGE_WEIGHT_TYPE: ATT") != std::string::npos)
        {
            return std::make_unique<PseudoEuclideanDistance>();
        }
    }

    throw std::runtime_error("Could not determine distance measure.");
    return nullptr;
}