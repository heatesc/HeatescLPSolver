#ifndef LINEARPROGRAM_HPP
#define LINEARPROGRAM_HPP

#include <vector>
#include <string>
#include "common.hpp"

enum class OptimisationMode
{
    MAX,
    MIN
};

class LinearProgram
{
public:
    LinearProgram();

    // SETTERS
    SetStatus setConstraintMatrix(const std::vector<std::vector<double>>& constraintMatrix);
    SetStatus setConstraintVector(const std::vector<double>& constraintVector);
    SetStatus setOptimisationMode(OptimisationMode isMaximisation);
    SetStatus setContinuousVariables(const std::vector<std::string>& variables);
    SetStatus setDiscreteVariables(const std::vector<std::string>& variables);

    // GETTERS
    std::vector<std::vector<double>> getConstraintMatrix();
    std::vector<double> getConstraintVector();
    OptimisationMode getOptimisationMode();
    std::vector<std::string> getContinuousVariables();
    std::vector<std::string> getDiscreteVariables();

private:
    std::vector<std::vector<double>> constraintMatrix;
    std::vector<double> constraintVector;
    OptimisationMode mode;
    std::vector<std::string> continuousVariables;
    std::vector<std::string> discreteVariables;
};

#endif