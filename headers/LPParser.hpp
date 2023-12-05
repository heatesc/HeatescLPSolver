#ifndef LPPARSER_HPP
#define LPPARSER_HPP

#include "LinearProgram.hpp"
#include <optional>
#include <string>
#include <fstream>
#include <vector>

enum class ParseStatus
{
    SUCCESS,
    FAILURE
};

class LPParser 
{
public:
    LPParser();
    std::optional<LinearProgram> parseFile(const std::string& filename);

private:
    bool linearProgramIsValid(const LinearProgram& lp);
    ParseStatus parseOptimisationMode(std::ifstream& file, OptimisationMode& mode);
    ParseStatus parseContinuousVariables(std::ifstream& file, std::vector<std::string>& variables);
    ParseStatus parseDiscreteVariables(std::ifstream& file, std::vector<std::string>& variables);
    ParseStatus parseObjectiveCoefficients(std::ifstream& file, std::vector<double>& coefficients);
    ParseStatus parseConstraintsMatrix(std::ifstream& file, std::vector<std::vector<double>>& matrix);
    ParseStatus parseConstraintsVector(std::ifstream& file, std::vector<double>& vector);
};

#endif