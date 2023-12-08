#include "LinearProgram.hpp"
#include "common.hpp"

using namespace std;

LinearProgram::LinearProgram() {};

// SETTERS
SetStatus LinearProgram::setConstraintMatrix(const vector<vector<double>>& constraintMatrix) 
{
    this->constraintMatrix = constraintMatrix;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setConstraintVector(const vector<double>& constraintVector) 
{
    this->constraintVector = constraintVector;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setOptimisationMode(OptimisationMode mode) 
{
    this->mode = mode;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setContinuousVariables(const vector<string>& variables) 
{
    this->continuousVariables = variables;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setDiscreteVariables(const vector<string>& variables) 
{
    this->discreteVariables = variables;
    return SetStatus::SUCCESS;
}

SetStatus LinearProgram::setObjectiveCoefficients(const vector<double>& objectiveCoefficients) 
{
    this->objectiveCoefficients = objectiveCoefficients;
    return SetStatus::SUCCESS;
}

// GETTERS
vector<vector<double>> LinearProgram::getConstraintMatrix() const
{
    return this->constraintMatrix;
}

vector<double> LinearProgram::getConstraintVector() const
{
    return this->constraintVector;
}

OptimisationMode LinearProgram::getOptimisationMode() const
{
    return this->mode;
}

vector<string> LinearProgram::getContinuousVariables() const
{
    return this->continuousVariables;
}

vector<string> LinearProgram::getDiscreteVariables() const
{
    return this->discreteVariables;
}

vector<double> LinearProgram::getObjectiveCoefficients() const
{
    return this->objectiveCoefficients;
}