#include "common.hpp"
#include <regex>
#include <string>

using namespace std;
using namespace Utils;

bool Utils::canParseAsDouble(const string& str)
{
    try 
    {
        stod(str);
        return true;
    }
    catch (const invalid_argument& e)
    {
        return false;
    }
}