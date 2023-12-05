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
    cin >> filepath;
    cout << "filepath entered: " << filepath << endl;
    cout << "Parsing specified file...\n";
    cout << "Computing optimal solution...\n";
    cout << "<optimal solution>\n";
    return 0;
}