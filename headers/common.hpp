#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>

// returned by setters
enum class SetStatus
{
    SUCCESS,
    FAILURE
};

namespace Utils
{
    bool canParseAsDouble(const std::string& str);
};

#endif