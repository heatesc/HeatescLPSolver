#include "LinearProgram.hpp"
#include "common.hpp"

// SETTERS
setStatus LinearProgram::setConstraintMatrix(const std::vector<std::vector<double>>& constraintMatrix) 
{
    this->constraintMatrix = constraintMatrix;
    return SET_SUCCESS; // Assuming success, add actual logic as needed
}

setStatus LinearProgram::setConstraintVector(const std::vector<double>& constraintVector) 
{
    this->constraintVector = constraintVector;
    return SET_SUCCESS; // Similarly, add logic for success/failure
}

setStatus LinearProgram::setOptimisationMode(optimisationMode mode) 
{
    this->mode = mode;
    return SET_SUCCESS;
}

setStatus LinearProgram::setContinuousVariables(const std::vector<std::string>& variables) 
{
    this->continuousVariables = variables;
    return SET_SUCCESS;
}

setStatus LinearProgram::setDiscreteVariables(const std::vector<std::string>& variables) 
{
    this->discreteVariables = variables;
    return SET_SUCCESS;
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

optimisationMode LinearProgram::getOptimisationMode() 
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
