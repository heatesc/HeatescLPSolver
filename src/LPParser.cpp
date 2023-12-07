#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <sstream>

#include "LPParser.hpp"
#include "LinearProgram.hpp"
#include "common.hpp"

using namespace std;

LPParser::LPParser() {};

optional<LinearProgram> LPParser::parseFile(const string& filename)
{
    // OPEN FILE
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "Error opening .lp input file" << endl;
        return nullopt;
    }
    
    ParseStatus parseStatus;
    
    // PARSE OPTIMISATION MODE
    OptimisationMode mode;
    parseStatus = parseOptimisationMode(inputFile, mode);
    if (parseStatus == ParseStatus::FAILURE)
    {
        cerr << "Error parsing optimisation mode" << endl;
        return nullopt;
    }

    // PARSE CONTINUOUS VARIABLES
    vector<string> continuousVariables;
    parseStatus = parseContinuousVariables(inputFile, continuousVariables);
    if (parseStatus == ParseStatus::FAILURE)
    {
        cerr << "Error parsing continuous variables" << endl;
        return nullopt;
    }

    // PARSE DISCRETE VARIABLES
    vector<string> discreteVariables;
    parseStatus = parseDiscreteVariables(inputFile, discreteVariables);
    if (parseStatus == ParseStatus::FAILURE)
    {
        cerr << "Error parsing discrete variables" << endl;
        return nullopt;
    }

    // PARSE OBJECTIVE COEFFICIENTS
    vector<double> objectiveCoefficients;
    parseStatus = parseObjectiveCoefficients(inputFile, objectiveCoefficients);
    if (parseStatus == ParseStatus::FAILURE)
    {
        cerr << "Error parsing objective coefficients" << endl;
        return nullopt;
    }

    // PARSE CONSTRAINTS MATRIX
    vector<vector<double>> constraintsMatrix;
    parseStatus = parseConstraintsMatrix(inputFile, constraintsMatrix);
    if (parseStatus == ParseStatus::FAILURE)
    {
        cerr << "Error parsing constraints matrix" << endl;
        return nullopt;
    }
    
    // PARSE CONSTRAINTS VECTOR
    vector<double> constraintsVector;
    parseStatus = parseConstraintsVector(inputFile, constraintsVector);
    if (parseStatus == ParseStatus::FAILURE)
    {
        cerr << "Error parsing constraints vector" << endl;
        return nullopt;
    }
    
    // CLOSE FILE AND RETURN LINEAR PROGRAM
    LinearProgram lp;
    lp.setOptimisationMode(mode);
    lp.setContinuousVariables(continuousVariables);
    lp.setDiscreteVariables(discreteVariables);
    lp.setObjectiveCoefficients(objectiveCoefficients);
    lp.setConstraintMatrix(constraintsMatrix);
    lp.setConstraintVector(constraintsVector);
    if (!linearProgramIsValid(lp))
    {
        cerr << "Error parsing linear program" << endl;
        return nullopt;
    }
    return lp;  
}

bool LPParser::linearProgramIsValid(const LinearProgram& lp)
{
    // CHECK THAT EACH ROW OF THE CONSTRAINT MATRIX HAS A SIZE EQUAL TO
    // THE NUMBER OF VARIABLES IN THE LINEAR PROGRAM    
    size_t numVariables = lp.getContinuousVariables().size() + lp.getDiscreteVariables().size();
    for (vector<double> row : lp.getConstraintMatrix())
    {
        if (row.size() != numVariables)
        {
            cerr << "Error: constraint matrix row has incorrect number of elements" << endl;
            return false;
        }
    }

    // CHECK THAT THE CONSTRAINT VECTOR HAS A SIZE EQUAL TO THE NUMBER OF ROWS
    // IN THE CONSTRAINT MATRIX
    if (lp.getConstraintVector().size() != lp.getConstraintMatrix().size())
    {
        cerr << "Error: constraint vector has incorrect number of elements" << endl;
        return false;
    }

    return true; 
}

ParseStatus LPParser::parseOptimisationMode(ifstream& file, OptimisationMode& mode)
{
    string line;
    getline(file, line);
    if (line == "max")
    {
        mode = OptimisationMode::MAX;
    }
    else if (line == "min")
    {
        mode = OptimisationMode::MIN;
    }
    else
    {
        return ParseStatus::FAILURE;
    }
    return ParseStatus::SUCCESS;
}

