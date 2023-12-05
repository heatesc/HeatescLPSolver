#include "LinearProgram.hpp"
#include "common.hpp"

// SETTERS
SetStatus LinearProgram::setConstraintMatrix(const std::vector<std::vector<double>>& constraintMatrix) 
{
    this->constraintMatrix = constraintMatrix;
    return SetStatus::SUCCESS; // Assuming success, add actual logic as needed
}

SetStatus LinearProgram::setConstraintVector(const std::vector<double>& constraintVector) 
{
    this->constraintVector = constraintVector;
    return SetStatus::SUCCESS; // Similarly, add logic for success/failure
}

SetStatus LinearProgram::setOptimisationMode(OptimisationMode mode) 
{
    this->mode = mode;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setContinuousVariables(const std::vector<std::string>& variables) 
{
    this->continuousVariables = variables;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setDiscreteVariables(const std::vector<std::string>& variables) 
{
    this->discreteVariables = variables;
    return SetStatus::SUCCESS;
}

// GETTERS
std::vector<std::vector<double>> LinearProgram::getConstraintMatrix() 
{
    return this->constraintMatrix;
}

std::vector<double> LinearProgram::getConstraintVector() 
{
    return this->constraintVector;
}

OptimisationMode LinearProgram::getOptimisationMode() 
{
    return this->mode;
}

std::vector<std::string> LinearProgram::getContinuousVariables() 
{
    return this->continuousVariables;
}

std::vector<std::string> LinearProgram::getDiscreteVariables() 
{
    return this->discreteVariables;
}
