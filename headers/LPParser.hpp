#ifndef LPPARSER_HPP
#define LPPARSER_HPP

#include "LinearProgram.hpp"

class LPParser 
{
public:
    LPParser();
    LinearProgram parseFile(const std::string filename);
};

#endif