#ifndef LINEARPROGRAM_HPP
#define LINEARPROGRAM_HPP

#include <vector>
#include <string>
#include "common.hpp"

enum optimisationMode
{
    MAX,
    MIN
};

class LinearProgram
{
public:
    LinearProgram();

    // SETTERS
    setStatus setConstraintMatrix(const std::vector<std::vector<double>>& constraintMatrix);
    setStatus setConstraintVector(const std::vector<double>& constraintVector);
    setStatus setOptimisationMode(optimisationMode isMaximisation);
    setStatus setContinuousVariables(const std::vector<std::string>& variables);
    setStatus setDiscreteVariables(const std::vector<std::string>& variables);

    // GETTERS
    std::vector<std::vector<double>> getConstraintMatrix();
    std::vector<double> getConstraintVector();
    optimisationMode getOptimisationMode();
    std::vector<std::string> getContinuousVariables();
    std::vector<std::string> getDiscreteVariables();

private:
    std::vector<std::vector<double>> constraintMatrix;
    std::vector<double> constraintVector;
    optimisationMode mode;
    std::vector<std::string> continuousVariables;
    std::vector<std::string> discreteVariables;
};

#endif