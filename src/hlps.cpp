#include <iostream>
#include "hlps.hpp"
#include "LPParser.hpp"
#include "LinearProgram.hpp"
#include "LPSolver.hpp"
#include "common.hpp"

using namespace std;

int main()
{
    string filepath;
    cout << "Enter Linear Program filepath: ";
    getline(cin, filepath);
    cout << "Filepath entered: " << filepath << endl;

    LPParser parser;
    cout << "Parsing specified file...\n";
    auto lp = parser.parseFile(filepath);

    if (!lp.has_value())
    {
        cout << "Error parsing file\n";
        return 1;
    }

    // Output parsed LP
    cout << "Parsed LP:\n";
    cout << "Optimisation mode: " << (lp->getOptimisationMode() == OptimisationMode::MAX ? "MAX" : "MIN") << endl;

    cout << "Continuous variables: ";
    for (const auto& var : lp->getContinuousVariables())
    {
        cout << var << " ";
    }
    cout << "\nDiscrete variables: ";
    for (const auto& var : lp->getDiscreteVariables())
    {
        cout << var << " ";
    }
    cout << "\nObjective coefficients: ";
    for (const auto& coeff : lp->getObjectiveCoefficients())
    {
        cout << coeff << " ";
    }
    cout << "\nConstraint matrix:\n";
    for (const auto& row : lp->getConstraintMatrix())
    {
        for (const auto& coeff : row)
        {
            cout << coeff << " ";
        }
        cout << endl;
    }
    cout << "Constraint vector: ";
    for (const auto& coeff : lp->getConstraintVector())
    {
        cout << coeff << " ";
    }
    cout << "\nLP parsing complete\n";

    // Add code here to compute the optimal solution using the parsed LinearProgram

    cout << "Computing optimal solution...\n";
    // Assuming you have a function or class method to compute the solution
    // e.g., LPSolver solver; auto solution = solver.solve(lp.value());

    cout << "<optimal solution>\n"; // Replace this with actual output of the solution

    return 0;
}