ParseStatus LPParser::parseContinuousVariables(ifstream& file, vector<string>& variables)
{
    string line;
    getline(file, line);

    // Check if variables line is "-". This means there are no continuous variables.
    if (line == "-")
    {
        return ParseStatus::SUCCESS;
    }

    // Ensure the variables line has no trailing or leading spaces
    if (!line.empty() && (line.front() == ' ' || line.back() == ' '))
    {
        cerr << "Error: continuous variables line starts or ends with a space" << endl;
        return ParseStatus::FAILURE;
    }

    // Tokenize the line and add the variables to the variables vector, while
    // checking that each variable name is valid, i.e. contains only alphanumeric characters
    istringstream iss(line);
    string variable;
    while (iss >> variable)
    {
        if (!all_of(variable.begin(), variable.end(), ::isalnum))
        {
            cerr << "Error: continuous variables line contains non-alphanumeric characters" << endl;
            return ParseStatus::FAILURE;
        }
        variables.push_back(variable);
    }
    return ParseStatus::SUCCESS;
}

ParseStatus LPParser::parseDiscreteVariables(ifstream& file, vector<string>& variables)
{
    string line;
    getline(file, line);
    string variable;

    // Check if variables line is "-". This means there are no 
    // continuous variables.
    if (line == "-")
    {
        return ParseStatus::SUCCESS;
    }

    // Check if the line has a trailing or leading space
    if (line[0] == ' ' || line[line.size() - 1] == ' ')
    {
        cerr << "Error: continuous variables line starts or ends with a space" << endl;
        return ParseStatus::FAILURE;
    }

    // Tokenize the line and add the variables to the variables vector, while
    // checking that each variable name is valid, i.e. contains only alphanumeric characters
    istringstream iss(line);
    while (iss >> variable)
    {
        if (!all_of(variable.begin(), variable.end(), ::isalnum))
        {
            cerr << "Error: discrete variables line contains non-alphanumeric characters" << endl;
            return ParseStatus::FAILURE;
        }
        variables.push_back(variable);
    }

    return ParseStatus::SUCCESS;
}

ParseStatus LPParser::parseObjectiveCoefficients(ifstream& file, vector<double>& coefficients)
{
    string line;
    getline(file, line);

    // check if line is "-". This means there are no 
    // objective coefficients.
    if (line == "-")
    {
        return ParseStatus::SUCCESS;
    }

    // VALIDITY CHECKS
    // ensure the variables line has no trailing or leading spaces
    if (line[0] == ' ' || line[line.size() - 1] == ' ')
    {
        cerr << "Error: continuous variables line starts or ends with a space" << endl;
        return ParseStatus::FAILURE;
    }

    // Tokenize the line and add the coefficients to the coefficients vector, while
    // checking that each coefficient is valid, i.e. can be converted to a double
    istringstream iss(line);
    string coefficient;
    while (iss >> coefficient)
    {
        if (!Utils::canParseAsDouble(coefficient))
        {
            cerr << "Error: objective coefficients line contains non-numeric characters" << endl;
            return ParseStatus::FAILURE;
        }
        coefficients.push_back(stod(coefficient));
    }
    
    return ParseStatus::SUCCESS;
}

ParseStatus LPParser::parseConstraintsMatrix(ifstream& file, vector<vector<double>>& matrix)
{
    string line;
    vector<double> row;

    // read the file line by line until the line "END OF CONSTRAINTS MATRIX" is reached
    while (getline(file, line))
    {
        if (line == "END OF CONSTRAINTS MATRIX")
        {
            break;
        }   

        // check if line has a trailing or leading space
        if (line[0] == ' ' || line[line.size() - 1] == ' ')
        {
            cerr << "Error: constraints matrix line starts or ends with a space" << endl;
            return ParseStatus::FAILURE;
        }

        // tokenize the line and add the entries to the matrix row vector, while
        // checking that each entry is valid, i.e. can be converted to a double
        istringstream iss(line);
        string entry;
        while (iss >> entry)
        {
            if (!Utils::canParseAsDouble(entry))
            {
                cerr << "Error: constraints matrix line contains non-numeric characters" << endl;
                return ParseStatus::FAILURE;
            }
            row.push_back(stod(entry));
        }
        matrix.push_back(row);
        row.clear();
    }

    return ParseStatus::SUCCESS;
}

ParseStatus LPParser::parseConstraintsVector(ifstream& file, vector<double>& vector)
{
    string line;
    getline(file, line);

    // check if line is "-". This means there are no 
    // constraints.
    if (line == "-")
    {
        return ParseStatus::SUCCESS;
    }

    // ensure the line has no trailing or leading spaces
    if (line[0] == ' ' || line[line.size() - 1] == ' ')
    {
        cerr << "Error: constraints vector line starts or ends with a space" << endl;
        return ParseStatus::FAILURE;
    }

    // tokenize the line and add the entries to the vector, while 
    // checking that each entry is valid, i.e. can be converted to a double
    istringstream iss(line);
    string entry;
    while (iss >> entry)
    {
        if (!Utils::canParseAsDouble(entry))
        {
            cerr << "Error: constraints vector line contains non-numeric characters" << endl;
            return ParseStatus::FAILURE;
        }
        vector.push_back(stod(entry));
    } 
    return ParseStatus::SUCCESS;
}