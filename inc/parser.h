#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Node.h"

class Parser
{
public:
    Parser() = default;
    std::vector<Node> parseTSPFile(const std::string& filename);
    unsigned getNumberOfNodes(const std::string& filename) const;
};

#endif // PARSER_H